import socket
import threading
import struct

def handle_client(conn, addr):
    print("[+] Connected:", addr)

    cmd = conn.recv(1024).decode()

    import subprocess
    try:
        result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
        output = result.stdout + result.stderr
        exit_code = result.returncode
    except:
        output = "Command failed.\n"
        exit_code = -1

    # send output length first
    conn.send(len(output).to_bytes(4, "big"))

    # send output content
    conn.send(output.encode())

    # send exit code
    conn.send(exit_code.to_bytes(4, "big", signed=True))

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
