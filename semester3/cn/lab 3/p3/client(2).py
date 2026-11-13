import socket, json, threading, tkinter as tk, uuid, sys

SERVER_IP = "192.168.1.5"
SERVER_PORT = 8888
BUF = 65536

class Client:
    def __init__(self, server_ip, server_port):
        self.server = (server_ip, server_port)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind(('', 0))
        self.running = True
        self.root = tk.Tk()
        self.root.title("UDP Whiteboard")

        self.canvas = tk.Canvas(self.root, bg="white", width=800, height=600)
        self.canvas.pack(fill=tk.BOTH, expand=True)
        self.canvas.bind("<B1-Motion>", self.draw)
        self.canvas.bind("<ButtonRelease-1>", self.release)

        self.last = None
        self.color = "#000000"

        threading.Thread(target=self.listen, daemon=True).start()

        self.send_json({"type": "join"})

    def send_json(self, msg):
        self.sock.sendto(json.dumps(msg).encode(), self.server)

    def draw(self, event):
        if self.last is not None:
            x1, y1 = self.last
            x2, y2 = event.x, event.y
            prim = {
                "id": uuid.uuid4().hex,
                "shape": "line",
                "coords": [x1, y1, x2, y2],
                "color": self.color,
                "width": 2,
                "fill": None
            }
            self.canvas.create_line(x1, y1, x2, y2, fill=self.color, width=2)
            self.send_json({"type": "draw", "prim": prim})
        self.last = (event.x, event.y)

    def release(self, event):
        self.last = None

    def listen(self):
        while self.running:
            try:
                data, addr = self.sock.recvfrom(BUF)
                msg = json.loads(data.decode())
            except:
                continue
            mtype = msg.get("type")
            if mtype == "draw":
                prim = msg["prim"]
                x1, y1, x2, y2 = prim["coords"]
                self.canvas.create_line(x1, y1, x2, y2, fill=prim["color"], width=prim["width"])
            elif mtype == "state":
                self.canvas.delete("all")
                for prim in msg["state"]:
                    x1, y1, x2, y2 = prim["coords"]
                    self.canvas.create_line(x1, y1, x2, y2, fill=prim["color"], width=prim["width"])

    def run(self):
        self.root.mainloop()
        self.running = False

if __name__ == "__main__":
    ip = sys.argv[1] if len(sys.argv) > 1 else SERVER_IP
    port = int(sys.argv[2]) if len(sys.argv) > 2 else SERVER_PORT
    c = Client(ip, port)
    c.run()
