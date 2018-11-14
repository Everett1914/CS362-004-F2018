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
  if(preHand == postHand && preDeck == postDeck && preDiscard == postDiscard){  //return 1 (true)
    return 1;
  }
  else{
    return 0;
  }
}

int checkAdventurerCard(int player, struct gameState *pre, struct gameState *post){
  int drawntreasure = 0;
  int z = 0;
  int temphand1[MAX_HAND];
  while(drawntreasure < 2){  //stop iterating when you've gone through the entire deck or you've found 2 treasure cards
    if (pre->deckCount[player] < 1){//if the deck is empty we need to shuffle discard and add to deck
      for (int i = 0; i < pre->discardCount[player];i++){
        pre->deck[player][i] = pre->discard[player][i];
        pre->discard[player][i] = -1;
      }
      shuffle(player, pre);
      pre->deckCount[player] = pre->discardCount[player];
      pre->discardCount[player] = 0; //Reset discard
    }
    drawCard(player, pre);
    int cardDrawn = pre->hand[player][pre->handCount[player]-1];//top card of hand is most recently drawn card.
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
      drawntreasure++;
    }
    else{
      temphand1[z]=cardDrawn;
      pre->handCount[player]--; //this should just remove the top card (the most recently drawn one).
      z++;
    }
  }
  while(z-1 >= 0){
    pre->discard[player][pre->discardCount[player]++]=temphand1[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }

  //assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);  //memcmp could not be used due to randomness of shuffle.
  if(assertTrue(pre->handCount[player], pre->deckCount[player], pre->discardCount[player], post->handCount[player], post->deckCount[player], post->discardCount[player])){
    printf("Test Passed\n");
  }
  else{
    printf("Test Failed\n");
  }
  return 0;
}

int main () {

  int i, n, p;
  int bonus = -1;
  struct gameState pre;
  struct gameState post;

  printf ("Testing AdventurerCard.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 20000; n++) {  //create random test state for the game.
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
    cardEffect(adventurer, -1, -1, -1, &post, -1, &bonus);
    checkAdventurerCard(p, &pre, &post);
  }

  return 0;
}
