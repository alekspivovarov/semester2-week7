/* Compile & run this program and observe what happens */

#include <stdio.h>

void assign_values(int x[])
{
    for (int i = 0; i < 100; ++i) { // trying to access memory that we have not created
        x[i] = (i + 1) * (i + 1);
    }
}

int main(void)
{
    int data[10] = { 0 }; // only 10 slots (on the stack - static memory)

    assign_values(data); // tries to write index 0-99
    printf("Done!\n");

    return 0;
}
