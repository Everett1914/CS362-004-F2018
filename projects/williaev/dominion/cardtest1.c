/*
 File: cardtest1.c
 Don't forget to add a number at the command line for the seed
 Testing executed with player ones hand.
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
  int player, i, change;
  int expectVal;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  printf ("\ncardtest1\n");
  printf ("Testing smithy card:\n");
  printf ("-------------------------------\n");

  /***********************************************************************************************************/
  /*********************************Initialize Game State*****************************************************/
  initializeGame(2, k, atoi(argv[1]), &G);  //set up game (each player has 7 coopers and 3 estates this also sets and shuffles decks)
  memcpy(&testG, &G, sizeof(struct gameState));

  printf("______________________________________________________________\n");
  printf("Test to see if hand is adjusted properly after playing smithy.\n");
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
  player = 0;
  expectVal = 8;  //intialization leaves 5 cards in hand so smithy should add 3.
  if(G.handCount[player] == expectVal){
    printf("smithy test:  Pass-Expected value %d:  Result %d\n", expectVal, testG.handCount[player]);
  }
  else{
    printf("smithy test:  Fail-Expected value %d:  Result %d\n", expectVal, testG.handCount[player]);
  }

  printf("______________________________________________________________\n");
  printf("Test to see if deck is adjusted properly after playing smithy.\n");
  expectVal = 2;  //intialization leaves 5 cards in deck so smithy should remove 3.
  if(G.deckCount[player] == expectVal){
    printf("smithy test:  Pass-Expected value %d:  Result %d\n", expectVal, testG.deckCount[player]);
  }
  else{
    printf("smithy test:  Fail-Expected value %d:  Result %d\n", expectVal, testG.deckCount[player]);
  }

  printf("________________________________________________________________________\n");
  printf("Test to ensure opponents hand is not changed after playing smithy.\n");
  player = 1;
  expectVal = 0;  //intialization leaves 5 cards in hand so smithy should add 3.
  if(G.handCount[player] == expectVal){
    printf("smithy test:  Pass-Expected value %d:  Result %d\n", expectVal, testG.handCount[player]);
  }
  else{
    printf("smithy test:  Fail-Expected value %d:  Result %d\n", expectVal, testG.handCount[player]);
  }

  printf("______________________________________________________________\n");
  printf("Test to ensure opponents deck is not changed after playing smithy.\n");
  expectVal = 10;  //intialization leaves 5 cards in deck so smithy should remove 3.
  if(G.deckCount[player] == expectVal){
    printf("smithy test:  Pass-Expected value %d:  Result %d\n", expectVal, testG.deckCount[player]);
  }
  else{
    printf("smithy test:  Fail-Expected value %d:  Result %d\n", expectVal, testG.deckCount[player]);
  }
  printf("__________________________________________________________________________\n");
  printf("Test to check if victory card states haven't changed after playing smithy.\n");
  expectVal = 8;
  if(testG.supplyCount[estate] == expectVal && testG.supplyCount[duchy] == expectVal && testG.supplyCount[province] == expectVal){
    printf("smithy test:  Pass-Expected value estate %d:  Result %d\n", expectVal, testG.supplyCount[estate]);
    printf("smithy test:  Pass-Expected value duchy %d:  Result %d\n", expectVal, testG.supplyCount[duchy]);
    printf("smithy test:  Pass-Expected value province %d:  Result %d\n", expectVal, testG.supplyCount[province]);
  }
  else{
    printf("smithy test:  Fail-Expected value estate %d:  Result %d\n", expectVal, testG.supplyCount[estate]);
    printf("smithy test:  Fail-Expected value duchy %d:  Result %d\n", expectVal, testG.supplyCount[duchy]);
    printf("smithy test:  Fail-Expected value province %d:  Result %d\n", expectVal, testG.supplyCount[province]);
  }

  printf("__________________________________________________________________________\n");
  printf("Test to check if kingdom card states haven't changed after playing smithy.\n");
  expectVal = 10;
  change = 0;
  for(i = 0; i < 10; i++){
    if(k[i] <= adventurer && k[i] > treasure_map){
      change = 1;
    }
  }

  if(change == 0){
    printf("smithy test:  Pass-No change to the state of the kingdom cards\n");
  }
  else{
    printf("smithy test:  Fail-Detected a change to the state of the kingdom cards\n");;
  }

  return 0;
}
