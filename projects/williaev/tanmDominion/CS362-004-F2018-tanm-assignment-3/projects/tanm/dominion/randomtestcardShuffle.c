#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//machine for assert results, compares decks.
int assertTrue(int sumPre, int sumPost, int diffOrder){
  if(sumPre == sumPost && diffOrder == 1){  //return 1 (true)
    return 1;
  }
  else{
    return 0;
  }
}

int checkShuffle(int player, struct gameState *pre, struct gameState *post){
  int i;
  int sumPre = 0;
  int sumPost = 0;
  int diffOrder = 0; //assumes decks are not shuffled

  if(pre->deckCount[player] == post->deckCount[player]){  //check if decks are equal size
    for(i = 0; i < pre->deckCount[player]; i++){  //sum element of decks and check order
      if(pre->deck[player][i] != post->deck[player][i]){
        diffOrder = 1;  //decks are shuffled
      }
      sumPre = sumPre + pre->deck[player][i];
      sumPost = sumPost + post->deck[player][i];
    }
    if(assertTrue(sumPre, sumPost, diffOrder) == 1){
      printf("Passed: Deck is shuffled.  DiffOrder = %d:  sumPre= %d:  sumPost= %d\n", diffOrder, sumPre, sumPost);
    }
    else{
      printf("Failed: Deck is not shuffled.  DiffOrder = %d:  sumPre= %d:  sumPost= %d\n", diffOrder, sumPre, sumPost); //deck is not in order or the sum or elements is not equal
    }
  }
  else{  //decks not equal size, test fails
    printf("Failed:  decks not the same size\n");
  }
  return 0;
}

int main () {

  int i, n, p;
  struct gameState pre;
  struct gameState post;

  printf ("Testing shuffle()\n");

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
    memcpy (&post, &pre, sizeof(struct gameState));
    shuffle(p, &post);
    checkShuffle(p, &pre, &post);
  }

  return 0;
}
