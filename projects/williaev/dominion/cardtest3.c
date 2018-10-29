/*
 File: cardtest3.c
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
  struct gameState testG1;
  int handpos = 0, choice1 = -1, choice2 = -1, choice3 = -1, bonus = -1;
  int player;
  int preVal1, preVal2, expectVal;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  printf ("\ncardtest3\n");
  printf ("Testing remodel card:\n");
  printf ("-------------------------------\n");

  /***********************************************************************************************************/
  /*********************************Initialize Game State*****************************************************/
  initializeGame(2, k, atoi(argv[1]), &G);  //set up game (each player has 7 coopers and 3 estates this also sets and shuffles decks)
  memcpy(&testG, &G, sizeof(struct gameState));
  memcpy(&testG1, &G, sizeof(struct gameState));

  player = 0;
  preVal1 = testG.handCount[player];
  preVal2 = testG.deckCount[player];
  choice1 = estate;
  choice2 = sea_hag;
  printf("______________________________________________________________________\n");
  printf("Test to see if hand count is properly updated after remodel is played.\n");
  cardEffect(remodel, choice1, choice2, choice3, &testG, handpos, &bonus);
  expectVal = 5;  //handcount should remain unchanged and discard should increase by one after playing remodel
  if(preVal1 == testG.handCount[player]){
    printf("remodel test:  Pass-Expected Value for hand count %d:  Result %d\n", expectVal, testG.handCount[player]);
  }
  else{
    printf("remodel test:  Fail-Expected Value for hand count %d:  Result %d\n", expectVal, testG.handCount[player]);
  }

  printf("______________________________________________________________________________\n");
  printf("Test to see if hand discard count is properly updated after remodel is played.\n");
  cardEffect(remodel, choice1, choice2, choice3, &testG, handpos, &bonus);
  expectVal = 1;  //handcount should remain unchanged and discard should increase by one after playing remodel
  if(preVal2 == testG.discardCount[player] + 1){
    printf("remodel test:  Pass-Expected Value for discard count %d:  Result %d\n", expectVal, testG.discardCount[player]);
  }
  else{
    printf("remodel test:  Fail-Expected Value for discard count %d:  Result %d\n", expectVal, testG.discardCount[player]);
  }

  printf("_________________________________________________________________\n");
  printf("Test to see if acquired card is worth more than the trashed card.\n");
  cardEffect(remodel, choice1, choice2, choice3, &testG, handpos, &bonus);
  expectVal = 1;  //handcount should remain unchanged and discard should increase by one after playing remodel
  if(getCost(choice1) + 2 <= testG.discard[player][testG.discardCount[player] - 1]){
    printf("remodel test:  Pass-Expected Value for new card >= %d\n", getCost(choice1) + 2);
  }
  else{
    printf("remodel test:  Fail-Expected Value for new card <= %d\n", getCost(choice1) + 2);
  }

  preVal1 = testG1.handCount[player];
  preVal2 = testG1.deckCount[player];
  choice1 = estate;
  choice2 = copper;
  printf("____________________________________________________________________________________________________________________________________\n");
  printf("The next set of tests evaluate what happens when the player attempts to exchange for a card that is less in value(estate for copper).\n");
  cardEffect(remodel, choice1, choice2, choice3, &testG, handpos, &bonus);
  expectVal = 5;  //handcount should remain unchanged and discard should increase by one after playing remodel
  if(preVal1 == testG.handCount[player]){
    printf("remodel test:  Pass-Expected Value for hand count %d:  Result %d\n", expectVal, testG.handCount[player]);
  }
  else{
    printf("remodel test:  Fail-Expected Value for hand count %d:  Result %d\n", expectVal, testG.handCount[player]);
  }

  printf("_____________________________________________________________________________ \n");
  printf("Test to see if hand discard count is properly updated after remodel is played.\n");
  cardEffect(remodel, choice1, choice2, choice3, &testG1, handpos, &bonus);
  expectVal = 1;  //handcount should remain unchanged and discard should increase by one after playing remodel
  if(preVal2 == testG1.discardCount[player] + 1){
    printf("remodel test:  Pass-Expected Value for discard count %d:  Result %d\n", expectVal, testG1.discardCount[player]);
  }
  else{
    printf("remodel test:  Fail-Expected Value for discard count %d:  Result %d\n", expectVal, testG1.discardCount[player]);
  }

  printf("_________________________________________________________________\n");
  printf("Test to see if acquired card is worth more than the trashed card.\n");
  cardEffect(remodel, choice1, choice2, choice3, &testG1, handpos, &bonus);
  expectVal = 1;  //handcount should remain unchanged and discard should increase by one after playing remodel
  if(getCost(choice1) + 2 <= testG1.discard[player][testG1.discardCount[player] - 1]){
    printf("remodel test:  Pass-Expected Value for new card >= %d\n", getCost(choice1) + 2);
  }
  else{
    printf("remodel test:  Fail-Expected Value for new card <= %d\n", getCost(choice1) + 2);
  }

  return 0;
}
