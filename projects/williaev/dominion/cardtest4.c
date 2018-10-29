/*
 File: cardtest4.c
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
  int player;
  int preVal1;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  printf ("\ncardtest4\n");
  printf ("Testing sea hag card:\n");
  printf ("-------------------------------\n");

  /***********************************************************************************************************/
  /*********************************Initialize Game State*****************************************************/
  initializeGame(2, k, atoi(argv[1]), &G);  //set up game (each player has 7 coopers and 3 estates this also sets and shuffles decks)
  memcpy(&testG, &G, sizeof(struct gameState));

  player = 1;
  preVal1 = testG.deckCount[player];
  printf("________________________________________________________________________________\n");
  printf("Test to see if opponents deck count is properly updated after sea_hag is played.\n");
  cardEffect(sea_hag, choice1, choice2, choice3, &testG, handpos, &bonus);
  if(testG.deckCount[player] == preVal1){
    printf("sea_hag test:  Pass-Expected Value %d:  Result %d\n", preVal1, testG.deckCount[player]);
  }
  else{
    printf("sea_hag test:  Fail-Expected Value %d:  Result %d\n", preVal1, testG.deckCount[player]);
  }

  printf("______________________________________________________________________________________________________\n");
  printf("Test to see if opponents deck contains a curse given the deck initially only had coppers and estates.\n");
  if(testG.deck[player][testG.deckCount[player] -1] == curse){
    printf("sea_hag test:  Pass-opponent has a Sea Hag at the top of their deck\n");
  }
  else{
    printf("sea_hag test:  Fail-opponent does not have a Sea Hag at the top of their deck\n");
  }

  return 0;
}
