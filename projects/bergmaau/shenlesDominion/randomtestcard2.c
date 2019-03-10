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

#define TESTCARD "council_room"

int checkCouncilRoom(int p, struct gameState *post) {

  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int discarded = 1;
  int shuffledCards = 0;
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  pre.whoseTurn = p;
  post->whoseTurn = p;
  //int postHand = post->handCount[p];
  //int postDeck = post->deckCount[p];
  int postHand = pre.handCount[p];
  int postDeck = pre.deckCount[p];
  printf("starting hand count = %d, starting deck count = %d\n", postHand, postDeck);
  printf("about to call effect\n");
	cardEffect(council_room, choice1, choice2, choice3, &pre, handpos, &bonus);
  printf("effect called\n");
	int newCards = 4;
  int preHand = pre.handCount[p];
  int preDeck = pre.deckCount[p];



	printf("hand count = %d, expected = %d\n", preHand, postHand + newCards - discarded);
	printf("deck count = %d, expected = %d\n", preDeck, postDeck - newCards + shuffledCards);
	assert(preHand == postHand + newCards - discarded);
	assert(preDeck == postDeck - newCards + shuffledCards);
  //free(&pre);
  return 0;

}

int main() {

    int j, n, p;
	struct gameState G;

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

  SelectStream(2);
  PutSeed(3);
int m;
  for (n = 0; n < 500; n++) {
    for (j = 0; j < sizeof(struct gameState); j++) {
      ((char*)&G)[j] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.whoseTurn = p;
    G.numBuys = 1;
    G.numPlayers = 2;
    for (m = 0; m < 2; m++) {
      G.deckCount[m] = floor(Random() * MAX_DECK);
    int i;
    for (i = 0; i < G.deckCount[m]; i++) {
      int randNum = rand() % 7;
      if (randNum == 0)
        G.deck[m][i] = copper;
      else if (randNum == 1)
        G.deck[m][i] = silver;
      else if (randNum == 2)
        G.deck[m][i] = gold;
      else if (randNum == 3)
        G.deck[m][i] = estate;
      else if (randNum == 4)
        G.deck[m][i] = adventurer;
      else if (randNum == 5)
        G.deck[m][i] = duchy;
      else if (randNum == 6)
        G.deck[m][i] = village;
    }
    G.discardCount[m] = floor(Random() * MAX_DECK);
    for (i = 0; i < G.discardCount[p]; i++) {
      int randNum = rand() % 7;
      if (randNum == 0)
        G.discard[m][i] = copper;
      else if (randNum == 1)
        G.discard[m][i] = silver;
      else if (randNum == 2)
        G.discard[m][i] = gold;
      else if (randNum == 3)
        G.discard[m][i] = estate;
      else if (randNum == 4)
        G.discard[m][i] = adventurer;
      else if (randNum == 5)
        G.discard[m][i] = duchy;
      else if (randNum == 6)
        G.discard[m][i] = village;
    }
    G.playedCardCount = 0;
    //printf("max hand = %d\n", MAX_HAND);
    G.handCount[m] = floor(Random() * MAX_HAND);
    for (i = 0; i < G.handCount[p]; i++) {
      int randNum = rand() % 7;
      if (randNum == 0)
        G.hand[m][i] = copper;
      else if (randNum == 1)
        G.hand[m][i] = silver;
      else if (randNum == 2)
        G.hand[m][i] = gold;
      else if (randNum == 3)
        G.hand[m][i] = estate;
      else if (randNum == 4)
        G.hand[m][i] = adventurer;
      else if (randNum == 5)
        G.hand[m][i] = duchy;
      else if (randNum == 6)
        G.hand[m][i] = village;
    }
  }

    printf("TEST %d: +4 cards\n", n + 1);

    // ----------- TEST 1: add three cards to player's hand --------------


  	// copy the game state to a test case
  	checkCouncilRoom(p, &G);
    //free(&G);
  }

  	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
	return 0;
}
