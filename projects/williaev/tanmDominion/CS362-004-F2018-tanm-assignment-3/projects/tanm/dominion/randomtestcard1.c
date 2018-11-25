#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//machine for assert results, compares deck, discard, and hand numbers of pre and post states.
int assertTrue(int preHand, int preDeck, int preDiscard, int postHand, int postDeck, int postDiscard){
  int preTotal = preHand + preDeck + preDiscard;
  int postTotal = preHand + postDeck + postDiscard;
  if(postHand == preHand && preTotal == postTotal && abs(preHand - postHand) <= 2){  //return 1 (true) if the size of the hands of both decks are the same and total number of cards in deck/hand/discard is the same
    return 1;
  }
  else{
    return 0;
  }
}

int checkSmithyCard(int handPos, int p, struct gameState *pre, struct gameState *post){
  int numDrawn = 3;
  for (int i = 0; i < numDrawn; i++){  //execute drawcard for three cards as stated in business rules
     drawCard(p, pre);
  }
  discardCard(handPos, p, pre, 0);
  if (assertTrue(pre->handCount[p], pre->deckCount[p], pre->discardCount[p], post->handCount[p], post->deckCount[p], post->discardCount[p])){
    //printf("Passed: %d change in size of hand and size of total number of cards for player\n", pre->handCount[p] - post->handCount[p]);
  }
  else{
    //printf("Failed: %d change in size of hand and size of total number of cards for player\n", pre->handCount[p] - post->handCount[p]);  //expect all test to fail because of added bug that cause code to draw 2 instead of 3 cards
  }
  return 0;
}

int main () {

  int i, n, p, smithyPos0, smithyPos1, smithyPos;
  int bonus = -1;
  struct gameState pre;
  struct gameState post;

  printf("____________________\n");
  printf ("Testing SmithyCard.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 20000; n++) {  //create random test state for the game.
    printf("test#: %d\n", n);
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&pre)[i] = floor(Random() * 256);
    }
    //Create random deck, hand, discard, and played piles
    for(int p = 0; p < 2; p++){
      pre.deckCount[p] = floor(Random() * MAX_DECK);
      for(i = 0; i < pre.deckCount[p]; i++){
        pre.deck[p][i]=floor(Random() * 26);
      }
      pre.discardCount[p] = floor(Random() * MAX_DECK);
      for(i = 0; i < pre.discardCount[p]; i++){
        pre.discard[p][i]=floor(Random() * 26);
      }
      pre.handCount[p] = floor(Random() * MAX_HAND);
      for(i = 0; i < pre.handCount[p]; i++){
        pre.hand[p][i]=floor(Random() * 26);
      }
      if(p == 0){
        smithyPos0 = floor(Random() * pre.handCount[p]); //ensure a smithy is in the hand to be played player 1
        pre.hand[p][smithyPos0]=smithy;
      }
      else{
        smithyPos1 = floor(Random() * pre.handCount[p]); //ensure a smithy is in the hand to be played player 2
        pre.hand[p][smithyPos1]=smithy;
      }
    }
    pre.playedCardCount = floor(Random() * MAX_DECK); //set up played deck
    for(i = 0; i < pre.playedCardCount; i++){
      pre.playedCards[i]=floor(Random() * 26);
    }
    pre.numPlayers = 2;
    pre.whoseTurn = floor(Random() * 2);  //set up turn and select correct handPos=cutPursPos for player
    p = pre.whoseTurn;
    if(pre.whoseTurn == 0){
      smithyPos = smithyPos0;
    }
    else{
      smithyPos = smithyPos1;
    }
    memcpy (&post, &pre, sizeof(struct gameState));
    cardEffect(smithy, -1, -1, -1, &post, smithyPos, &bonus);
    checkSmithyCard(smithyPos, p, &pre, &post);
  }

  printf ("SIMPLE FIXED TESTS.\n");  //Test to see if drawCard draws from discard when deck is empty
  p = 0;
  for(i = 0; i < pre.deckCount[p]; i++){
    pre.deck[p][i]=-1;
  }
  pre.deckCount[p] = 0;
  pre.deckCount[p] = floor(Random() * MAX_DECK);
  for(i = 0; i < pre.deckCount[p]; i++){
    pre.deck[p][i]=floor(Random() * 26);
  }
  pre.discardCount[p] = floor(Random() * MAX_DECK);
  for(i = 0; i < pre.discardCount[p]; i++){
    pre.discard[p][i]=floor(Random() * 26);
  }
  pre.handCount[p] = floor(Random() * MAX_HAND);
  for(i = 0; i < pre.handCount[p]; i++){
    pre.hand[p][i]=floor(Random() * 26);
  }
  pre.playedCardCount = floor(Random() * MAX_DECK); //set up played deck
  for(i = 0; i < pre.playedCardCount; i++){
    pre.playedCards[i]=floor(Random() * 26);
  }
  smithyPos0 = floor(Random() * pre.handCount[p]); //ensure a smithy is in the hand to be played player 1
  pre.hand[p][smithyPos0]=smithy;
  memcpy (&post, &pre, sizeof(struct gameState));
  cardEffect(smithy, -1, -1, -1, &post, -1, &bonus);
  checkSmithyCard(smithyPos, p, &pre, &post);

  return 0;
}
