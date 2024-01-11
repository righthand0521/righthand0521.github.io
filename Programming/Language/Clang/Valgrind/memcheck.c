#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void memory_leak_test()
{
    char *buf = malloc(8);
}

void invalid_memory_access()
{
    // 1. Invalid write
    char *str = malloc(4);
    strcpy(str, "Brian");
    free(str);

    // 2. Invalid read
    int *arr = malloc(3);
    printf("%d", arr[4]);
    free(arr);

    // 3. Invalid read
    printf("%d", arr[0]);

    // 4. Invalid free
    free(arr);
}


int main(int argc, char **argv)
{
    memory_leak_test();
    invalid_memory_access();


    return EXIT_SUCCESS;
}

