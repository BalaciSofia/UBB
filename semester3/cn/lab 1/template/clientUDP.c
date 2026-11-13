// c_udp_client.c
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    char ip[32];
    int port;

    printf("Server IP: ");
    scanf("%31s", ip);
    printf("Server port: ");
    scanf("%d", &port);

    int s = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in srv;
    memset(&srv, 0, sizeof(srv));
    srv.sin_family = AF_INET;
    srv.sin_port = htons(port);
    inet_pton(AF_INET, ip, &srv.sin_addr);

    // sending/receiving

    close(s);
    return 0;
}
