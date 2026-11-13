import socket
import struct
import random
import time


def main():
    #ip = input("IP to bind: ")
    ip="192.168.1.5"
    #port = int(input("Port: "))
    port=1234
    # creating UDP socket
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # binding
    s.bind((ip, port))
    print("UDP server listening on", ip, port)

    #random number
    guess = random.randint(1,100)
    print("Server choose:", guess)

    clients = {}

    while True:
        # recvfrom gives both data and client address

        data, addr = s.recvfrom(4096)
        print("[+] Packet from:", addr)

        #receiving guess number
        number = struct.unpack(">i", data)[0]

        if addr not in clients:
            clients[addr] = 0

        clients[addr] += 1

        if number > guess:
            s.sendto(b"smaller", addr)
        elif number < guess:
            s.sendto(b"larger", addr)
        else:
            # correct guess
            winner_tries = clients[addr]
            print(f"Client {addr} guessed correctly in {winner_tries} tries!")
            s.sendto(f"You won in {winner_tries} tries".encode(), addr)

            for rest,tries in clients.items():
                if rest != addr:
                    s.sendto(f"You lost after {tries} tries!".encode(), rest)

            # reset game
            time.sleep(2)
            print("Starting new game...")
            clients.clear()
            guess = random.randint(1,100)
            print("Server choose:", guess)


if __name__ == "__main__":
    main()
