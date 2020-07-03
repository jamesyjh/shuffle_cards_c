
/* Student Name: _________________________
 * Student Number: _______________________
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SUITS 4
#define RANKS 13
#define DECK_SIZE 52

typedef struct {
  char *rank;
  char *suit;
  char *colour;
} Card;

Card *make_deck();
void print(Card *);
void shuffle(Card *);

/****** DO NOT ALTER THE MAIN FUNCTION ********/
int main() {

  Card *deck = make_deck();

  printf(" *************** Original Deck ***************\n");
  print(deck); /* print original deck */

  printf("\n\n *************** Shuffled Deck ***************\n");
  shuffle(deck);
  print(deck); /* print shuffled deck */

  return 0;
}

Card *make_deck() {
  /* You may want to use these arrays to point rank and suit to, or to strcpy
   * from. Your choice which you choose */
  char *ranks[] = {"King", "Queen", "Jack", "10", "9", "8",  "7",
                   "6",    "5",     "4",    "3",  "2", "Ace"};
  char *suits[] = {"Spades", "Clubs", "Hearts", "Diamonds"};

  /* allocate space for 52 cards on the heap */
  Card *deck;

  deck = malloc(DECK_SIZE * sizeof(*deck));
  /* put cards into the space */

  int i = 0;
  int s;
  int r;

  for (s = 0; s < SUITS; s++) {
    for (r = 0; r < RANKS; r++) {
      if (strcmp(suits[s], "Spades") == 0 || strcmp(suits[s], "Clubs") == 0) {
        deck[i].colour = "Black";
      } else {
        deck[i].colour = "Red";
      }
      deck[i].suit = suits[s];
      deck[i].rank = ranks[r];
      i++;
    }
  }
  return deck;
  free(deck);
}

/* print the deck to the screen (see sample output on assignment sheet). */
void print(Card *deck) {
  int j;
  for (j = 0; j < DECK_SIZE; j++) {
    printf("[%d] : %s %s %s\n", j + 1, deck[j].colour, deck[j].suit,
           deck[j].rank);
  }
}

/* traverse the deck, one card at a time, swapping the current card
 * with a randomly chosen card from the deck
 */
void shuffle(Card *deck) {
  srand(time(0));
  int i;
  int r;
  Card temp;

  for (i = 0; i < DECK_SIZE; i++) {
    r = rand() % DECK_SIZE;
    temp = deck[i];
    deck[i] = deck[r];
    deck[r] = temp;
  }
}