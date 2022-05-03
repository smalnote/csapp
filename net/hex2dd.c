/*
 * Conver a hexadecimal ip address to point seperated decimal ip address.
 */
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

char get(char* hex, int pos);
uint8_t hex2uint8(char c);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <hex ip address>\n", argv[0]);
        return -1;
    }

    char* ipaddr = argv[1];
    char buf[INET_ADDRSTRLEN];
    int i, offset = 0;
    for (i = 0; i < 4; i++) {
        uint8_t part = 0;
        char h = get(ipaddr, 2 + i * 2);
        char l = get(ipaddr, 2 + i * 2 + 1);
        part += hex2uint8(h) << 4 | hex2uint8(l);
        offset += sprintf(buf + offset, "%d", part);
        if (i != 3) {
            offset += sprintf(buf + offset, ".");
        }
    }
    buf[offset] = '\0';
    printf("%s\n", buf);
    return 0;
}

char get(char* hex, int pos) {
    char v = hex[pos];
    if (!(v >= '0' && v <= '9') && !(v >= 'a' && v <= 'f') && !(v >= 'A' && v <= 'F')) {
        printf("invalid hex char: %c\n", v);
        exit(-1);
    }
}

uint8_t hex2uint8(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    } else {
        printf("invalid hex char: %c\n", c);
        exit(-1);
    }
}