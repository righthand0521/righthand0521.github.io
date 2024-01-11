QUIET = @
ECHO = echo
RM = rm -rf
CP = cp
FILE = file

JAVAC = javac
JAVAC_VER = $(subst patch, , $(subst GNU, , $(shell for file in `javac --version`; do echo $$file; done)))
JAVAC_FLAGS = -g
JAVA = java
JAVA_VER = $(subst patch, , $(subst GNU, , $(shell for file in `java --version`; do echo $$file; done)))
JAVA_SRC = $(wildcard *.java)
JAVA_OBJS  = $(patsubst %.java, %, $(wildcard *.java))

all: clean java
	$(QUIET)$(ECHO)

java:
	$(QUIET)$(ECHO)
	@find . -name "*.class" -exec echo rm {} \; -exec rm -rf {} \;
	$(QUIET)$(ECHO)
	@for file in $(JAVA_OBJS) ; do \
		$(ECHO) $(JAVAC) $(JAVAC_FLAGS) $$file.java -d .; \
		$(JAVAC) $(JAVAC_FLAGS) $$file.java -d .; \
	done
	$(QUIET)$(ECHO)
	@find . -name "*.class" -exec $(FILE) {} \;

clean:
	@clear
	$(QUIET)$(ECHO)
	@find . -name "*.class" -exec echo rm {} \; -exec rm -rf {} \;

info:
	$(QUIET)$(ECHO) "JAVAC_VER=$(JAVAC_VER)"
	$(QUIET)$(ECHO) "JAVA_VER=$(JAVA_VER)"
