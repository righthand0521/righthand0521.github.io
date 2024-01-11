BUILD_ID := $(shell date +%Y%m%d%H%M%S)
CC = gcc
# CC = arm-linux-gnueabihf-gcc
CFLAGS = -O2 -Wall
TARGET = hello.exe

all: clean
	$(CC) -c $(CFLAGS) hello.c
	$(CC) -o $(TARGET) *.o

clean:
	rm -f $(TARGET) *.o
	rm -f *.pdf
	rm -f results.fpr

fortify: clean
	@echo $(BUILD_ID)
	sourceanalyzer -b $(BUILD_ID) -clean
	sourceanalyzer -b $(BUILD_ID) $(CC) -c $(CFLAGS) hello.c
	sourceanalyzer -b $(BUILD_ID) -show-build-warnings
	sourceanalyzer -b $(BUILD_ID) -show-files
	sourceanalyzer -b $(BUILD_ID) -scan -f results.fpr
	BIRTReportGenerator -template "Developer Workbook" -source results.fpr -format PDF -output $(BUILD_ID).pdf
