default:
	cc -o game main.c -I. -lraylib -lGL -lm -lpthread -ldl -lrt

clean:
	rm -f game