default:
	cc game.c -lraylib -lGL -lm -lpthread -ldl -lrt

clean:
	rm -f game