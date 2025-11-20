import socket

def main():
    ip = "0.0.0.0"
    port = int(input("Port to bind: "))

    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind((ip, port))

    print("Simple UDP Whiteboard server on", ip, port)

    clients = set()
    canvas = []  # list of shape command strings

    while True:
        data, addr = s.recvfrom(4096)
        msg = data.decode().strip()

        # register client
        clients.add(addr)

        if msg == "SYNC":
            # send full canvas state to this client
            for cmd in canvas:
                s.sendto(cmd.encode(), addr)
            continue

        # any other message = shape command
        canvas.append(msg)

        # broadcast it to all clients
        for c in clients:
            s.sendto(msg.encode(), c)

if __name__ == "__main__":
    main()
