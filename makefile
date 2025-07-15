lingo: data.o game.o help.o judge.o main.o menu.o
		gcc -o lingo data.o game.o help.o judge.o main.o menu.o -lncursesw
data.o: data.c
		gcc -c data.c
game.o: game.c
		gcc -c game.c
help.o: help.c
		gcc -c help.c
judge.o: judge.c
		gcc -c judge.c
main.o: main.c
		gcc -c main.c
menu.o: menu.c
		gcc -c menu.c
clean:
		rm lingo.exe data.o game.o help.o judge.o main.o menu.o