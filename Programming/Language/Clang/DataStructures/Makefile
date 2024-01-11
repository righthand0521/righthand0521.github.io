SUBDIRS := $(wildcard */.)
ALLSUBDIRS = $(SUBDIRS:%=%)
BUILDSUBDIRS = $(SUBDIRS:%=build-%)
TESTSUBDIRS = $(SUBDIRS:%=test-%)
CLEANSUBDIRS = $(SUBDIRS:%=clean-%)

CC = gcc
C++ = g++
# CFLAGS = -ansi -g -Wall -O3 -ffreestanding -o
# CFLAGS = -std=c99 -g -Wall -O3 -ffreestanding -o
CFLAGS = -Wall -O3 -o
GPROFFLAGS = -Wall -pg -lc -o
LDFLAGS =
# LDFLAGS = -lm
DEBUGFLAGS = -DDEBUG=1
GDBFLAGS = -g3

QUIET = @
ECHO = echo
RM = rm -rf
CP = cp
STRIP = strip
OBJDUMP = objdump -S ?
FILE = file
VALGRIND = valgrind
VALGRIND_ARGS = -s --tool=memcheck --leak-check=full --max-stackframe=5000000
VALGRIND_VER = $(shell valgrind --version)
GPROF = gprof

SRC = $(wildcard *.c)
OBJS  = $(patsubst %.c, %, $(wildcard *.c))
C++_SRC = $(wildcard *.cpp)
C++_OBJS  = $(patsubst %.cpp, %, $(wildcard *.cpp))
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


.PHONY: $(SUBDIRS) $(BUILDSUBDIRS) $(TESTSUBDIRS) $(CLEANSUBDIRS)

all: clean $(ALLSUBDIRS)
	$(QUIET)$(ECHO)
	@for file in $(OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(CC) $(CFLAGS) $$file $$file.c $(DEBUGFLAGS) $(LDFLAGS); \
		$(CC) $(CFLAGS) $$file $$file.c $(DEBUGFLAGS) $(LDFLAGS); \
		$(FILE) $$file; \
	done
	$(QUIET)$(ECHO)
	@for file in $(C++_OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(C++) $(CFLAGS) $$file $$file.cpp $(DEBUGFLAGS) $(LDFLAGS); \
		$(C++) $(CFLAGS) $$file $$file.cpp $(DEBUGFLAGS) $(LDFLAGS); \
		$(FILE) $$file; \
	done

build: clean $(BUILDSUBDIRS)
	$(QUIET)$(ECHO)
	@for file in $(OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(CC) $(CFLAGS) $$file $$file.c $(LDFLAGS); \
		$(CC) $(CFLAGS) $$file $$file.c $(LDFLAGS); \
		$(ECHO) $(STRIP) $$file; \
		$(STRIP) $$file; \
		$(FILE) $$file; \
	done
	$(QUIET)$(ECHO)
	@for file in $(C++_OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(C++) $(CFLAGS) $$file $$file.cpp $(LDFLAGS); \
		$(C++) $(CFLAGS) $$file $$file.cpp $(LDFLAGS); \
		$(ECHO) $(STRIP) $$file; \
		$(STRIP) $$file; \
		$(FILE) $$file; \
	done

debug: clean
	@for file in $(OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(CC) $(GPROFFLAGS) $$file $$file.c $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS); \
		$(CC) $(GPROFFLAGS) $$file $$file.c $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS); \
		$(FILE) $$file; \
	done
	$(QUIET)$(ECHO)
	@for file in $(C++_OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(C++) $(GPROFFLAGS) $$file $$file.cpp $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS); \
		$(C++) $(GPROFFLAGS) $$file $$file.cpp $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS); \
		$(FILE) $$file; \
	done

test: clean
	@for file in $(OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(CC) $(GPROFFLAGS) $$file $$file.c $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS); \
		$(CC) $(GPROFFLAGS) $$file $$file.c $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS); \
		$(FILE) $$file; \
		$(ECHO) ./$$file; \
		$(ECHO) "$(VALGRIND) $(VALGRIND_ARGS)" ./$$file; \
		$(ECHO) "$(GPROF) -b $$file $(GMON)"; \
		$(ECHO) "$(GPROF) -b -A $$file $(GMON)"; \
		$(ECHO) "$(GPROF) -b $$file $(GMON) | gprof2dot | dot -T png -o output.png"; \
	done
	$(QUIET)$(ECHO)
	@for file in $(C++_OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(C++) $(GPROFFLAGS) $$file $$file.cpp $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS); \
		$(C++) $(GPROFFLAGS) $$file $$file.cpp $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS); \
		$(FILE) $$file; \
		$(ECHO) ./$$file; \
		$(ECHO) "$(VALGRIND) $(VALGRIND_ARGS)" ./$$file; \
		$(ECHO) "$(GPROF) -b $$file $(GMON)"; \
		$(ECHO) "$(GPROF) -b -A $$file $(GMON)"; \
		$(ECHO) "$(GPROF) -b $$file $(GMON) | gprof2dot | dot -T png -o output.png"; \
	done

