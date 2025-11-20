import socket
import time

def main():
    ip = "192.168.1.5"
    port = int(input("Port to bind: "))

    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind((ip, port))

    print("UDP chat server on", ip, port)

    users = {}  # username -> (ip, port)

    while True:
        try:
            data, addr = s.recvfrom(1024)
        except BlockingIOError:
            continue
        msg = data.decode().strip()

        parts = msg.split()
        if len(parts) == 2 and parts[0] == "REGISTER":
            username = parts[1]
            users[username] = addr

            print(f"[REGISTER] {username} at {addr}")

            s.sendto(f"USERLIST {len(users)}".encode(), addr)
            time.sleep(0.05)

            for u, (uip, uport) in users.items():
                s.sendto(f"{u} {uip} {uport}".encode(), addr)
                time.sleep(0.05)

            # notify other clients
            for u, caddr in users.items():
                if u != username:
                    s.sendto(
                        f"NEWUSER {username} {addr[0]} {addr[1]}".encode(),
                        caddr
                    )


if __name__ == "__main__":
    main()
