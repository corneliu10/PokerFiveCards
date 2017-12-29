#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

void build(struct Deck *deck)
{
	int i,j,c=0;
	for(i=0;i<SUITE_SIZE;i++)
		for(j=0;j<CARDS_SIZE;j++)
		{
			deck->cards[c].value = j;
			deck->cards[c].suite = i;
			++c;
		}

	deck->head = 0;
}

void swap_cards(Card *a,Card *b)
{
    int aux1,aux2;
    aux1 = a->value;
    aux2 = a->suite;
    a->value = b->value;
    a->suite = b->suite;
    b->value = aux1;
    b->suite = aux2;
}

void shuffle(struct Deck *deck)
{
	int i,index;
	for(i=0;i<DECK_SIZE;i++)
	{
		index = rand() % 52;
		swap_cards(&deck->cards[i], &deck->cards[index]);
	}
}

Card get_card(struct Deck *deck)
{
	Card card = deck->cards[deck->head];
	deck->cards[deck->head].value = -1;//	delete card
	deck->cards[deck->head].suite = -1;//

	deck->head++;
	return card;
}

void init_deck(struct Deck *deck)
{
	build(deck);
	shuffle(deck);
}
