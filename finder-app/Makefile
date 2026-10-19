CROSS_COMPILE ?=
CC := $(CROSS_COMPILE)gcc
CFLAGS ?= -Wall -Werror -g

TARGET := writer
OBJS := writer.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
