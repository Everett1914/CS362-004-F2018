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
  if(postHand == preHand && preTotal == postTotal){  //return 1 (true) if the size of the hands of both decks are the same and total number of cards in deck/hand/discard is the same
    return 1;
  }
  else{
    return 0;
  }
}

int checkSmithyCard(int p, struct gameState *pre, struct gameState *post){
  int numDrawn = 3;
  int ogHandCount = pre->handCount[p];
  int newHandCount = post->handCount[p];
  for (int i = 0; i < numDrawn; i++){  //execute drawcard for three cards as stated in business rules
     drawCard(p, pre);
  }
  if (assertTrue(pre->handCount[p], pre->deckCount[p], pre->discardCount[p], post->handCount[p], post->deckCount[p], post->discardCount[p])){
    printf("Passed: %d cards added to the hand\n", newHandCount - ogHandCount);
  }
  else{
    printf("Failed: %d cards added to the hand\n", newHandCount - ogHandCount);  //expect all test to fail because of added bug that cause code to draw 2 instead of 3 cards
  }
  return 0;
}

int main () {

  int i, n, p;
  int bonus = -1;
  struct gameState pre;
  struct gameState post;

  printf("____________________\n");
  printf ("Testing SmithyCard.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 20; n++) {  //create random test state for the game.
    printf("test#: %d\n", n);
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&pre)[i] = floor(Random() * 256);
    }

    //Create random deck, hand, and discard
    p = floor(Random() * 2);
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
    pre.whoseTurn = p;
    memcpy (&post, &pre, sizeof(struct gameState));
    cardEffect(smithy, -1, -1, -1, &post, -1, &bonus);
    checkSmithyCard(p, &pre, &post);
  }

  printf ("SIMPLE FIXED TESTS.\n");  //Test to see if drawCard draws from discard when deck is empty
  pre.deckCount[p] = 0;
  for(i = 0; i < pre.deckCount[MAX_DECK]; i++){
    pre.deck[p][i]=-1;
  }
  pre.discardCount[p] = floor(Random() * MAX_DECK);
  for(i = 0; i < pre.discardCount[p]; i++){
    pre.discard[p][i]=floor(Random() * 26);
  }
  pre.handCount[p] = floor(Random() * MAX_HAND);
  for(i = 0; i < pre.handCount[p]; i++){
    pre.hand[p][i]=floor(Random() * 26);
  }
  memcpy (&post, &pre, sizeof(struct gameState));
  cardEffect(smithy, -1, -1, -1, &post, -1, &bonus);
  checkSmithyCard(p, &pre, &post);

  return 0;
}
