NAME0 = interpreter
NAME1 = kompilator


goal: $(NAME0) $(NAME1)
	@echo "OK"
	
$(NAME0) $(NAME1): y.tab.o lex.yy.o $(NAME0).o $(NAME1).o
	cc -o $(NAME0)  y.tab.o lex.yy.o $(NAME0).o -ll -ly
	cc -o $(NAME1)  y.tab.o lex.yy.o $(NAME1).o -ll -ly

y.tab.c y.tab.h: gramm.y
	yacc -dv gramm.y

lex.yy.c: scan.l y.tab.h
	lex scan.l

.c.o:	
	cc -c $<

clean: 
	rm -f *~ *.[Bb][Aa][Kk] *.o y.tab.[ch] y.output lex.yy.c $(NAME0) $(NAME1)
