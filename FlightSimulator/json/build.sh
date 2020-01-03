bison -d cyrus-reader.ypp
flex cyrus-lex.l
gcc -c lex.yy.c -g
g++ -c cyrus-reader.tab.cpp -g
g++ -c converter.cpp -g
g++ -g converter.o lex.yy.o cyrus-reader.tab.o -o cyrus-reader