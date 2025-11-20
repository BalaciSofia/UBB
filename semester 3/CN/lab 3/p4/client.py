import socket
import threading

def main():
    server_ip = "192.168.1.5"
    server_port = int(input("Server port: "))
    username = input("Your username: ")

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(("", 0))
    sock.setblocking(False)

    server = (server_ip, server_port)
    peers = {}  # username -> (ip,port)

    # REGISTER
    sock.sendto(f"REGISTER {username}".encode(), server)

    # RECEIVE USERLIST HEADER
    while True:
        try:
            data, _ = sock.recvfrom(1024)
        except BlockingIOError:
            continue

        msg = data.decode().strip()
        parts = msg.split()

        if parts[0] == "USERLIST":
            count = int(parts[1])
            break

    # RECEIVE USERLIST ENTRIES
    for _ in range(count):
        while True:
            try:
                data, _ = sock.recvfrom(1024)
                break
            except BlockingIOError:
                continue

        u, ip, port = data.decode().split()
        peers[u] = (ip, int(port))

    print("Peers:", peers)

    # RECEIVER THREAD
    def receiver():
        while True:
            try:
                data, _ = sock.recvfrom(1024)
            except BlockingIOError:
                continue

            msg = data.decode().strip()
            parts = msg.split()

            if parts[0] == "NEWUSER":
                u = parts[1]
                ip = parts[2]
                port = int(parts[3])
                peers[u] = (ip, port)
                print(f"\nNew user: {u} @ {ip}:{port}\n> ", end="")
            else:
                print("\n" + msg + "\n> ", end="")

    threading.Thread(target=receiver, daemon=True).start()

    print("Chat ready. Start typing.\n")

    # MAIN CHAT LOOP
    while True:
        text = input("> ")
        if not text:
            continue

        msg = f"{username}: {text}"
        for u, (ip, port) in peers.items():
            if u == username:
                continue  # don't send to yourself
            sock.sendto(msg.encode(), (ip, port))

if __name__ == "__main__":
    main()
