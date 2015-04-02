ROCmain : testReconnaissance.o image.o tab2Ddynamique.o affichage.o
	gcc -Wall -lm ROCmain.o testReconnaissance.o image.o tab2Ddynamique.o affichage.o -o ROCmain

ROCmain.o : ROCmain.c
	gcc -c -Wall ROCmain.c

testReconnaissance.o : testReconnaissance_v2.c testReconnaissance_v2.h
	gcc -c -Wall testReconnaissance_v2.c 

image.o : image.c image.h
	gcc -c -Wall image.c

tab2Ddynamique.o : tab2Ddynamique.c tab2Ddynamique.h
	gcc -c -Wall tab2Ddynamique.c

affichage.o : affichage.c affichage.h
	gcc -c -Wall affichage.C
