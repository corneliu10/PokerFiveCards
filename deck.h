#include <stdio.h>
#include <stdlib.h>

#define DECK_SIZE 52
#define SUITE_SIZE 4
#define CARDS_SIZE 13

/* card combos */
enum VALUE { Two = 0, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };
enum SUITE { Hearts = 0, Spades, Diamonds, Clubs };

typedef struct
{
	int value;
	int suite;
}Card;

struct Deck
{
	int head; // index of the head
	Card cards[DECK_SIZE];
};

void build(struct Deck *deck);
void shuffle(struct Deck *deck);
Card get_card(struct Deck *deck);
void init_deck(struct Deck *deck);
