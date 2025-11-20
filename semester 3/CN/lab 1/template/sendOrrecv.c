// recipes_c.c
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

// SEND -------------------------------------------------------

void send_int(int sock, int32_t n) {
    int32_t net = htonl(n);
    send(sock, &net, 4, 0);
}

void send_float(int sock, float f) {
    uint32_t temp;
    memcpy(&temp, &f, 4);   // float -> 4 raw bytes
    temp = htonl(temp);
    send(sock, &temp, 4, 0);
}

void send_char(int sock, char c) {
    send(sock, &c, 1, 0);
}

void send_string(int sock, const char *msg) {
    int32_t len = strlen(msg);
    int32_t net = htonl(len);
    send(sock, &net, 4, 0);
    send(sock, msg, len, 0);
}

void send_array(int sock, int32_t *arr, int32_t count) {
    int32_t count_net = htonl(count);
    send(sock, &count_net, 4, 0);
    for (int i = 0; i < count; i++) {
        int32_t x_net = htonl(arr[i]);
        send(sock, &x_net, 4, 0);
    }
}


// RECEIVE ----------------------------------------------------

int32_t recv_int(int sock) {
    int32_t net;
    recv(sock, &net, 4, 0);
    return ntohl(net);
}

float recv_float(int sock) {
    uint32_t net;
    recv(sock, &net, 4, 0);
    net = ntohl(net);

    float f;
    memcpy(&f, &net, 4);  // raw bytes → float
    return f;
}

char recv_char(int sock) {
    char c;
    recv(sock, &c, 1, 0);
    return c;
}

void recv_string(int sock, char *buffer, int maxlen) {
    int32_t len_net;
    recv(sock, &len_net, 4, 0);
    int32_t len = ntohl(len_net);

    if (len >= maxlen) len = maxlen - 1;

    recv(sock, buffer, len, 0);
    buffer[len] = '\0';
}

int recv_array(int sock, int32_t *arr, int max_count) {
    int32_t count_net;
    recv(sock, &count_net, 4, 0);
    int32_t count = ntohl(count_net);

    if (count > max_count) count = max_count;

    for (int i = 0; i < count; i++) {
        int32_t x_net;
        recv(sock, &x_net, 4, 0);
        arr[i] = ntohl(x_net);
    }

    return count;
}
