# CST 311 - Programming Assignment 3 - TCP Server
# Team 4/BayTech: Luis Jimenez-Barrios, Warren Ngoun, Yukio Rivera, Jennah Yasin
# This program acts as the server for the TCP client/server assignment 
# requirement, the in-between message manager between Clients X & Y.

# 11 - We need multithreading for this assignment to handle two different 
# clients concurrently. In other words, multithreading is needed so that the 
# server can handle multiple connections at the same time. Multithreading 
# prevents the recv connection socket line from blocking the main server thread 
# when more than one client attempts to access it as now each child thread will 
# block individually when they need to and our main/other threads can work as 
# needed.

# Imports needed for sockets & threading/semaphores
from multiprocessing import Semaphore
from socket import * 
import threading

serverPort = 12000 # port declaration

# Create two binary lock semaphores for later mutexing
firstConnCheck = Semaphore(1)
secondCheck = Semaphore(1)

# Lists for keeping track of data in-between threads, need lists b/c they 
# are mutable and so values can be changed.
firstClientChecker = [0, 0] # Variable for determining Client X/Y
secondResponse = [0] # Global list counter for keeping track of 2nd msg received
clientMsg = [0, 0] # List to keep track of text of first/second msgs
clientMsgCnt = [0] # List to keep count of num of messages sent already

threadTracker = [] # List to keep track of active threads

class connectionThread (threading.Thread):
    def __init__(self, connectionSocket):
        threading.Thread.__init__(self)
        # Thread Object variables, needed for checking certain conditions
        self.connSock = connectionSocket
        self.firstResponse = [0]
        self.msgWhile = [0]
        self.threadID = ''

    def run(self):
        # Checks to see which connection will be labeled X or Y, prints 
        # respective details too.
        # Uses semaphores to provide mutual exclusion to shared var.
        firstConnCheck.acquire()
        if (firstClientChecker[0] == 0):
            self.threadID = 'X'
            print("Accepted first connection, calling it client X")
            firstClientChecker[0] = 1
        else:
            self.threadID = 'Y'
            print("Accepted second connection, calling it client Y\n")
            print("Waiting to receive messages from client X and client Y...\n")
            secondResponse[0] = 1
        firstConnCheck.release()

        # First while loop tracks only the confirmation message that the server 
        # sends upon both connections. If two connections haven't been 
        # confirmed yet, it'll spin indefinitely waiting.
        while (self.firstResponse[0] < 1):
            # Tests if a thread has sent its confirmation message to respective 
            # client only AFTER Y has confirmed being connected.
            if (self.firstResponse[0] == 0 and secondResponse[0] == 1):
                self.sendConfirmation()
                self.firstResponse[0] = 1
        
        # After loop, threads WAIT for a response from their respective client
        result = self.connSock.recv(1024).decode()
        # On a msg, grab lock to ensure accurate msg receipt count & accurately 
        # setting up the message array in charge of final confirmations.
        secondCheck.acquire()
        clientMsgCnt[0] += 1
        # Server-side confirmation print of received msg & its number 
        print("Client " + self.threadID + " sent message " + str(clientMsgCnt[0]) + ": " + result)
        # if/elif to set up the actual list depending on which msg it is
        if (clientMsgCnt[0] == 1):
            clientMsg[0] = self.threadID + ": " + result
        elif (clientMsgCnt[0] == 2):
            clientMsg[1] = self.threadID + ": " + result
        secondCheck.release()
        
        # This while acts as a barrier to ensure that ONLY when both msgs have 
        # been received will the threads send their final confirmations.
        while (self.msgWhile[0] == 0):
            # Semaphore lock ensures we're reading an accurate msg count
            secondCheck.acquire() 
            if (clientMsgCnt[0] == 2):
                self.msgWhile[0] = 1 # exit loop on confirmation of 2 recv msgs
            secondCheck.release()

        self.sendFinalConfirmation() # Both threads can send their final msgs
            
    # Function lets each connectionThread send their respective connection 
    # message back to their matching clients.
    def sendConfirmation(self):
        toSend = "Client " + self.threadID + " Connected"
        self.connSock.send(toSend.encode())

    # Function lets each connectionThread send the same message back to their 
    # respective clients. Utilizes shared array to get the same results. 
    def sendFinalConfirmation(self):
        toSend = str(clientMsg[0]) + " received before " + str(clientMsg[1])
        self.connSock.send(toSend.encode())

# Create a TCP socket
serverSocket = socket(AF_INET, SOCK_STREAM)
# Assign IP address and port number to socket 
serverSocket.bind(('',serverPort))
# Set socket to listen now & print waiting message.
serverSocket.listen(1)
print ('The server is waiting to receive 2 connections...\n')

# Only allows 2 active clients, other clients WONT connect and hang b/c there 
# will be no more open accepting sockets.
while (threading.active_count() < 3):
    # Per connection, create a thread and run it, set them aside to later join()
    connectionSocket, addr = serverSocket.accept()
    tempThread = connectionThread(connectionSocket)
    tempThread.start()
    threadTracker.append(tempThread)
    
# Finally wait to join our threads back
for thread in threadTracker:
    thread.join()

# Final "waiting" and completion prints on socket close.
print()
print("Waiting a bit for clients to close their connection")
connectionSocket.close()
print("Done.")