gprof: clean $(GPROFSUBDIRS)
	$(QUIET)$(ECHO)
	@for file in $(OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(CC) $(GPROFFLAGS) $$file $$file.c $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS); \
		$(CC) $(GPROFFLAGS) $$file $$file.c $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS); \
		$(FILE) $$file; \
		$(ECHO) "$(GPROF) -b $$file $(GMON)"; \
		$(ECHO) "$(GPROF) -b -A $$file $(GMON)"; \
		$(ECHO) "$(GPROF) -b $$file $(GMON) | gprof2dot | dot -T png -o output.png"; \
	done

valgrind: clean $(VALGRINDSUBDIRS)
	$(QUIET)$(ECHO)
	@for file in $(OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(CC) $(CFLAGS) $$file $$file.c $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS); \
		$(CC) $(CFLAGS) $$file $$file.c $(DEBUGFLAGS) $(LDFLAGS); \
		$(FILE) $$file; \
		$(ECHO) "$(VALGRIND) $(VALGRIND_ARGS)" ./$$file; \
		$(VALGRIND) $(VALGRIND_ARGS) ./$$file; \
	done

lib: clean
	@for file in $(OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(CC) $(CFLAGS) -fPIC -shared lib$$file.so $$file.c; \
		$(CC) $(CFLAGS) -fPIC -shared lib$$file.so $$file.c; \
		$(FILE) lib$$file.so; \
	done

clean: $(CLEANSUBDIRS)
	@clear
	$(QUIET)$(ECHO)
	@find . -name "*.so" -exec echo rm {} \; -exec rm -rf {} \;
	@find . -name "*.out" -exec echo rm {} \; -exec rm -rf {} \;
	@find . -name "vgcore.*" -exec echo rm {} \; -exec rm -rf {} \;
	@for file in $(OBJS) ; do \
		if [ -a $$file ]; then \
			$(ECHO) $(RM) $$file; \
			$(RM) $$file; \
		fi; \
	done
	@for file in $(C++_OBJS) ; do \
		if [ -a $$file ]; then \
			$(ECHO) $(RM) $$file; \
			$(RM) $$file; \
		fi; \
	done
	$(QUIET)$(ECHO)


$(ALLSUBDIRS):
	$(QUIET)$(ECHO)
	$(MAKE) -C $(@:%=%)

$(BUILDSUBDIRS):
	$(QUIET)$(ECHO)
	$(MAKE) -C $(@:build-%=%) build

$(GPROFSUBDIRS):
	$(QUIET)$(ECHO)
	$(MAKE) -C $(@:gprof-%=%) gprof

$(VALGRINDSUBDIRS):
	$(QUIET)$(ECHO)
	$(MAKE) -C $(@:valgrind-%=%) valgrind

$(CLEANSUBDIRS):
	$(QUIET)$(ECHO)
	$(MAKE) -C $(@:clean-%=%) clean

info:
	$(QUIET)$(ECHO) "CC = $(CC)"
	$(QUIET)$(ECHO) "C++ = $(C++)"
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
