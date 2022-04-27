CC=gcc

CFLAGS=-Wall -Wextra -g

BINS=linkedlist
all: $(BINS)

%: %.c
	mkdir -p out
	$(CC) $(CFLAGS) $^ -o ./out/$@

clean:
	$(RM) -r ./out/$(BINS) 