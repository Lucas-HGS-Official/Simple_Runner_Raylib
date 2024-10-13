default:
	cc -o game main.c -lraylib -lpthread

clean:
	rm -f game