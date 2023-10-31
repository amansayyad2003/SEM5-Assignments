from socket import *
server_name = input('Enter the server name : ')
server_port = int(input('Enter the server port no : '))
client_socket = socket(AF_INET, SOCK_STREAM)
print(f'Trying to connect to {server_name}:{server_port}....')
client_socket.connect((server_name, server_port))
print(f'Connected to {server_name}:{server_port}')
while True:
    message = input('Enter your message: ')
    client_socket.send(message.encode())
    print('Waiting for server....')
    reply = client_socket.recv(1024).decode()
    print(f'server: {reply}')
client_socket.close()

