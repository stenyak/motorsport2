CC = g++ -ansi

all:
	$(CC) -g -dH -Iinclude -I/usr/include src/*.cpp -o motorsport

clean:
	@echo Cleaning up...
	@rm src/*.o motorsport
	@echo Done.
run:
	@./motorsport
