#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//machine for assert results, compares deck, discard, and hand numbers of pre and post states.
int assertTrue(int found, int preHand, int postHand){
  if(found == 1 && postHand == preHand - 1){
    return 1;
  }
  else{
    return 0;
  }
}

int checkCutpurseCard(int p, struct gameState *pre, struct gameState *post){
  int i, opponent;
  int found = 0;
  int j = 0;
  for(i = 0; i < pre->numPlayers; i++){
    if(i != p){  //select opponent
      opponent = i;
    }
  }
  while(j < pre->handCount[opponent]){
    if(pre->hand[opponent][j] == copper){
      found = 1;
    }
    j++;
  }
  if(assertTrue(found, pre->handCount[opponent], post->handCount[opponent])){
    printf("Passed\n");
  }
  else{
    printf("Failed\n");
  }
  return 0;
}

int main () {

  int i, n, cutPursePos, cutPursePos0, cutPursePos1;
  int bonus = -1;
  struct gameState pre;
  struct gameState post;

  printf("_____________________\n");
  printf("Testing Cutpurse Card.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 20; n++) {  //create random test state for the game.
    printf("test#: %d\n", n);
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&pre)[i] = floor(Random() * 256);
    }
    //Create random deck, hand, played and discard
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
        cutPursePos0 = floor(Random() * pre.handCount[p]); //ensure a cutpurse is in the hand to be played player 1
        pre.hand[p][cutPursePos0]=cutpurse;
      }
      else{
        cutPursePos1 = floor(Random() * pre.handCount[p]); //ensure a cutpurse is in the hand to be played player 2
        pre.hand[p][cutPursePos1]=cutpurse;
      }
    }
    pre.playedCardCount = floor(Random() * MAX_DECK); //set up played deck
    for(i = 0; i < pre.playedCardCount; i++){
      pre.playedCards[i]=floor(Random() * 26);
    }
    pre.numPlayers = 2;
    pre.whoseTurn = floor(Random() * 2);  //set up turn and select correct handPos=cutPursPos for player
    if(pre.whoseTurn == 0){
      cutPursePos = cutPursePos0;
    }
    else{
      cutPursePos = cutPursePos1;
    }
    memcpy (&post, &pre, sizeof(struct gameState));
    cardEffect(cutpurse, -1, -1, -1, &post, cutPursePos, &bonus);
    checkCutpurseCard(pre.whoseTurn, &pre, &post);
  }
  return 0;
}
