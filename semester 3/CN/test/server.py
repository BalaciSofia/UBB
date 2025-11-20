import socket
import time
def main():
    ip="192.168.28.1"
    port=7000

    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind((ip, port))

    print("UDP chat server on",ip,port)

    users={}

    while True:
        data,addr=s.recvfrom(1024)
        msg=data.decode().strip()

        parts=msg.split()
        if(len(parts)==2 and parts[0]=="Register"):
            print("tried to register")
            username=parts[1]
            users[username]=addr

        print(f"Registered {username}: {addr}")

        #send userlist
        s.sendto(f"USERLIST {len(users)}".encode(),addr)

        for u, (uip, uport) in users.items():
                s.sendto(f"{u} {uip} {uport}".encode(), addr)
                time.sleep(0.05)

        # notify other clients
        for u, caddr in users.items():
            if u != username:
                s.sendto(f"NEWUSER {username} {addr[0]} {addr[1]}".encode(),caddr)

        if len(parts)==2 and parts[0]== "QUIT":
            username=parts[1]
            #print("am ajuns aici, trimit notif la clienti ca a iesit")
            if username in users:
                print(f"QUIT {username}: {addr}")
                del users[username]#sterg din lista
                for u, caddr in users.items():
                    s.sendto(f"USERLEFT {username} {addr[0]} {addr[1]}".encode(), caddr)

if __name__=="__main__":
    main()