import socket
import threading

def receiver(sock):
    while True:
        try:
            data, _ = sock.recvfrom(4096)
            print("UPDATE:", data.decode().strip())
        except:
            pass

def main():
    ip = input("Server IP: ")
    port = int(input("Server port: "))

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(("", 0))  # random local port
    sock.setblocking(False)

    server = (ip, port)

    # request full canvas
    sock.sendto(b"SYNC", server)

    # background thread to receive broadcasts
    threading.Thread(target=receiver, args=(sock,), daemon=True).start()

    print("\nWhiteboard client ready.")
    print("Type commands like:")
    print("  LINE x1 y1 x2 y2 color")
    print("  CIRCLE cx cy r color")
    print("  RECT x1 y1 x2 y2 outline fill")
    print("  ELLIPSE x1 y1 x2 y2 outline fill")
    print("\nAnything you type will be broadcast to all clients.\n")

    while True:
        cmd = input("> ")
        if not cmd.strip():
            continue
        sock.sendto(cmd.encode(), server)

if __name__ == "__main__":
    main()
