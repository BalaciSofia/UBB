// recipes_udp_c.c
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

// SENDTO -----------------------------------------------------

void sendto_int(int sock, struct sockaddr_in *addr, int32_t n) {
    int32_t net = htonl(n);
    sendto(sock, &net, 4, 0, (struct sockaddr*)addr, sizeof(*addr));
}

void sendto_float(int sock, struct sockaddr_in *addr, float f) {
    uint32_t temp;
    memcpy(&temp, &f, 4);
    temp = htonl(temp);
    sendto(sock, &temp, 4, 0, (struct sockaddr*)addr, sizeof(*addr));
}

void sendto_char(int sock, struct sockaddr_in *addr, char c) {
    sendto(sock, &c, 1, 0, (struct sockaddr*)addr, sizeof(*addr));
}

void sendto_string(int sock, struct sockaddr_in *addr, const char *msg) {
    int32_t len = strlen(msg);
    int32_t net = htonl(len);

    char packet[4096];
    memcpy(packet, &net, 4);
    memcpy(packet + 4, msg, len);

    sendto(sock, packet, 4 + len, 0, (struct sockaddr*)addr, sizeof(*addr));
}

void sendto_array(int sock, struct sockaddr_in *addr, int32_t *arr, int count) {
    int32_t net_count = htonl(count);

    char packet[4096];
    int offset = 0;

    memcpy(packet + offset, &net_count, 4);
    offset += 4;

    for (int i = 0; i < count; i++) {
        int32_t net = htonl(arr[i]);
        memcpy(packet + offset, &net, 4);
        offset += 4;
    }

    sendto(sock, packet, offset, 0, (struct sockaddr*)addr, sizeof(*addr));
}


// RECVFROM ----------------------------------------------------

int32_t recvfrom_int(int sock, struct sockaddr_in *addr) {
    socklen_t l = sizeof(*addr);
    int32_t net;
    recvfrom(sock, &net, 4, 0, (struct sockaddr*)addr, &l);
    return ntohl(net);
}

float recvfrom_float(int sock, struct sockaddr_in *addr) {
    socklen_t l = sizeof(*addr);
    uint32_t net;
    recvfrom(sock, &net, 4, 0, (struct sockaddr*)addr, &l);

    net = ntohl(net);
    float f;
    memcpy(&f, &net, 4);
    return f;
}

char recvfrom_char(int sock, struct sockaddr_in *addr) {
    socklen_t l = sizeof(*addr);
    char c;
    recvfrom(sock, &c, 1, 0, (struct sockaddr*)addr, &l);
    return c;
}

int recvfrom_string(int sock, struct sockaddr_in *addr, char *buf, int maxlen) {
    socklen_t l = sizeof(*addr);

    int32_t len_net;
    recvfrom(sock, &len_net, 4, 0, (struct sockaddr*)addr, &l);
    int32_t len = ntohl(len_net);

    if (len >= maxlen) len = maxlen - 1;

    recvfrom(sock, buf, len, 0, (struct sockaddr*)addr, &l);
    buf[len] = '\0';

    return len;
}

int recvfrom_array(int sock, struct sockaddr_in *addr, int32_t *arr, int maxcount) {
    socklen_t l = sizeof(*addr);

    int32_t count_net;
    recvfrom(sock, &count_net, 4, 0, (struct sockaddr*)addr, &l);
    int32_t count = ntohl(count_net);

    if (count > maxcount) count = maxcount;

    for (int i = 0; i < count; i++) {
        int32_t x_net;
        recvfrom(sock, &x_net, 4, 0, (struct sockaddr*)addr, &l);
        arr[i] = ntohl(x_net);
    }

    return count;
}
