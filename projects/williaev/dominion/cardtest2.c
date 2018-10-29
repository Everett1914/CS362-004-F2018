/*
 File: cardtest2.c
 Don't forget to add a number at the command line for the seed
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <string.h>
#include <stdlib.h>

int main (int argc, char** argv) {
  struct gameState G;
  struct gameState testG;
  int handpos = 0, choice1 = -1, choice2 = -1, choice3 = -1, bonus = -1;
  int player, totalCards;
  int expectVal, preVal;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  printf ("\ncardtest2\n");
  printf ("Testing adventurer card:\n");
  printf ("-------------------------------\n");

  /***********************************************************************************************************/
  /*********************************Initialize Game State*****************************************************/
  initializeGame(2, k, atoi(argv[1]), &G);  //set up game (each player has 7 coopers and 3 estates this also sets and shuffles decks)
  memcpy(&testG, &G, sizeof(struct gameState));

  expectVal = 10;  //Player starts with 10 cards so expect deck+hand+discard = 10 is the player has 5 deck and 5 hand cards
  player = 0;
  preVal = testG.handCount[player];
  printf("______________________________________________________________________________________\n");
  printf("Test to see if hand, deck and discard are properly updated after adventurer is played.\n");
  printf("adventurer test:  Pile values before playing adventurer\n");
  printf("adventurer test:  discard: %d  deck: %d  hand: %d\n", testG.discardCount[player], testG.deckCount[player], testG.handCount[player]);
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus); //play adventurerPos
  totalCards = testG.handCount[player] + testG.deckCount[player] + testG.discardCount[player];
  if(totalCards == expectVal){
    if(testG.handCount[player] - preVal > 2){  //Fail hand pile should not increase by more than 2
      printf("adventurer test:  Fail-Hand increased by more than 2 cards\n");
      printf("adventurer test:  discard: %d  deck: %d  hand: %d\n", testG.discardCount[player], testG.deckCount[player], testG.handCount[player]);
    }
    else{  //Pass hand pile increased by at most 2
      printf("adventurer test:  Pass-Expected value %d:  Result %d\n", expectVal, totalCards);
      printf("adventurer test:  discard: %d  deck: %d  hand: %d\n", testG.discardCount[player], testG.deckCount[player], testG.handCount[player]);
    }
  }
  else{
    printf("adventurer test:  Fail-Expected value %d:  Result %d\n", expectVal, totalCards);
    printf("adventurer test:  discard: %d  deck: %d  hand: %d\n", testG.discardCount[player], testG.deckCount[player], testG.handCount[player]);
  }

  return 0;
}
