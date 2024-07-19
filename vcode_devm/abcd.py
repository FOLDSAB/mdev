# import socket

# HOST = '0.0.0.0'  # Bind to all available interfaces
# PORT = 80

# def handle_client(client_socket):
#     request_data = client_socket.recv(1024).decode()
#     print("Received request:")
#     print(request_data)
    
#     # Always respond with HTTP 200 OK
#     response = """HTTP/1.1 200 OK
# Content-Type: text/html

# <!DOCTYPE html>
# <html>
# <head>
#     <title>200 OK</title>
# </head>
# <body>
#     <h1>200 OK - It's working!</h1>
#     <p>This is a mock response from the server.</p>
# </body>
# </html>
# """

#     # Send the response
#     client_socket.sendall(response.encode())
#     client_socket.close()

# def main():
#     # Create socket
#     with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
#         # Bind socket to address
#         server_socket.bind((HOST, PORT))
        
#         # Listen for incoming connections
#         server_socket.listen()
#         print(f"Server listening on {HOST}:{PORT}...")
        
#         # Accept incoming connections and handle requests
#         while True:
#             client_socket, client_address = server_socket.accept()
#             print(f"Connection from {client_address}")
            
#             # Handle client request
#             handle_client(client_socket)

# if __name__ == "__main__":
#     main()





















import socket

HOST = '0.0.0.0'  # Bind to all available interfaces
PORT = 80

def handle_client(client_socket):
    request_data = client_socket.recv(1024).decode()
    print("Received request:")
    print(request_data)
    
    # Send HTTP 200 OK response
    response = """HTTP/1.1 200 OK
Content-Type: text/html

<!DOCTYPE html>
<html>
<head>
    <title>200 OK</title>
</head>
<body>
    <h1>200 OK - It's working!</h1>
    <p>This is a mock response from the server.</p>
</body>
</html>
"""
    client_socket.sendall(response.encode())
    
    # Close the connection immediately after sending the response
    client_socket.close()

def main():
    # Create socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        # Bind socket to address
        server_socket.bind((HOST, PORT))
        
        # Listen for incoming connections
        server_socket.listen()
        print(f"Server listening on {HOST}:{PORT}...")
        
        while True:
            # Accept incoming connections
            client_socket, client_address = server_socket.accept()
            print(f"Connection from {client_address}")
            
            # Handle client request
            handle_client(client_socket)
            
            # After sending the response and closing the connection, continue listening
            print(f"Server listening on {HOST}:{PORT}...")

if __name__ == "__main__":
    main()



