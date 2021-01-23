all: rnnPG.o rnnST.o rnnAST.o rnnLowPass.o
	gcc -o rnnPG      rnnPG.o -lm
	gcc -o rnnST      rnnST.o -lm
	gcc -o rnnAST      rnnAST.o -lm
	gcc -o rnnLowPass  rnnLowPass.o -lm


rnnPG:	rnnPG.o
	gcc -o rnnPG      rnnPG.o -lm

rnnPG.o: rnnPG.c
	gcc -c rnnPG.c

rnnST.o:	rnnST.c
	gcc -c rnnST.c

rnnAST.o:	rnnAST.c
	gcc -c rnnAST.c

rnnLowPass.o:	rnnLowPass.c
	gcc -c rnnLowPass.c

clean:
	rm *.o rnnPG rnnST rnnAST rnnLowPass *.txt *~ 


display:	rnnPG 
	./rnnPG > t.txt && gnuplot  -e "plot 't.txt' using 2:3 title 'a_2-a_3 phase space' " -persist
	./rnnPG > t.txt && gnuplot  -e "plot [0:500] 't.txt' using 2 title 'a_2', 't.txt' using 3 title 'a_3' " -persist
	./rnnPG > t.txt && gnuplot  -e "plot [0:500] 't.txt' using 3 title 'a_3', 't.txt' using 4 title 'a_4 - amplification of a_3' " -persist
