executar: *.h *.cpp
	make compilar
ifdef NOME
ifdef NUMERO
	./a.out $(NOME) $(NUMERO)
else
	./a.out $(NOME)
endif
else
	./a.out
endif


limpar:
	rm *.h.gch
	rm a.out
	rm entrada/*.dot

compilar:
	g++ -O3 -std=c++11 *.h *.cpp
	
dot: entrada/*.dot
	dot -Tpdf -O desenhos/*.dot
