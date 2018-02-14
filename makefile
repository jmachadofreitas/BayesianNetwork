	
all:teste.o gerador.o prob.o amostra.o grafoo.o grafop.o bayes.o
	gcc -g amostra.o grafoo.o grafop.o bayes.o gerador.o -o gerador.out -lm
	gcc -g amostra.o grafoo.o grafop.o bayes.o prob.o -o prob.out -lm
	gcc -g amostra.o grafoo.o grafop.o bayes.o teste.o -o teste.out -lm
	@echo '                     «PROJECTO AMC - GRUPO14»                    '
teste.o: teste.c bayes.h
	gcc -c -g teste.c	
gerador.o: gerador.c bayes.h
	gcc -c -g gerador.c
prob.o: prob.c bayes.h
	gcc -c -g prob.c
amostra.o: amostra.c amostra.h
	gcc -c -g amostra.c
grafoo.o: grafoo.c grafoo.h
	gcc -c -g grafoo.c
grafop.o: grafop.c grafop.h
	gcc -c -g grafop.c
bayes.o: bayes.c bayes.h
	gcc -c -g bayes.c

clean:
	rm *.out
	rm *.o
	
	
	
	
	