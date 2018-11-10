CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc  -o testme -g  testme.c  $(CFLAGS)

clean:
	rm -f *.gcov *.gcda *.gcno testme
