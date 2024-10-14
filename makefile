default:
	cc -o game main.c -lraylib -lGL -lm -lpthread -ldl -lrt

clean:
	rm -f game