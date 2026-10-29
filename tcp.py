import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_ip = "127.0.0.1"
server_port = 12345

server_socket.bind((server_ip, server_port))
server_socket.listen(1)

print("TCP Server is running...")
print("Waiting for client connection...")

while True:
    client_socket, client_address = server_socket.accept()
    print("Client connected:", client_address)

    data = client_socket.recv(1024).decode()
    num1, operator, num2 = data.split(",")

    num1 = float(num1)
    num2 = float(num2)

    if operator == "+":
        result = num1 + num2
    elif operator == "-":
        result = num1 - num2
    elif operator == "*":
        result = num1 * num2
    elif operator == "/":
        if num2 == 0:
            result = "Error: Division by zero"
        else:
            result = num1 / num2
    else:
        result = "Error: Invalid operator"

    print("Calculation:", num1, operator, num2)
    print("Result:", result)

    client_socket.sendall(str(result).encode())
    client_socket.close()

--------------

import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = ("127.0.0.1", 12345)

client_socket.connect(server_address)

num1 = input("Enter first number: ")
operator = input("Enter operator (+, -, *, /): ")
num2 = input("Enter second number: ")

message = num1 + "," + operator + "," + num2

client_socket.sendall(message.encode())

result = client_socket.recv(1024).decode()

print("Result from server:", result)

client_socket.close()
