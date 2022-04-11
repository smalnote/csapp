extern int buf[]; // link to a length-known array
// extern int *buf; // core dumped, buf length is not known

void swap() {
    int tmp = buf[0];
    buf[0] = buf[1];
    buf[1] = tmp;
}