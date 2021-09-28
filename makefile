executar: a.out
ifdef NOME		#Nome da rede de entrada entrada/$(NOME).txt
ifdef NUMERO	#Número de anéis
ifdef TIPO		#Tipo de Execucao, 0 = todas, 1 = A1LSC, 2 = A1LCC, 3 = A1P, 4 = A2L, 5 = A2P, 6 = A3, 7 = funções
ifdef GRAO		#Tamanho do grao em buscas paralelas
ifdef THREADS	#Maior número de threads possível em buscas paralelas
	./a.out $(NOME) $(NUMERO) $(TIPO) $(GRAO) $(THREADS)
else
	./a.out $(NOME) $(NUMERO) $(TIPO) $(GRAO)
endif
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

dot: desenhos/*.dot
	dot -Tpdf -O desenhos/*.dot
