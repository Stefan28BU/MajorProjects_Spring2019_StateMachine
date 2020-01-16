CFLAGS= -O

CFILES=SMClass.cpp globals.cpp Main.cpp

GENCFILES=lex.yy.cpp y.tab.cpp y.tab.h

OFILES=SMClass.o lex.yy.o y.tab.o globals.o Main.o


Parser: $(OFILES)
	g++ $(CFLAGS) $(OFILES) -o Parser

$(OFILES): SMClass.h y.tab.h globals.h

y.tab.cpp y.tab.h: SM.yacc
	yacc -d SM.yacc
	mv y.tab.c y.tab.cpp

lex.yy.cpp: SM.lex
	lex SM.lex
	mv lex.yy.c lex.yy.cpp

.cpp.o:
	g++ -c $(CFLAGS) $*.cpp

clean:
	rm -f $(OFILES) $(GENCFILES) Parser

bulk:
	wc -l $(CFILES) SM.lex SM.yacc globals.h
