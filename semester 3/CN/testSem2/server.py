import socket
import struct

def is_balanced(n: int) -> bool:
    s = str(n)
    odd = sum(int(s[i]) for i in range(0, len(s), 2))
    even = sum(int(s[i]) for i in range(1, len(s), 2))
    return odd == even

def next_balanced(n: int) -> int:
    x = n + 1
    while True:
        if is_balanced(x):
            return x
        x += 1

def main():
    ip = "192.168.1.5"
    tcp_port = 12345
    udp_port = 12345

    # TCP handshake socket
    s1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s1.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s1.bind((ip, tcp_port))
    s1.listen(5)
    s1.setblocking(False)              # allow concurrent TCP + UDP

    # UDP game socket
    s2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s2.bind((ip, udp_port))

    print(f"TCP handshake on {tcp_port}, UDP game on {udp_port}")

    while True:

        # ------- Accept TCP client if available -------
        try:
            conn, addr = s1.accept()
        except BlockingIOError:
            conn = None

        if conn:
            # username length
            ln_bytes = conn.recv(4)
            if not ln_bytes:
                conn.close()
                continue

            ln = struct.unpack("!I", ln_bytes)[0]
            username = conn.recv(ln).decode()

            print(f"[TCP] Connected: {addr}, Username: {username}")

            # send UDP port (16 bits)
            conn.send(struct.pack("!H", udp_port))
            conn.close()

        # ------- Handle UDP game -------
        try:
            data, addr = s2.recvfrom(4)
        except BlockingIOError:
            continue

        if len(data) != 4:
            continue

        number = struct.unpack("!I", data)[0]
        print(f"[UDP] received {number} from {addr}")

        if number == 0:
            s2.sendto(struct.pack("!I", 0), addr)
            continue

        nb = next_balanced(number)
        s2.sendto(struct.pack("!I", nb), addr)

if __name__ == "__main__":
    main()
