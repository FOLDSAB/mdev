import socket

HOST_TCP = '0.0.0.0'  # Bind TCP socket to all available interfaces
PORT_TCP = 80

HOST_UDP = '0.0.0.0'  # Bind UDP socket to all available interfaces
PORT_UDP = 53  # DNS port

def handle_client_tcp(client_socket):
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
    
    # Close the TCP connection immediately after sending the response
    client_socket.close()

def handle_udp(udp_socket):
    while True:
        data, addr = udp_socket.recvfrom(1024)
        print(f"Received UDP message from {addr}: {data.decode()}")

def main():
    tcp_connections_count = 0
    
    # Create TCP socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as tcp_server_socket:
        # Bind TCP socket to address
        tcp_server_socket.bind((HOST_TCP, PORT_TCP))
        
        # Listen for incoming TCP connections
        tcp_server_socket.listen()
        print(f"TCP Server listening on {HOST_TCP}:{PORT_TCP}...")
        
        while tcp_connections_count < 3:
            # Accept incoming TCP connections
            client_socket, client_address = tcp_server_socket.accept()
            print(f"TCP Connection from {client_address}")
            
            # Handle TCP client request
            handle_client_tcp(client_socket)
            
            tcp_connections_count += 1
            if tcp_connections_count < 3:
                print(f"TCP Server listening on {HOST_TCP}:{PORT_TCP}...")
        
        # Close TCP server socket after 3 connections
        print("Closing TCP server socket...")
    
    # After handling TCP connections, switch to UDP
    
    # Create UDP socket
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as udp_server_socket:
        # Bind UDP socket to address
        udp_server_socket.bind((HOST_UDP, PORT_UDP))
        
        print(f"UDP Server listening on {HOST_UDP}:{PORT_UDP}...")
        
        # Handle UDP messages
        handle_udp(udp_server_socket)

if __name__ == "__main__":
    main()
