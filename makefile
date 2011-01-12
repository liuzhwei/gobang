



scr = main.c base_shape.c
para = -Wall

main:$(scr) 
	gcc -o main $(scr) $(para)
clean:
	rm -r main
	rm -r *.o
	rm -r *~
