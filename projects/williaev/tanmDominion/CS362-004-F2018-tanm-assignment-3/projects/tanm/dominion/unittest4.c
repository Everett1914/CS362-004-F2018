/*
 File: unittest4.c
 Don't forget to add a number at the command line for the seed
 Testing executed with player ones hand.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <string.h>
#include <stdlib.h>

int assertNumHandCards(int pHBefore, int pHAfter, int numDrawn){
  if(pHAfter == pHBefore + numDrawn){
    printf("numHandCards():  Pass-Function gets correct number of cards\n");
  }
  else{
    printf("numHandCards():  Fail-Function gets incorrect number of cards\n");
  }

  return 0;
}

int main (int argc, char** argv) {
  struct gameState G;
  int player0Hand1;
  int player0Hand2;
  int player1Hand1;
  int player1Hand2;
  int player = 0;  //first player
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  printf ("\nunittest4\n");
  printf ("Testing numHandCards Function:\n");
  printf ("-------------------------------\n");

  /***********************************************************************************************************/
  /*********************************Initialize Game State*****************************************************/
  initializeGame(2, k, atoi(argv[1]), &G);  //set up game (each player has 7 coopers and 3 estates this also sets and shuffles decks)
  printf("__________________________________________________________________________________________________________\n");
  printf("Test to see if the function gets correct # of handcards before and after a card is drawn the deck.\n");
  player0Hand1 = numHandCards(&G);
  drawCard(player, &G);
  player0Hand2 = numHandCards(&G);
  assertNumHandCards(player0Hand1, player0Hand2, 1);
  printf("____________________________________________________________________________________________________________________________\n");
  printf("Test to see if the function gets correct # of handcards before and after a card is drawn when the player is changed.\n");
  G.whoseTurn = 1;  //change to player 2
  player = 1;
  player1Hand1 = numHandCards(&G);
  drawCard(player, &G);
  player1Hand2 = numHandCards(&G);
  assertNumHandCards(player1Hand1, player1Hand2, 1);

  return 0;
}
