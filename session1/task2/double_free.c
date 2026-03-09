/* Program with a 'double free' memory allocation bug */

#include <stdlib.h>

int main(void)
{
    int* a = (int*) calloc(4, sizeof(int));

    a[0] = 5;
    a[1] = 4;
    a[2] = 3;
    a[3] = 2;

    free(a); // releases the memory back to heap

    free(a); // double free - a still points to same address, but memory is already freed

    return 0;
}
