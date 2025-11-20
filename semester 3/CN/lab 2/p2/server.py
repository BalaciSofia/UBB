import socket
import threading
import struct

def handle_client(conn, addr):
    print("[+] Connected:", addr)

    filepath = conn.recv(1024).decode()
    print("Client requested file:", filepath)

    try:
        # open file and read content
        with open(filepath, "rb") as f:
            content = f.read()
        length = len(content)
    except:
        # file not found
        length = -1
        content = b""

    # send length
    conn.send(length.to_bytes(4, "big", signed=True))

    # send content (only if exists)
    if length != -1:
        conn.send(content)

    conn.close()
    print("[-] Disconnected:", addr)


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
