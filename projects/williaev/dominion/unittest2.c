/*
 File: unittest2.c
 Don't forget to add a number at the command line for the seed

 */

#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int assertTrue(struct gameState *state, int searchCard, int tgt){
  int count = fullDeckCount(1, searchCard, state);
  if (count == tgt){
    printf("FullDeckCount(): Pass-target count(%d) for specific card matches actual number of a specific card in Hand, Deck and Discard (%d).\n", tgt, count);
  }
  else{
    printf("FullDeckCount(): Fail-target count (%d) for specific card doesn't match actual number of a specific card Hand, Deck and Discard (%d).\n", tgt, count);
  }
  return 0;
}

int main (int argc, char** argv) {
  struct gameState G;
  int i, j, tgt1;
  int upper = 9;
  int lower = 0;
  int ranNum[3];
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  printf ("\nunittest2\n");
  printf ("Testing fullDeckCount Function:\n");
  printf ("-------------------------------\n");

  /***********************************************************************************************************/
  /*********************************Initialize Game State*****************************************************/
  initializeGame(2, k, atoi(argv[1]), &G);  //set up game (each player has 7 coopers and 3 estates)

  for (i = 0; i < 3; i++) {
    int num = (rand() % (upper - lower + 1)) + lower;  //create random positions in each array for sought card
       ranNum[i] = num;
  }

  for (i = 0; i < G.numPlayers; i++){  //Build deck
      G.deckCount[i] = 0;
      for (j = 0; j < 10; j++){  //create deck - 10 coppers to each deck and increase by deckcount
        G.deck[i][j] = copper;
        G.deckCount[i]++;  //number of cards in the deck
      }
      G.deck[i][ranNum[0]] = silver;
  }

  for (i = 0; i < G.numPlayers; i++){  //Build discard
      G.discardCount[i] = 0;
      for (j = 0; j < 10; j++){  //create deck - 10 coppers to each deck and increase by deckcount
        G.discard[i][j] = copper;
        G.discardCount[i]++;  //number of cards in the deck
      }
      G.discard[i][ranNum[1]] = silver;
  }

  for (i = 0; i < G.numPlayers; i++){  //Build hand
      G.handCount[i] = 0;
      for (j = 0; j < 10; j++){  //create deck - 10 coppers to each deck and increase by deckcount
        G.hand[i][j] = copper;
        G.handCount[i]++;  //number of cards in the deck
      }
      G.hand[i][ranNum[2]] = silver;
  }

  /****************************************************************************************************************/
  /*Test to see if the function correct calculates the total number of a specfic card in a given players hand, deck,
  and discard pile.*/
  printf("_____________________________\n");
  printf("Test for Correct Card Number.\n");
  tgt1 = 3;
  assertTrue(&G, silver, tgt1);  //Test Correct Card Count
  tgt1 = 12;
  assertTrue(&G, silver, tgt1);  //Test Incorrect Card count

  /****************************************************************************************************************/
  /*Test to see if the function returns a count of zero if the card does not exist in the deck, hand, and discard piles*/
  printf("_________________________________________________________\n");
  printf("Test for when card is not in deck, hand or discard piles.\n");
  tgt1 = 0;
  assertTrue(&G, gold, tgt1);  //Correctly catches when card does not exist
  tgt1 = 10;
  assertTrue(&G, gold, tgt1);  //fails to catch when card does not exist

  /****************************************************************************************************************/
  /*Test to see if the function executes correctly if either discard, hand, or deck is empty*/
  for (i = 0; i < G.numPlayers; i++){  //Build deck
      G.deckCount[i] = 0;
      for (j = 0; j < 10; j++){  //create deck - 10 coppers to each deck and increase by deckcount
        G.deck[i][j] = 50;
        G.deckCount[i]++;  //number of cards in the deck
      }
  }
  printf("___________________________________________________________\n");
  printf("Test for when either deck, hand or discard piles are empty.\n");
  tgt1 = 2;
  assertTrue(&G, silver, tgt1);  //Test Correct Card Count
  tgt1 = 12;
  assertTrue(&G, silver, tgt1);  //Test Incorrect Card count

  return 0;
}
