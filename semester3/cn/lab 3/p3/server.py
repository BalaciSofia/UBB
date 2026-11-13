import socket, json, threading

HOST = "0.0.0.0"
PORT = 8888
BUF = 65536

clients = set()
state = []
lock = threading.Lock()

def send_json(sock, msg, addr):
    sock.sendto(json.dumps(msg).encode(), addr)

def broadcast_json(sock, msg):
    data = json.dumps(msg).encode()
    with lock:
        for c in list(clients):
            try:
                sock.sendto(data, c)
            except:
                pass

def handle(sock):
    while True:
        data, addr = sock.recvfrom(BUF)
        try:
            msg = json.loads(data.decode())
        except:
            continue

        mtype = msg.get("type")

        with lock:
            clients.add(addr)

        if mtype == "join":
            print("Join from", addr)
            send_json(sock, {"type": "state", "state": state}, addr)

        elif mtype == "draw":
            prim = msg.get("prim")
            if prim:
                with lock:
                    state.append(prim)
                broadcast_json(sock, {"type": "draw", "prim": prim})

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((HOST, PORT))
    print(f"Server running on {HOST}:{PORT}")
    handle(sock)

if __name__ == "__main__":
    main()
