# PA2
# Luis Jimenez-Barrios, Warren Ngoun, Yukio Rivera, Jennah Yasin
# Server Ping software by BayTech for CST311 @ CSUMB
from operator import mod
import random
from socket import *

# Create & Bind Socket
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(('', 12000))
# Ping packet number tracker
pingnum = 0

print("Waiting for Client.....")
while True:
    # Count the pings received
    pingnum += 1
    # Generate random number in the range of 0 to 10
    rand = random.randint(0, 10)

    # Receive the client packet along with the
    # address it is coming from
    message, address = serverSocket.recvfrom(1024)

    # If rand is less is than 4, and this not the
    # first "ping" of a group of 10, consider the
    # packet lost and do not respond

    if rand < 4 and pingnum % 10 != 1:
        print("Packet was lost.")
        continue

    # Output statements
    print("PING " + str(pingnum) + " Received")
    moddedMsg = message.decode()  # decode text from client
    print("Mesg rcvd: " + moddedMsg)
    moddedMsg = moddedMsg.upper()  # uppercase message from client
    print("Mesg sent: " + moddedMsg)

    # Actually send msg back
    serverSocket.sendto(moddedMsg.encode(), address)
