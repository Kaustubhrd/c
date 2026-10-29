
import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_address = ("127.0.0.1", 12345)

message = input("Enter a string: ")

client_socket.sendto(message.encode(), server_address)

data, server_address = client_socket.recvfrom(1024)

reversed_message = data.decode()

print("Original string:", message)
print("Reversed string:", reversed_message)

client_socket.close()
