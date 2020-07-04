/* Student Name: James Hong
 * Student Number: 991554074
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define GetCurrentDir getcwd
#define SUITS 4
#define RANKS 13
#define DECK_SIZE 52

typedef struct
{
  char *rank;
  char *suit;
  char *colour;
} Card;

Card *make_deck();
void print(Card *);
void shuffle(Card *);
void printToFile(FILE *out, Card *deck, int opt);

/****** THE MAIN FUNCTION ********/
int main(int argc, char **argv)
{

  Card *deck = make_deck();
  FILE *out;
  char buff[FILENAME_MAX];
  GetCurrentDir(buff, FILENAME_MAX);

  /* PRINT THE ORIGINAL DECK*/
  printf("\n*************** Original Deck ***************\n");
  print(deck);

  /* SHUFFLE THE DECK*/
  shuffle(deck);
  printf("\n\n*************** Shuffled Deck ***************\n");
  print(deck); /* print shuffled deck */

  out = fopen(argv[1], "w");
  if (argv[1] != NULL)
  {
    printToFile(out, deck, 1);

    printf("** Original Deck data saved to location: %s/%s\n\n", buff, argv[1]);
  }
  else
  {
    printf("Filename required for copy of original deck data: eg. ./shuffle "
           "original.deck\n");
    free(deck);
    fclose(out);

    return 1;
  }
  fclose(out);

  out = fopen(argv[2], "w");
  if (argv[2] != NULL)
  {
    printToFile(out, deck, 2);

    printf("** Shuffled Deck data saved to location: %s/%s\n\n", buff, argv[2]);
  }
  else
  {
    printf("Filename required for copy of shuffled deck data: eg. ./shuffle "
           "shuffled.deck\n");

    free(deck);
    fclose(out);
    return 1;
  }

  fclose(out);
  free(deck);
  return 0;
}

Card *make_deck()
{
  char *ranks[] = {"King", "Queen", "Jack", "10", "9", "8", "7",
                   "6", "5", "4", "3", "2", "Ace"};
  char *suits[] = {"Spades", "Clubs", "Hearts", "Diamonds"};

  /* allocate space for 52 cards on the heap */
  Card *deck = malloc(DECK_SIZE * sizeof(*deck));
  /* put cards into the space */

  int i = 0;
  int s;
  int r;

  for (s = 0; s < SUITS; s++)
  {
    for (r = 0; r < RANKS; r++)
    {
      if (strcmp(suits[s], "Spades") == 0 || strcmp(suits[s], "Clubs") == 0)
      {
        deck[i].colour = "Black";
      }
      else
      {
        deck[i].colour = "Red";
      }
      deck[i].suit = suits[s];
      deck[i].rank = ranks[r];
      i++;
    }
  }
  return deck;
}

void print(Card *deck)
{

  int j;
  for (j = 0; j < DECK_SIZE; j++)
  {
    printf("[%d] : %s %s %s\n", j + 1, deck[j].colour, deck[j].suit,
           deck[j].rank);
  }
}

/* traverse the deck, one card at a time, swapping the current card
 * with a randomly chosen card from the deck
 */
void shuffle(Card *deck)
{
  srand(time(0));
  int i;
  int r;
  Card temp;

  for (i = 0; i < DECK_SIZE; i++)
  {
    r = rand() % DECK_SIZE;
    temp = deck[i];
    deck[i] = deck[r];
    deck[r] = temp;
  }
}

void printToFile(FILE *out, Card *deck, int opt)
{
  int j;
  if (opt == 1)
  {
    fprintf(out, "*************** Original Deck ***************\n");
  }
  else
  {
    fprintf(out, "*************** Shuffled Deck ***************\n");
  }
  for (j = 0; j < DECK_SIZE; j++)
  {
    fprintf(out, "[%d] : %s %s %s\n", j + 1, deck[j].colour, deck[j].suit,
            deck[j].rank);
  }
}
