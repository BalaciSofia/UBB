import socket
import threading
import struct
import time
import random


clients = []
lock = threading.Lock()
game_over = False

SRF = random.uniform(0, 100)
print("Server chose float:", SRF)

def end_game_after_10_seconds():
    global game_over
    time.sleep(10)
    game_over = True
    print("10 seconds passed. Evaluating...")

    # nobody connected
    if not clients:
        print("No clients participated.")
        return

    # find best guess
    best_conn = None
    best_error = float("inf")

    with lock:
        for conn, addr, guess in clients:
            error = abs(SRF - guess)
            if error < best_error:
                best_error = error
                best_conn = conn

        # send results
        for conn, addr, guess in clients:
            if conn is best_conn:
                msg = f"You have the best guess with an error of {best_error}"
            else:
                msg = "You lost!"
            conn.send(msg.encode())
            conn.close()
        clients.clear()
    print("Round ended.")

def handle_client(conn, addr):
    if game_over:
        # ignore late clients
        conn.send("Game already ended.".encode())
        conn.close()
        return

    print("[+] Connected:", addr)
    data = conn.recv(4)
    guess_scaled = int.from_bytes(data, "big")
    guess = guess_scaled / 1000.0

    print(f"Received guess {guess} from {addr}")

    # store client
    with lock:
        clients.append((conn, addr, guess))



def main():
    ip = input("IP to bind: ")
    port = int(input("Port: "))

    # creating socket
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # binding
    s.bind((ip, port))

    # listening
    s.listen(5)
    print("Server waiting for clients (10 seconds)...")

    # start game timer
    threading.Thread(target=end_game_after_10_seconds, daemon=True).start()

    while True:
        conn, addr = s.accept()
        threading.Thread(target=handle_client, args=(conn, addr)).start()


if __name__ == "__main__":
    main()
