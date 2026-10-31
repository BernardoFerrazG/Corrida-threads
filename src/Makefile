CC      ?= gcc
CFLAGS  ?= -Wall -Wextra -Wpedantic -O2
CPPFLAGS += -D_XOPEN_SOURCE=700
LDLIBS  += -pthread
CFLAGS  += -std=c11 -pthread

TARGET   = corrida
OBJS     = main.o threads.o
NTHREADS ?= 5

.PHONY: all run test clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

%.o: %.c threads.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) $(NTHREADS)

test: $(TARGET)
	./test.sh

clean:
	rm -f $(TARGET) $(OBJS)
