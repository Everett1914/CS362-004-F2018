/*
 File: unittest3.c
 Don't forget to add a number at the command line for the seed
 Testing executed with player ones hand.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <string.h>
#include <stdlib.h>

int cmpfunc (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

int assertShuffle(int originalArr[], int shuffledArr[], int player, struct gameState *state){
  int result0;
  int result1;
  int i;
  result0 = 0;  //assume array is shuffled
  for(i = 0; i < state->deckCount[player]; i++){ //copy of array after shuffle
    printf("Original: %d\n", originalArr[i]);
    printf("Shuffled: %d\n", shuffledArr[i]);
    if(originalArr[i] != shuffledArr[i]){  //arrays are not in same order
      result0 = 1;
    }
  }
  if(result0 == 0){ //arrays are the same in terms of order and elements
    printf("shuffle():  Fail-Deck was not shuffled\n");
  }
  else{ //arrays are arranged differently so check to see arrays contain the same elements if true the original deck was properly shuffled.
    qsort(originalArr, state->deckCount[player], sizeof(int), cmpfunc);  //https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
    qsort(shuffledArr, state->deckCount[player], sizeof(int), cmpfunc);
    result1 = 0;  //assume arrays are the same
    for(i = 0; i < state->deckCount[player]; i++){
      if(originalArr[i] != shuffledArr[i]){ //arrays contain different elements
        result1 = 1;
      }
    }
    if(result1 == 0){
      printf("shuffle():  Pass-deck was shuffled\n");
    }
    else{
      printf("shuffle():  Fail-decks contain different elements\n");
    }
  }
  return 0;
}

int main (int argc, char** argv) {
  struct gameState G;
  int i;
  int testDeck0[MAX_DECK];
  int testDeck1[MAX_DECK];
  int testDeckCount;
  int player = 0;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  printf ("\nunittest3\n");
  printf ("Testing shuffle Function:\n");
  printf ("-------------------------------\n");

  /***********************************************************************************************************/
  /*********************************Initialize Game State*****************************************************/
  initializeGame(2, k, atoi(argv[1]), &G);  //set up game (each player has 7 coopers and 3 estates this also sets and shuffles decks)
  printf("________________________________________________________\n");
  printf("Test to see if the function correctly shuffles the deck.\n");
  printf("If shuffle is working expect this result to pass.\n");
  testDeckCount = G.deckCount[player];
  for(i = 0; i < testDeckCount; i++){ //copy of array before shuffle
    testDeck0[i] = G.deck[player][i];
  }
  shuffle(player, &G);  //shuffle original array
  for(i = 0; i < testDeckCount; i++){ //copy of array after shuffle
    testDeck1[i] = G.deck[player][i];
  }
  assertShuffle(testDeck0, testDeck1, player, &G);  //test to see if test and original arrays are the same
  printf("___________________________________________________________________________\n");
  printf("Since shuffle is not working this is a test to verify the test coding.\n");
  printf("Arrays are the same, but arranged differently.  Expect this result to pass.\n");
  int testDeck2[5] = {0, 1, 3, 4, 8};
  int testDeck3[5] = {1, 0, 4, 3, 8};
  assertShuffle(testDeck2, testDeck3, player, &G);
  printf("_________________________________________________________________________________\n");
  printf("Since shuffle is not working this is a test to verify the test coding.\n");
  printf("In this test arrays are the same size but different.  Expect this result to fail.\n");
  int testDeck4[5] = {7, 0, 5, 3, 8};
  int testDeck5[5] = {6, 0, 5, 3, 8};
  assertShuffle(testDeck4, testDeck5, player, &G);
  return 0;
}
