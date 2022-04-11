int multcnt = 0;

void mult(int *a, int *b, int *c, int n) {
    int i;
    multcnt++;
    for (i = 0; i < n; i++)
        c[i] = a[i] * b[i];
}