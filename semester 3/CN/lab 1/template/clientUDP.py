# python_udp_client.py
import socket

def main():
    ip = input("Server IP: ")
    port = int(input("Server port: "))

    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # send/recv happens in recipes file

if __name__ == "__main__":
    main()
