# PA2
# Luis Jimenez-Barrios, Warren Ngoun, Yukio Rivera, Jennah Yasin
# Client Ping software by BayTech for CST311 @ CSUMB
from http import client
from socket import *
import time

# Socket itself, timeout for 1 second, & num of packets to be sent
clientSocket = socket(AF_INET, SOCK_DGRAM)
clientSocket.settimeout(1)
pingNum = 10
# For standard RTT calculation
lostPackets = 0
beginTimer = time.time()
# Array of every RTT we'll need for further metrics

# Declaring vars for every RTT we'll need for further metrics
estimatedRtt = 0
prevDev = 0
sumRtt = 0
minRtt = 0
maxRtt = 0

# Loop of our pingNum of packets to be sent
for x in range(1, (pingNum + 1)):
    try:
        # Build our "PingX" strings to send
        message = "Ping" + str(x)
        print("Mesg sent: " + message)

        #  Sent to server the message & start recording time
        clientSocket.sendto(message.encode(), ('127.0.0.1', 12000))
        startTime = time.time()

        # Grab output from server & stop recording time
        moddedMsg, serverAddr = clientSocket.recvfrom(1024)
        endTime = time.time()

        # Output our received message & calculate RTT
        print("Mesg rcvd: " + moddedMsg.decode())
        rtt = (endTime - startTime) * 1000  # sec to milliseconds

        if (rtt < minRtt or minRtt == 0):
            minRtt = rtt

        if (rtt > maxRtt):
            maxRtt = rtt

        sumRtt += rtt 

        # Append values to arrays we'll use later for calculating metrics
        if (x == 1):
            estimatedRtt = rtt
            prevDev = rtt / 2.0
        else:
            estimatedRtt = (0.875 * estimatedRtt) + (0.125 * rtt)
            prevDev = (0.75 * prevDev) + (0.25 * abs(rtt - estimatedRtt))
        
        # Print Start/End & RTT times
        print("Start time: " + str(startTime))
        print("Return time: " + str(endTime))
        print("PONG " + str(x) + " RTT: " + str(rtt))
        print()  # Newline
    except timeout:
        # Handles lost packets
        print("Request Timed Out\n")
        lostPackets += 1
        
# Close down the socket
clientSocket.close()

print("Minimum RTT:    " + str(minRtt) + "ms")
print("Maximum RTT:    " + str(maxRtt) + "ms")
print("Average RTT:    " + str((sumRtt/(pingNum - lostPackets))) + "ms")
print("Packet Loss = " + str(lostPackets) +
      " (" + str((lostPackets/pingNum) * 100) + "% loss)")
print("Estimated RTT: " + str(estimatedRtt) + "ms")
print("Dev RTT: " + str(prevDev) + "ms")
print("Timeout Interval: " + str(estimatedRtt + (4 * prevDev)) + "ms")
