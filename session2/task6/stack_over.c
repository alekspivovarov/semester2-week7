/* Program with a stack-based buffer overrun */

#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char* argv[])
{
    int i;
    int data[10];

    for (i = 0; i < 20; ++i) {
        data[i] = (i + 1) * (i + 1);
    }

    for (i = 0; i < 10; ++i) {
        printf("%d\n", data[i]);
    }

    return 0;
}
