compile ans: main.o 
	@gcc -o ans main.o -lm

main.o: main.c
	@gcc -c main.c

run: ans
	@./ans $(ARGS)

clean:
	@rm *.o
	@rm ans
