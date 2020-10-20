executar: *.h *.cpp
	make compilar
	./a.out

limpar:
	rm *.h.gch
	rm a.out
	rm entrada/*.dot
	rm entrada/*.pdf

compilar:
	g++ -std=c++11 *.h *.cpp
	
dot: entrada/*.dot
	dot -Tpdf -O entrada/*.dot