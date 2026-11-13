import socket
import struct

def main():
    ip = input("Server IP: ")
    port = int(input("Server port: "))

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((ip, port))

    # send recv here

    s.close()

if __name__ == "__main__":
    main()