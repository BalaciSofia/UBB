// c_udp_server.c
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

    int s = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in srv, cli;
    memset(&srv, 0, sizeof(srv));
    srv.sin_family = AF_INET;
    srv.sin_port = htons(port);
    inet_pton(AF_INET, ip, &srv.sin_addr);

    bind(s, (struct sockaddr*)&srv, sizeof(srv));
    printf("UDP server listening on %s %d\n", ip, port);

    char buf[2048];
    socklen_t clen = sizeof(cli);

    while (1) {
        recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)&cli, &clen);
        // sending/receiving
    }

    close(s);
    return 0;
}
