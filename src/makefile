#Makefile pour les tests locaux, pas pour l'arduino

OBJ = Bras.o  Capteur.o  main.o  Motor.o  Pompe.o  Tapis.o  Volet.o

robSv_test: $(OBJ)
	gcc $(OPTIMISATION) $^ $(GTK) -o $(EXE) 

%.o : %.c include.h
	gcc -c $<

clean:
	rm -f *.o