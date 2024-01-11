CC=gcc
FLAGS=-I. `net-snmp-config --cflags` -g
DLFLAGS=-shared -fPIC -g

Test.so: Test.c
	$(CC) $(CFLAGS) $(DLFLAGS) -c -o Test.o Test.c
	$(CC) $(CFLAGS) $(DLFLAGS) -o Test.so Test.o

.PHONY : clean
clean :
	rm -f *.so *.o
