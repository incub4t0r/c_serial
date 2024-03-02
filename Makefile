all:
	gcc main.c -o main.out -Iinclude src/buffer.c src/serialization.c

clean:
	rm -f main.out