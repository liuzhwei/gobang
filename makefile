



scr = main.c basic_shape.c chessboard.c mouse.c
para = -Wall

main:$(scr) 
	gcc -o main $(scr) $(para)
clean:
	rm -r main
	rm -r *.o
	rm -r *~
