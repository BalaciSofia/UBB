// c_tcp_server.c
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    char ip[32];
    int port;

    printf("IP to bind: ");
    scanf("%31s", ip);
    printf("Port: ");
    scanf("%d", &port);

    int s = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in srv;
    memset(&srv, 0, sizeof(srv));
    srv.sin_family = AF_INET;
    srv.sin_port = htons(port);
    inet_pton(AF_INET, ip, &srv.sin_addr);

    bind(s, (struct sockaddr*)&srv, sizeof(srv));
    listen(s, 5);
    printf("TCP server listening on %s %d\n", ip, port);

    while (1) {
        int c = accept(s, NULL, NULL);
        //sending/receiving
        close(c);
    }

    close(s);
    return 0;
}
