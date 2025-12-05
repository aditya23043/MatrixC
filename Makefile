build: src/main.c
	cc src/main.c -o bin/main -Wall -g

run: bin/main
	./bin/main
