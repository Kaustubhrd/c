import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_ip = "127.0.0.1"
server_port = 12345

server_socket.bind((server_ip, server_port))

print("UDP Server is running...")
print("Waiting for a message from the client...")

while True:
    data, client_address = server_socket.recvfrom(1024)

    message = data.decode()
    print("Original message:", message)

    reversed_message = message[::-1]
    print("Reversed message:", reversed_message)

    server_socket.sendto(
        reversed_message.encode(),
        client_address
    )

    print("Reversed message sent to client.\n")

------------------

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
