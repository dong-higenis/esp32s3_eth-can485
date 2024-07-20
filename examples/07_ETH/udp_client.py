from socket import *

# Change to the IP address of the board
#address = ("192.168.50.210", 1234)
address = ("192.168.50.165", 1234)

s = socket(AF_INET, SOCK_DGRAM)

s.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)

message = b"This is"

s.sendto(message, address)

print(" send ok !")

s.close()