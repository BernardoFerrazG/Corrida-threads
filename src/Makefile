TARGET = corrida
SRC = main.c threads.c
NTHREADS ?= 5

all:
	gcc $(SRC) -o $(TARGET) -pthread -D_XOPEN_SOURCE=700

run: all
	./$(TARGET) $(NTHREADS)

clean:
	rm -f $(TARGET)