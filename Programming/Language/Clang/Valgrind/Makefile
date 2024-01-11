CC = gcc
# CFLAGS = -ansi -g -Wall -O3 -ffreestanding -o
# CFLAGS = -std=c99 -g -Wall -O3 -ffreestanding -o
CFLAGS = -Wall -O3 -o
GPROFFLAGS = -Wall -pg -lc -o
LDFLAGS =
DEBUGFLAGS = -DDEBUG=1
GDBFLAGS = -g3

QUIET = @
ECHO = echo
RM = rm -rf
STRIP = strip
OBJDUMP = objdump -S ?
READELF = readelf -h
FILE = file
VALGRIND = valgrind
VALGRIND_ARGS = -s --tool=memcheck --leak-check=full --max-stackframe=5000000
VALGRIND_VER = $(shell valgrind --version)
GPROF = gprof

SRC = $(wildcard *.c)
OBJS  = $(patsubst %.c, %, $(wildcard *.c))
GMON = gmon.out

PATCH_VER = $(subst patch, , $(subst GNU, , $(shell for file in `patch -v | grep patch`; do echo $$file; done)))
PATCH_VER_MAJOR = $(word 1, $(subst ., ,$(PATCH_VER)))
PATCH_VER_MINOR = $(word 2, $(subst ., ,$(PATCH_VER)))
PATCH_VER_2_7 = $(shell [ $(PATCH_VER_MAJOR) -gt 2 -o \( $(PATCH_VER_MAJOR) -eq 2 -a $(PATCH_VER_MINOR) -ge 7 \) ] && echo true)
ifeq ($(PATCH_VER_2_7), true)
	PATCH_RESULT=found
else
	PATCH_RESULT=notfound
endif


all: clean
	@for file in $(OBJS) ; do \
		$(ECHO) $(CC) $(CFLAGS) $$file $$file.c $(DEBUGFLAGS) $(LDFLAGS); \
		$(CC) $(CFLAGS) $$file $$file.c $(DEBUGFLAGS) $(LDFLAGS); \
		$(FILE) $$file; \
	done

build: clean
	@for file in $(OBJS) ; do \
		$(ECHO) $(CC) $(CFLAGS) $$file $$file.c $(LDFLAGS); \
		$(CC) $(CFLAGS) $$file $$file.c $(LDFLAGS); \
		$(ECHO) $(STRIP) $$file; \
		$(STRIP) $$file; \
		$(FILE) $$file; \
	done

gprof: clean
	@for file in $(OBJS) ; do \
		$(ECHO) $(CC) $(GPROFFLAGS) $$file $$file.c $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS); \
		$(CC) $(GPROFFLAGS) $$file $$file.c $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS); \
		$(FILE) $$file; \
		$(ECHO) "$(GPROF) -b $$file $(GMON)"; \
		$(ECHO) "$(GPROF) -b -A $$file $(GMON)"; \
		$(ECHO) "$(GPROF) -b $$file $(GMON) | gprof2dot | dot -T png -o output.png"; \
	done

valgrind: clean
	@for file in $(OBJS) ; do \
		$(ECHO); \
		$(ECHO) $(CC) $(CFLAGS) $$file $$file.c $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS); \
		$(CC) $(CFLAGS) $$file $$file.c $(DEBUGFLAGS) $(LDFLAGS); \
		$(FILE) $$file; \
		$(ECHO) "$(VALGRIND) $(VALGRIND_ARGS)" ./$$file; \
		$(VALGRIND) $(VALGRIND_ARGS) ./$$file; \
	done

lib: clean
	@for file in $(OBJS) ; do \
		$(ECHO) $(CC) $(CFLAGS) -fPIC -shared lib$$file.so $$file.c; \
		$(CC) $(CFLAGS) -fPIC -shared lib$$file.so $$file.c; \
		$(FILE) lib$$file.so; \
	done


readelf:
	@for file in $(OBJS) ; do \
		if [ -a $$file ]; then \
			$(ECHO) $(READELF) $$file; \
			$(READELF) $$file; \
		fi; \
	done

clean:
	@clear
	@find . -name "*.so" -exec echo rm {} \; -exec rm -rf {} \;
	@find . -name "*.out" -exec echo rm {} \; -exec rm -rf {} \;
	@find . -name "vgcore.*" -exec echo rm {} \; -exec rm -rf {} \;
	@for file in $(OBJS) ; do \
		if [ -a $$file ]; then \
			$(ECHO) $(RM) $$file; \
			$(RM) $$file; \
		fi; \
	done

info:
	$(QUIET)$(ECHO) "CC = $(CC)"
	$(QUIET)$(ECHO) "CFLAGS = $(CFLAGS)"
	$(QUIET)$(ECHO) "GPROFFLAGS = $(GPROFFLAGS)"
	$(QUIET)$(ECHO) "LDFLAGS = $(LDFLAGS)"
	$(QUIET)$(ECHO) "DEBUGFLAGS = $(DEBUGFLAGS)"
	$(QUIET)$(ECHO) "GDBFLAGS = $(GDBFLAGS)"
	$(QUIET)$(ECHO) "VALGRIND_VER = $(VALGRIND_VER)"
	$(QUIET)$(ECHO) "PATCH_VER=$(PATCH_VER)"
	$(QUIET)$(ECHO) "PATCH_VER_MAJOR=$(PATCH_VER_MAJOR)"
	$(QUIET)$(ECHO) "PATCH_VER_MINOR=$(PATCH_VER_MINOR)"
	$(QUIET)$(ECHO) "PATCH_VER_2_7=$(PATCH_VER_2_7)"
	$(QUIET)$(ECHO) "PATCH_RESULT=${PATCH_RESULT}"
