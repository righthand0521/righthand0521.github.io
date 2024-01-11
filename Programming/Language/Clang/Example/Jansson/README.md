# [Jansson](https://github.com/akheron/jansson)

[Jansson Documentation](https://jansson.readthedocs.io/en/latest/)

```bash
wget https://github.com/akheron/jansson/releases/download/v2.14/jansson-2.14.tar.gz
tar -zxvf jansson-2.14.tar.gz
cd jansson-2.14
./configure
make
make install
```

```bash
whereis libjansson
ls -l /usr/local/lib/libjansson.la
ls -l /usr/local/lib/libjansson.so
ls -l /usr/local/lib/libjansson.a
ln -s /usr/local/lib/libjansson.so /usr/lib/libjansson.so
ls -l /usr/lib/libjansson.so
ldconfig
```

```bash
cd examples
gcc -Wall -O3 -o simple_parse simple_parse.c -DDEBUG=1 -g3 -ljansson
```
