#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

#define HAND_SIZE 5

struct Player
{
	char Name[40];
	Card cards[HAND_SIZE];
	int score;
};

int compare_cards(const void *a,const void *b)
{
	 Card *A = (Card *) a;
	 Card *B = (Card *) b;

	 return A->value - B->value;
}

int hand_stregth(int rank, int high_card)
{
	return (rank * 49) + high_card;
}

/*int hand_stregth_high_cards(Card hand[HAND_SIZE])
{
	return (hand[4].value * 10000 + hand[3].value * 100 + hand[2].value * 10 + hand[1].value * 2 + hand[0].value);
}*/

int analyze_hand(Card hand[HAND_SIZE])
{
	qsort(hand,HAND_SIZE,sizeof(Card),compare_cards); // sort ascending the hand

    int i;
	int flush = 0;
	int straight = 0;
	int four = 0;
	int full_house = 0;
	int three = 0;
	int pairs = 0;
	int high_card = 0;

	flush = 1;
	for(i = 1;i < HAND_SIZE;++i)
		if(hand[i].suite != hand[i-1].suite) flush = 0;

	straight = 1;
	for(i = 1; i < HAND_SIZE;++i)
		if(hand[i].value - hand[i-1].value != 1) straight = 0;

	if(!straight)
	{
		straight = 1;
		for(i = 1; i < HAND_SIZE - 1;++i)
			if(hand[i].value - hand[i-1].value != 1) straight = 0;

		if(hand[4].value != Ace) straight = 0;
	}


	if(flush && straight)
	{
		//ROYAL FLUSH - rank 10
		if(hand[0].value == Ten) return hand_stregth(10, hand[4].value);
		printf("ROYAL FLUSH\n");

		//STRAIGHT FLUSH - rank 9
		return hand_stregth(9, hand[4].value);
		printf("STRAIGHT FLUSH\n");
	}

	four = 1; i = 1;
	int j = HAND_SIZE - 1;
	if(hand[0].value != hand[1].value) i = 2,j++;

	for( ; i < j; ++i)
		if(hand[i].value != hand[i-1].value) four = 0;

	if(four)
	{
		//FOUR OF A KIND - rank 8
		return hand_stregth(8, hand[3].value);
		printf("FOUR OF A KIND\n");
	}

	for(i=1; i < HAND_SIZE - 1; ++i)
	{
		three = 1;
		for(j=i;j <= i + 1;++j)
			if(hand[j].value != hand[j-1].value) three = 0;

		if(three) break;
	}

	full_house = 1;pairs = 0;
	for(i=1; i < HAND_SIZE; ++i)
		if(hand[i].value == hand[i-1].value) ++pairs;

	if(pairs == 3 && three)
	{
		//FULL HOUSE - rank 7
		printf("FULL HOUSE\n");
		return hand_stregth(7, hand[3].value);

	}

	if(flush)
	{
		//FLUSH - rank 6
		printf("FLUSH\n");
		return hand_stregth(6, hand[4].value);

	}

	if(straight)
	{
		//STRAIGHT - rank 5
		printf("STRAIGHT\n");
		return hand_stregth(5, hand[4].value);
	}

	if(three)
	{
		//THREE OF A KIND - rank 4
		printf("THREE OF A KIND\n");
		return hand_stregth(4, hand[2].value);
	}

	if((hand[0].value == hand[1].value && hand[2].value == hand[3].value) ||
		(hand[2].value == hand[3].value && hand[3].value == hand[4].value) ||
		(hand[0].value == hand[1].value && hand[3].value == hand[4].value))
		pairs = 2;

	if(pairs == 2)
	{
		//TWO PAIRS - rank 3
		printf("TWO PAIRS\n");
		return hand_stregth(3, hand[3].value);
	}

	for(i=1; i < HAND_SIZE; ++i)
		if(hand[i].value == hand[i-1].value)
        {
            printf("ONE PAIR\n");
			//ONE PAIR - rank 2
			return hand_stregth(2, hand[i].value);
        }
	//HIGH CARD - rank 1
	printf("HIGH CARD\n");
	return hand_stregth(1, hand[4].value);
}

void show_hand(struct Player J1)
{
    int i;
	printf("%s hand: ", J1.Name);
	for(i=0; i < HAND_SIZE; ++i)
	{
	    //char c;
	    if(J1.cards[i].value+2 == 11) printf("J");
	    else if(J1.cards[i].value+2 == 12) printf("Q");
	    else if(J1.cards[i].value+2 == 13) printf("K");
	    else if(J1.cards[i].value+2 == 14) printf("A");
	    else
    		printf("%d",J1.cards[i].value+2);

    	if(J1.cards[i].suite == 0)
			printf("\u2661 ");
		if(J1.cards[i].suite == 1)
			printf("\u2660 ");
		if(J1.cards[i].suite == 2)
			printf("\u2662 ");
		if(J1.cards[i].suite == 3)
			printf("\u2663 ");
	}

	printf("\n");
}

int main()
{
	int i;
	struct Player J1, J2;

	printf("Nume Jucator 1:  ");
    scanf("%s",J1.Name);

	printf("Nume Jucator 2:  ");
    scanf("%s",J2.Name);

    printf("\nPOKER : \n");

	struct Deck deck;
	int game = 1;
	srand (time(NULL));

	do
	{
		init_deck(&deck);

		for(i=0;i<HAND_SIZE;i++)
		{
			J1.cards[i] = get_card(&deck);
			J2.cards[i] = get_card(&deck);
		}

		show_hand(J1);
		show_hand(J2);

		J1.score = analyze_hand(J1.cards);
		J2.score = analyze_hand(J2.cards);

		if(J1.score > J2.score)
		{
			printf("Castigator: %s\n",J1.Name);
			printf("Felicitari!\n");
		}
		else if(J1.score < J2.score)
		{
			printf("Castigator: %s\n",J2.Name);
			printf("Felicitari!\n");
		}
		else printf("Remiza\n");

		printf("Press 0 to exit or 1 to continue\n");
		scanf("%d",&game);

	}while(game);
}
