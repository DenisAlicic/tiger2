CC=g++
CPPFLAGS=-std=c++17
LDFLAGS=

tiger: lex.yy.o parser.tab.o temp.o tree.o frame.o util.o symbol.o absyn.o assem.o types.o canon.o frag.o findescape.o translate.o errormsg.o mips.o semant.o
	$(CC) -o $@ $^ $(LDFLAGS)
lex.yy.o: lex.yy.c parser.tab.hpp
	$(CC) $(CPPFLAGS) -Wno-sign-compare -c -o $@ $<
lex.yy.c: lexer.lex
	flex $<
parser.tab.o: parser.tab.cpp parser.tab.hpp 
	$(CC) $(CPPFLAGS) -c -o $@ $<
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<
temp.o: temp.cpp temp.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<
tree.o: tree.cpp tree.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<
frame.o: frame.cpp frame.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<
util.o: util.cpp util.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<
symbol.o: symbol.cpp symbol.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<
absyn.o: absyn.cpp absyn.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<
assem.o: assem.cpp assem.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<
canon.o: canon.cpp canon.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<
types.o: types.cpp types.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<
frag.o: frag.cpp frag.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<
findescape.o: findescape.cpp findescape.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<
translate.o: translate.cpp translate.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<
errormsg.o: errormsg.cpp errormsg.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<
mips.o: mips.cpp mips.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<
semant.o: semant.cpp semant.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f *~ *.o lex.yy.c tiger *.output parser.tab.*


