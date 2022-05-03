#include <arpa/inet.h>
#include <stdio.h>

void print_ip(char* msg, in_addr_t ip);

int main(void) {
    char* ipaddr = "192.168.0.1\0";
    in_addr_t ip = inet_addr(ipaddr);
    printf("original ipaddr: %s, uint32_t: %d\n", ipaddr, ip);
    print_ip("net byte order:", ip);
    uint32_t hostip = ntohl(ip);
    print_ip("host byte order:", hostip);

    if (inet_pton(AF_INET, ipaddr, &ip) != 1) {
        printf("inet_pton failed\n");
        return -1;
    }
    char ipbuf[INET_ADDRSTRLEN];
    printf("inet_pton: %s ==> %d\n", ipaddr, ip);
    if (inet_ntop(AF_INET, &ip, ipbuf, INET_ADDRSTRLEN) == NULL) {
        printf("inet_ntop failed\n");
        return -1;
    }
    printf("inet_ntop: %d ==> %s\n", ip, ipbuf);

    return 0;
}

void print_ip(char* msg, in_addr_t ip) {
    int i;
    uint8_t parts[4];

    printf(msg);
    for (i = 0; i < 4; i++) {
        parts[4 - i - 1] = ip & 0xff;
        ip >>= 8;
    }
    for (i = 0; i < 4; i++) {
        printf("%03d", parts[i]);
        if (i != 3) {
            printf(" ");
        }
    }
    printf("\n");
}