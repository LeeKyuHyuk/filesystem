SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
CFLAGS = -O2

all: clean fat32

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

fat32: $(OBJS)
	gcc $(OBJS) -o fat32

clean:
	rm fat32 *.o >/dev/null 2>/dev/null || true