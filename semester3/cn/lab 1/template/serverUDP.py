# python_udp_server.py
import socket

def main():
    ip = input("IP to bind: ")
    port = int(input("Port: "))

    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind((ip, port))
    print("UDP server listening on", ip, port)

    while True:
        data, addr = s.recvfrom(2048)
        print("[+] From:", addr)

if __name__ == "__main__":
    main()
