executar: arquivos_prog/a.out
ifdef WEB		#Executa server
	make web
endif

ifdef PROG		#Executa programa	
	make prog
endif

web: arquivos_prog/a.out codigo_interface/web.py
	python codigo_interface/web.py

prog: arquivos_prog/a.out codigo_interface/prog.py
	python codigo_interface/prog.py

limpar:
	-rm codigo_c_plus_plus/*.h.gch
	-rm arquivos_prog/a.out

remover:
	make limpar
	rm desenhos/*
	rm outros/*
	rm aneis/*

arquivos_prog/a.out: codigo_c_plus_plus/*.h codigo_c_plus_plus/*.cpp
	make compilar

compilar: codigo_c_plus_plus/*.h codigo_c_plus_plus/*.cpp
	g++ -o arquivos_prog/a.out -O3 -pthread -std=c++11 codigo_c_plus_plus/*.h codigo_c_plus_plus/*.cpp

debug: codigo_c_plus_plus/*.h codigo_c_plus_plus/*.cpp
	g++ -o arquivos_prog/a.out -g -O3 -pthread -std=c++11 codigo_c_plus_plus/*.h codigo_c_plus_plus/*.cpp

dot: desenhos/*.dot
	dot -Tpdf -O desenhos/*.dot

compilar_windows: codigo_c_plus_plus/*.h codigo_c_plus_plus/*.cpp
	g++ -o arquivos_prog/a.exe -O3 -pthread -std=c++11 codigo_c_plus_plus/*.h codigo_c_plus_plus/*.cpp

prog_windows: arquivos_prog/a.exe codigo_interface/prog.py
	python codigo_interface/prog.py

escience: arquivos_prog/a.out
	-./arquivos_prog/a.out entrada/Arara4MaqPar.txt 1 8 20 10 0
	-./arquivos_prog/a.out entrada/Arara4MaqPar.txt 1 8 20 10 1
	-./arquivos_prog/a.out entrada/Arara4MaqPar.txt 1 8 20 10 2
	-./arquivos_prog/a.out entrada/Arara4MaqPar.txt 2 8 20 10 0
	-./arquivos_prog/a.out entrada/Arara4MaqPar.txt 2 8 20 10 1
	-./arquivos_prog/a.out entrada/Arara4MaqPar.txt 2 8 20 10 2	
	-./arquivos_prog/a.out entrada/mbya.txt 1 8 20 10 0
	-./arquivos_prog/a.out entrada/mbya.txt 1 8 20 10 1
	-./arquivos_prog/a.out entrada/mbya.txt 1 8 20 10 2
	-./arquivos_prog/a.out entrada/mbya.txt 2 8 20 10 0
	-./arquivos_prog/a.out entrada/mbya.txt 2 8 20 10 1
	-./arquivos_prog/a.out entrada/mbya.txt 2 8 20 10 2	
	-./arquivos_prog/a.out entrada/EN4MaqPar.txt 1 8 20 10 0
	-./arquivos_prog/a.out entrada/EN4MaqPar.txt 1 8 20 10 1
	-./arquivos_prog/a.out entrada/EN4MaqPar.txt 1 8 20 10 2
	-./arquivos_prog/a.out entrada/EN4MaqPar.txt 2 8 20 10 0
	-./arquivos_prog/a.out entrada/EN4MaqPar.txt 2 8 20 10 1
	-./arquivos_prog/a.out entrada/EN4MaqPar.txt 2 8 20 10 2
	./arquivos_prog/a.out entrada/Arara4MaqPar.txt 3 8 20 10 0
	./arquivos_prog/a.out entrada/Arara4MaqPar.txt 3 8 20 10 1
	./arquivos_prog/a.out entrada/Arara4MaqPar.txt 3 8 20 10 2
	./arquivos_prog/a.out entrada/mbya.txt 3 8 20 10 0
	./arquivos_prog/a.out entrada/mbya.txt 3 8 20 10 1
	./arquivos_prog/a.out entrada/mbya.txt 3 8 20 10 2
	./arquivos_prog/a.out entrada/EN4MaqPar.txt 3 8 20 10 0
	./arquivos_prog/a.out entrada/EN4MaqPar.txt 3 8 20 10 1
	./arquivos_prog/a.out entrada/EN4MaqPar.txt 3 8 20 10 2