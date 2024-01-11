# LD_PRELOAD

## [用 LD_PRELOAD 替換動態連結的函式庫](http://fcamel-life.blogspot.tw/2011/09/ldpreload.html)

> [What is the LD_PRELOAD trick?](http://stackoverflow.com/questions/426230/what-is-the-ld-preload-trick)

- vim main.c

```c
#include <string.h>
#include <stdio.h>

int main(void) {
    char s[10];
    memset(s, 0, 0);
    putchar('X');
    putchar('\n');
    return 0;
}
```

```bash
gcc -o main main.c
./main
strings main | grep memset
```

- vim mylib.c

```c
#include <stddef.h>
#include <stdio.h>

int putchar(int c) {
    printf("call putchar()\n");
    return c;
}

void *memset(void *s, int c, size_t n) {
    printf("call memset()\n");
    return s;
}
```

```bash
gcc -Wall -fpic -shared -o libmylib.so mylib.c
LD_PRELOAD=./libmylib.so ./main
strings main | grep memset
```
