compile control.out write.out: control.o write.o
	@gcc -o control.out control.c -lm
	@gcc -o write.out write.c -lm

control.o: control.c
	@gcc -c control.c

write.o: write.c
	@gcc -c write.c

control: control.out
	@./control.out $(ARGS)
	
write: write.out
	@./write.out

clean:
	@rm *.o
	@rm control.out
	@rm write.out
