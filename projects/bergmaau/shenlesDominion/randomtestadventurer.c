/*
 * randomtestadventurer.c
 */
/*
 * Include the following lines in your makefile:
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

#define TESTCARD "adventurer"

int checkAdventurer(int p, struct gameState *post) {
  int i;
  int coppers = 0;
  int silvers = 0;
  int golds = 0;
  int treasuresPre;
  int treasuresPost;
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

  struct gameState pre;

  memcpy (&pre, post, sizeof(struct gameState));

  //int r;
  //r = cardEffect( p, post);
int cards = pre.handCount[p];
printf("initial handcount is %d\n", cards);
  for (i = 0; i < cards; i++) {
    //printf("in the loop\n");
    if (handCard(i, &pre) == copper) {
      //printf("found a copper\n");
      coppers++;
    }
    else if (handCard(i, &pre) == silver) {
      //printf("found a silver\n");
      silvers++;
    }
    else if (handCard(i, &pre) == gold) {
      //printf("found a gold\n");
      golds++;
    }
    //printf("done\n");
  }
  treasuresPre = (coppers + silvers + golds);
  printf("Starting number of treasure cards = %d\n", treasuresPre);

  cardEffect(adventurer, choice1, choice2, choice3, post, handpos, &bonus);

  coppers = 0;
  silvers = 0;
  golds = 0;

  for (i = 0; i < post->handCount[p]; i++) {
    if (handCard(i, post) == copper) {
      coppers++;
    }
    else if (handCard(i, post) == silver) {
      silvers++;
    }
    else if (handCard(i, post) == gold) {
      golds++;
    }
  }
  treasuresPost = (coppers + silvers + golds);
  printf("final treasures = %d, expected = %d\n", treasuresPost, treasuresPre + 2);
  assert(treasuresPost == treasuresPre + 2);
  return 0;
}

int main() {
    //int i;
    //int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    //int seed = 1000;
    //int numPlayers = 2;
    //int thisPlayer = 0;

    int j, n, p;
    printf("first print statement");
    struct gameState G;
//	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,	sea_hag, tribute, smithy, council_room};

	printf("----------------- Testing Card: Adventurer ----------------\n");

  SelectStream(2);


  PutSeed(3);

  for (n = 0; n < 50; n++) {
    for (j = 0; j < sizeof(struct gameState); j++){
      ((char*)&G)[j] = floor(Random() * 256);
      //printf("check1\n");
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

    printf("TEST %d: +2 treasure cards\n", n+1);

    checkAdventurer(p, &G);

  	// copy the game state to a test case
  	//struct gameState testG;
	//memcpy(&testG, &G, sizeof(struct gameState));

}
printf("\n >>>>> SUCCESS: Testing complete Adventurer <<<<<\n\n");

	return 0;
}
