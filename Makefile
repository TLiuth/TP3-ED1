all: tp.o arvore.o impressao.o
	@gcc tp.o arvore.o impressao.o -o exe
	@rm tp.o arvore.o impressao.o
tp.o: tp.c
	@gcc tp.c -c
arvore.o: arvore.c
	@gcc arvore.c -c
impressao.o: impressao.c
	@gcc impressao.c -c
run:
	@./exe
