#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Hello\n");

    unsigned int i = 3;
    printf("%.*s\n", i, "abcdefg");

    return 0;
}
