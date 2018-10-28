/*
 File: unittest1.c
 Don't forget to add a number at the command line for the seed
 Testing executed with player ones hand.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <string.h>
#include <stdlib.h>

int assertDrawCard(struct gameState *state, int initH, int initD, int player, int numDrawn){
  if((state->handCount[player] == initH + numDrawn) && (state->deckCount[player] == initD - numDrawn)){
    printf("drawCard():  Pass-Initial # of hand cards %d.  After %d cards drawn hand contains %d cards.\n", initH, numDrawn, state->handCount[player]);
    printf("drawCard():  Pass-Initial # of deck cards %d.  After %d cards drawn deck contains %d cards.\n", initD, numDrawn, state->deckCount[player]);
  }
  else{
    printf("drawCard():  Fail-Initial # of hand cards %d.  After %d cards drawn hand contains %d cards.\n", initH, numDrawn, state->handCount[player]);
    printf("drawCard():  Fail-Initial # of deck cards %d.  After %d cards drawn deck contains %d cards.\n", initD, numDrawn, state->deckCount[player]);
  }
  return 0;
}

int main (int argc, char** argv) {
  struct gameState G;
  struct gameState G1;
  struct gameState G2;
  int i, j, numDrawn, initH, initD, numDiscardCards;
  int player = 0;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  printf ("\nunittest1\n");
  printf ("Testing drawCard Function:\n");
  printf ("-------------------------------\n");

  /***********************************************************************************************************/
  /*********************************Initialize Game State*****************************************************/
  initializeGame(2, k, atoi(argv[1]), &G);  //set up game (each player has 7 coopers and 3 estates this also sets and shuffles decks)
  initializeGame(2, k, atoi(argv[1]), &G1);
  initializeGame(2, k, atoi(argv[1]), &G2);

  /****************************************************************************************************************/
  /********Test to see if the function correctly adds a card to the players hand if the deck is not empty.*********/
  printf("____________________________________________________________________________________________________________________\n");
  printf("Test to see if the function correctly adds cards to the players hand if the deck is not empty and discard is empty.\n");
  printf("Expect this test to pass.\n");
  initH = G.handCount[player];  //Since starting from initial game, initialize handcount to 5
  initD = G.deckCount[player];  //note that initialization automatically executes draw card so only five in deck at start of game.
  numDrawn = 4;  //number of cards to draw
  for (j = 0; j < numDrawn; j++){ //draw cards for first player
    drawCard(player, &G);
  }
  assertDrawCard(&G, initH, initD, player, numDrawn);

  /****************************************************************************************************************/
  /********Test to see if the function correctly adds a card to the players hand if the deck is not empty.*********/
  printf("___________________________________________________________________________________________________________________\n");
  printf("Test to see if the function correctly adds cards to the players hand if the deck is not empty and discard is empty.\n");
  printf("Since discard is empty and we are attempting to draw more than is in the deck expect this test to fail.\n");
  initH = G2.handCount[player];  //Since starting from initial game, initialize handcount to 5
  initD = G2.deckCount[player];  //note that initialization automatically executes draw card so only five in deck at start of game.
  numDrawn = 7;  //number of cards to draw
  for (j = 0; j < numDrawn; j++){ //draw cards for first player
    drawCard(player, &G2);
  }
  assertDrawCard(&G2, initH, initD, player, numDrawn);

  /****************************************************************************************************************************************/
  /********Test to see if the function correctly adds a card to the players hand if the deck and discard are not empty*********************/
  printf("___________________________________________________________________________________________________________\n");
  printf("Test to see if the function correctly adds cards to the players hand if the deck and discard are not empty.\n");
  printf("This test draws more than is in the deck forcing us to use the discard pile.  Expect this test to pass.\n");
  initH = G1.handCount[player];  //Since starting from initial game, initialize handcount to 5
  initD = G1.deckCount[player];  //note that initialization automatically executes draw card so only five in deck at start of game.
  numDiscardCards = 10;
  G1.discardCount[0] = 0;
  for (i = 0; i < numDiscardCards; i++) {  //create a discard deck of 10 coppers
       G1.discard[0][i] = copper;
       G1.discardCount[player]++;
  }
  numDrawn = 8;  //number of cards to draw
  for (j = 0; j < numDrawn; j++){ //draw cards for first player
    drawCard(player, &G1);
  }
  if(initD < numDrawn){
    initD = numDiscardCards + initD;
  }
  assertDrawCard(&G1, initH, initD, player, numDrawn);

  return 0;
}
