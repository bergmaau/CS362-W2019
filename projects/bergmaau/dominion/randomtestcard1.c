/*
 * randomtestcard1.c
 */
/*
 * Include the following lines in your makefile:
 * randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *      gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

#define TESTCARD "smithy"

int checkSmithy(int p, struct gameState *post) {

  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int discarded = 1;
  int shuffledCards = 0;
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  pre.whoseTurn = p;
  post->whoseTurn = p;

	cardEffect(smithy, choice1, choice2, choice3, &pre, handpos, &bonus);

	int newCards = 3;
  int preHand = pre.handCount[p];
  int preDeck = pre.deckCount[p];
  int postHand = post->handCount[p];
  int postDeck = post->deckCount[p];

  printf("starting hand count = %d, starting deck count = %d\n", postHand, postDeck); 
	printf("hand count = %d, expected = %d\n", preHand, postHand + newCards - discarded);
	printf("deck count = %d, expected = %d\n", preDeck, postDeck - newCards + shuffledCards);
	assert(preHand == postHand + newCards - discarded);
	assert(preDeck == postDeck - newCards + shuffledCards);
  return 0;

}

int main() {

    int j, n, p;
	struct gameState G;

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 50; n++) {
    for (j = 0; j < sizeof(struct gameState); j++) {
      ((char*)&G)[j] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.whoseTurn = p;
    G.deckCount[p] = floor(Random() * MAX_DECK);
    int i;
    for (i = 0; i < G.deckCount[p]; i++) {
      int randNum = rand() % 7;
      if (randNum == 0)
        G.deck[p][i] = copper;
      else if (randNum == 1)
        G.deck[p][i] = silver;
      else if (randNum == 2)
        G.deck[p][i] = gold;
      else if (randNum == 3)
        G.deck[p][i] = estate;
      else if (randNum == 4)
        G.deck[p][i] = adventurer;
      else if (randNum == 5)
        G.deck[p][i] = duchy;
      else if (randNum == 6)
        G.deck[p][i] = village;
    }
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.playedCardCount = 0;
    //printf("max hand = %d\n", MAX_HAND);
    G.handCount[p] = floor(Random() * MAX_HAND);
    for (i = 0; i < G.handCount[p]; i++) {
      int randNum = rand() % 7;
      if (randNum == 0)
        G.hand[p][i] = copper;
      else if (randNum == 1)
        G.hand[p][i] = silver;
      else if (randNum == 2)
        G.hand[p][i] = gold;
      else if (randNum == 3)
        G.hand[p][i] = estate;
      else if (randNum == 4)
        G.hand[p][i] = adventurer;
      else if (randNum == 5)
        G.hand[p][i] = duchy;
      else if (randNum == 6)
        G.hand[p][i] = village;
    }

    printf("TEST %d: +3 cards\n", n + 1);

    // ----------- TEST 1: add three cards to player's hand --------------


  	// copy the game state to a test case
  	checkSmithy(p, &G);
  }

  	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
	return 0;
}
