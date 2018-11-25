CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

#myTestUtilities: dominion.o rngs.o
#	gcc -o myTestUtilities myTestUtilities.c -g dominion.o rngs.o $(CFLAGS)

unittest1: dominion.o unittest1.c myTestUtilities.c rngs.o
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o myTestUtilities.c $(CFLAGS)

unittest2: dominion.o unittest2.c myTestUtilities.o rngs.o
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o myTestUtilities.c $(CFLAGS)

unittest3: dominion.o unittest3.c myTestUtilities.o rngs.o
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o myTestUtilities.c $(CFLAGS)

unittest4: dominion.o unittest4.c myTestUtilities.o rngs.o
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o myTestUtilities.c $(CFLAGS)

cardtest1: dominion.o cardtest1.c myTestUtilities.o rngs.o
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o myTestUtilities.c $(CFLAGS)

cardtest2: dominion.o cardtest2.c myTestUtilities.o rngs.o
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o myTestUtilities.c $(CFLAGS)

cardtest3: dominion.o cardtest3.c myTestUtilities.o rngs.o
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o myTestUtilities.c $(CFLAGS)

cardtest4: dominion.o cardtest4.c myTestUtilities.o rngs.o
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o myTestUtilities.c $(CFLAGS)

unittestresults: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 dominion.o
	./unittest1 1>&2 unittestresults.out
	gcov unittest1.c -b >> unittestresults.out 2>&1
	./unittest2 >> unittestresults.out 2>&1
	gcov unittest2.c -b >> unittestresults.out 2>&1
	./unittest3 >> unittestresults.out 2>&1
	gcov unittest3.c -b >> unittestresults.out 2>&1
	./unittest4 >> unittestresults.out 2>&1
	gcov unittest4.c -b >> unittestresults.out 2>&1
	./cardtest1 >> unittestresults.out 2>&1
	gcov cardtest1.c -b >> unittestresults.out 2>&1
	./cardtest2 >> unittestresults.out 2>&1
	gcov cardtest2.c -b >> unittestresults.out 2>&1
	./cardtest3 >> unittestresults.out 2>&1
	gcov cardtest3.c -b >> unittestresults.out 2>&1
	./cardtest4 >> unittestresults.out 2>&1
	gcov cardtest4.c -b >> unittestresults.out 2>&1

uresults: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	echo "Result for running dominion tests:" > unittestresults.out
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1 7 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 7 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 7 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 7 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardtest1 7 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2 7 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3 7 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4 7 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 unittestresults cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard1 randomtestcard2 randomtestadventurer
