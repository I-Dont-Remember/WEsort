all: sort.c
	gcc -o sort -Wall sort.c
clean:
	$(RM) sort
