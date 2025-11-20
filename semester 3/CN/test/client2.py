import socket
import threading

def main():
    server_ip = "192.168.28.1"
    server_port = int(input("Server port: "))
    username = input("Your username: ")

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(("", 0))
    sock.setblocking(False)

    server = (server_ip, server_port)
    peers = {}  # username -> (ip,port)

    sock.sendto(f"Register {username}".encode(), server)

    # recv user list how many
    while True:
        try:
            data, _ = sock.recvfrom(1024)
        except BlockingIOError:
            continue

       #print("recived numeber of users")
        #print(data.decode())
        msg = data.decode().strip()
        parts = msg.split()

        if parts[0] == "USERLIST":
            count = int(parts[1])
            break

    # recv user list entries
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
                if parts[0] == "USERLEFT":
                    print("am ajuns aici in client sterg din lista de prieteni si printez ca a iesit")
                    u = parts[1]
                    del peers[u]
                    print(f"\nUser left: {u} @ {ip}:{port}\n> ", end="")
                else:
                    print("\n" + msg + "\n> ", end="")

    threading.Thread(target=receiver, daemon=True).start()

    print("Chat ready. Start typing.\n")

    #chat loop
    while True:
        text = input("> ")
        if not text:
            continue

        if text != "quit" :
            msg = f"{username}: {text}"
            for u, (ip, port) in peers.items():
                if u == username:
                    continue  # don't send to me
                sock.sendto(msg.encode(), (ip, port))
        else:
            #print("am ajuns aici am identificat mesajul quit")
            msg = f"QUIT {username}"
            sock.sendto(msg.encode(), (server_ip, server_port))

if __name__ == "__main__":
    main()
