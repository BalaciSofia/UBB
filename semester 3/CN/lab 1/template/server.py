import socket
import threading
import struct

def handle_client(conn, addr):
    print("[+] Connected:", addr)
    conn.close()
    #lalalla

def main():
    ip = input("IP to bind: ")
    port = int(input("Port: "))

    # creating socket
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # binding
    s.bind((ip, port))

    # listening
    s.listen(5)
    print("Server listening on", ip, port)

    while True:
        conn, addr = s.accept()
        threading.Thread(target=handle_client, args=(conn, addr)).start()


if __name__ == "__main__":
    main()
