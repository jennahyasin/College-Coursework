# CST 311 - Programming Assignment 3 - TCP Client
# This program acts as the client for the TCP client/server assignment 
# requirement, sending inputted messages to the server. 
#Team 4/BayTech - Luis Jimenez-Barrios, Warren Ngoun, Yukio Rivera, Jennah Yasin
from socket import *

# Server Connection Variables
serverName = '127.0.0.1'
serverPort = 12000
# Socket Variable and Connection
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))
# While Loop tracker
testCase = True

# While loop keeps client in perpetual state of waiting on results from Server
# Only acts on two messages: A connection message & a final results message.
while testCase:
    # Receive results, print them, prep tempSplit for later testing
    result = clientSocket.recv(1024).decode()
    print(result)
    tempSplit = result.split(" ")

    # Case for first Connection message, just check strings
    if (result == 'Client X Connected' or result == 'Client Y Connected'):
        message = input("Enter message to send to server: ")
        clientSocket.send(message.encode())
    # Case for FINAL connection message w/ first sender results
    # Checking by using Split to see the first few chars of 'X/Y:'
    elif (tempSplit[0] == 'X:' or tempSplit[0] == 'Y:'):
        testCase = False

# Close down the socket once we've gotten final message
clientSocket.close()