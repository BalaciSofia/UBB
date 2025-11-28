import socket
import struct

def main():
    #ip = input("IP to bind: ")
    ip="192.168.28.1"
    #port = int(input("Port: "))
    port=1234
    # creating UDP socket
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # binding
    s.bind((ip, port))
    print("UDP server listening on", ip, port)

    while True:
        data, addr = s.recvfrom(4096)
        print("[+] Packet from:", addr)
        s.sendto(data, addr)

if __name__ == "__main__":
    main()
