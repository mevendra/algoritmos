executar: a.out
ifdef NOME
ifdef NUMERO
ifdef TIPO
ifdef MAXIMO
	./a.out $(NOME) $(NUMERO) $(TIPO) $(MAXIMO)
else
	./a.out $(NOME) $(NUMERO) $(TIPO)
endif
else
	./a.out $(NOME) $(NUMERO)
endif
else
	./a.out $(NOME)
endif
else
	./a.out
endif

limpar:
	rm *.h.gch
	rm a.out

remover:
	limpar
	rm desenhos/*
	rm outros/*
	rm aneis/*

a.out: *.h *.cpp
	make compilar

compilar: *.h *.cpp
	g++ -O3 -pthread -std=c++11 *.h *.cpp

debug: *.h *.cpp
	g++ -g -O3 -pthread -std=c++11 *.h *.cpp
	
dot: entrada/*.dot
	dot -Tpdf -O desenhos/*.dot

all_nome: a.out
ifdef NOME
	./a.out $(NOME) 1
	./a.out $(NOME) 2
	./a.out $(NOME) 3
endif

all_1_2: a.out
	-./a.out ap.txt 1
	-./a.out ap.txt 2
	-./a.out Arara4MaqPar.txt 1
	-./a.out Arara4MaqPar.txt 2
	-./a.out chacobo_fem.txt 1
	-./a.out chacobo_fem.txt 2
	-./a.out chacobo_mas.txt 1
	-./a.out chacobo_mas.txt 2
	-./a.out deni.txt 1
	-./a.out deni.txt 2
	-./a.out EN4MaqPar.txt 1
	-./a.out EN4MaqPar.txt 2
	-./a.out im.txt 1
	-./a.out im.txt 2
	-./a.out kraho.txt 1
	-./a.out kraho.txt 2
	-./a.out marcapata.txt 1
	-./a.out marcapata.txt 2 1 6
	-./a.out marcapata.txt 2
	-./a.out mbya.txt 1
	-./a.out mbya.txt 2
	-./a.out xv.txt 1
	-./a.out xv.txt 2
	-./a.out zo.txt 1
	-./a.out zo.txt 2

all_3: a.out
	-./a.out Arara4MaqPar.txt 3 1
	-./a.out Arara4MaqPar.txt 3 2
	-./a.out EN4MaqPar.txt 3 1 6
	-./a.out EN4MaqPar.txt 3 2
	-./a.out im.txt 3 1 6
	-./a.out im.txt 3 2
	-./a.out xv.txt 3 1 6
	-./a.out xv.txt 3 2
	-./a.out zo.txt 3 1 6
	-./a.out zo.txt 3 2
	-./a.out ap.txt 3 1 6
	-./a.out ap.txt 3 2
