/* Fig. 5.24: main.c
Card shuffling dealing program */
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <stdbool.h>
/* prototypes */
void shuffle( int wDeck[][ 13 ] );
void deal(int wDeck[][ 13 ], const char *wFace[], 
		  const char *wSuit[], int Deck5[2][5][2]);
int check_recur( int Decks[2][5][2], int hand);
bool check_pair(int Decks[2][5][2], int hand);
bool check_two_pair( int Decks[2][5][2], int hand);
bool check_three(int Decks[2][5][2], int hand);
bool check_four(int Decks[2][5][2], int hand);
bool check_full(int Decks[2][5][2], int hand);
bool check_flush(int Decks[2][5][2], int hand);
bool check_straight(int Decks[2][5][2], int hand);
int getMin(int Decks[2][5][2], int hand);
int getMax(int Decks[2][5][2], int hand);
int getSum(int Decks[2][5][2], int hand);
void evaluate_hand(int Decks[2][5][2], int Hands[2], const char *hNames[]);
void printDeal( int Deck5[2][5][2], const char *wFace[], const char *wSuit[]);

int main()
{
	/* initialize suit array */
	const char *suit[ 4 ] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	/* initialize face array */
	const char *face[ 13 ] = 
	{ "Deuce", "Three", "Four", 
	"Five", "Six", "Seven", "Eight",
	"Nine", "Ten", "Jack", "Queen", "King", "Ace" };
	const char *names[ 9 ] = { "High card", "Pair", "Two Pair", "Three of a kind",
	"Straight", "Flush", "Full house", "Four of a kind", "Straight Flush" };
	int hand1, hand2;
	/* initialize deck array */
	int deck[ 4 ][ 13 ] = { 0 };
	int Hands[10] = { 0 };
	int Decks[2][5][2];	
	srand( time( 0 ) ); /* seed random-number generator */
	int Decks2[2][5][2] ={ { {2, 2},{3, 2},{8, 2},{12, 2},{9, 2} }, { {12, 1},{8, 3},{9, 3},{10, 1},{11, 2} } }; 
	shuffle( deck );
	deal( deck, face, suit, Decks);
	printDeal(Decks, face, suit);
	evaluate_hand(Decks, Hands, names);
	//getchar();

	return 0; /* indicates successful termination */

} /* end main */

void printDeal( int Deck5[2][5][2], const char *wFace[], const char *wSuit[] )
{
	int i,j = 0;

	printf( "\n\t%5s\t\t%-8s\n\n", "Hand 1", "Hand 2");

	for(i = 0; i <= 4; i++) 
	{
		printf( "%5s of %-8s\t%5s of %-8s\n", wFace[ Deck5[0][i][j] ], wSuit[ Deck5[0][i][j + 1] ]
				, wFace[ Deck5[1][i][j] ], wSuit[ Deck5[1][i][j + 1] ]); 

	}		
}

/* shuffle cards in deck */
void shuffle( int wDeck[][ 13 ] )
{
	int row;    /* row number */
	int column; /* column number */
	int card;   /* counter */

	/* for each of the 52 cards, choose slot of deck randomly */
	for ( card = 1; card <= 52; card++ ) {

		/* choose new random location until unoccupied slot found */
		do {
			row = rand() % 4;
			column = rand() % 13;
		} while( wDeck[ row ][ column ] != 0 ); /* end do...while */

		/* place card number in chosen slot of deck */
		wDeck[ row ][ column ] = card;
	} /* end for */

} /* end function shuffle */

/* deal cards in deck */



void deal( int wDeck[][ 13 ], const char *wFace[],
		  const char *wSuit[], int Deck5[2][5][2] )
{
	int card;   /* card counter */
	int row;    /* row counter */
	int column; /* column counter */	

	/* deal each of the 52 cards */
	for ( card = 1; card <= 10; card++ ) {

		/* loop through rows of wDeck */
		for ( row = 0; row <= 3; row++ ) {

			/* loop through columns of wDeck for current row */
			for ( column = 0; column <= 12; column++ ) {

				/* if slot contains current card, display card */
				if ( wDeck[ row ][ column ] == card && card <= 5) {
//					printf( "%5s of %-8s\r\n", wFace[ column ], wSuit[ row ]); 
					Deck5[0][card-1][0]= column;
					Deck5[0][card-1][1]= row ;

				} else if ( wDeck[ row ][ column ] == card && card > 5) {
//					printf("%5s of %-8s\r\n", wFace[ column ], wSuit[ row ]); 
					Deck5[1][card-6][0]= column;
					Deck5[1][card-6][1]= row;
				}

				/* end if */

			} /* end for */

		} /* end for */

	} /* end for */

}/* end function deal */


// check for recurring cards
int check_recur( int Decks[2][5][2], int hand)
{
	int i, j, m = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = i + 1; j < 5; j++)
		{
			if (Decks[hand][i][0] == Decks[hand][j][0])
			{
				m++;
			}
		}
		
	}
	
	return m;
	
}

bool check_pair(int Decks[2][5][2], int hand)
{
	if(check_recur(Decks, hand) == 1)
		return true;
	else 
		return false;

}

bool check_two_pair(int Decks[2][5][2], int hand)
{
	if(check_recur(Decks, hand) == 2)
		return true;
	else 
		return false;

}

// checks for three of a kind.
bool check_three(int Decks[2][5][2], int hand)
{
	if(check_recur(Decks, hand) == 3)
		return true;
	else 
		return false;

}

//checks for four of a kind
bool check_four(int Decks[2][5][2], int hand)
{
	if(check_recur(Decks, hand) == 6)
		return true;
	else 
		return false;

}

//checks for full house
bool check_full(int Decks[2][5][2], int hand)
{
	if(check_recur(Decks, hand) == 4)
		return true;
	else 
		return false;

}

bool check_flush(int Decks[2][5][2], int hand)
{
	
	return (Decks[hand][0][1] == Decks[hand][1][1] && Decks[hand][1][1] == Decks[hand][2][1] && Decks[hand][2][1] == Decks[hand][3][1] &&
		Decks[hand][3][1] == Decks[hand][4][1]);
	
}

bool check_straight(int Decks[2][5][2], int hand)
{

 
  // 1) Get the minimum element in array 
  int min = getMin(Decks, hand);
 
  // 2) Get the maximum element in array 
  int max = getMax(Decks, hand);

  int sum = getSum(Decks, hand);
 
  // 4) max - min + 1 is equal to 5(number of cards) or check explictly for A2345, then only check all elements */
  if ((max - min  + 1 == 5) || (min == 0 && max == 12 && sum == 18))
  {
      
		bool visited[13] = { false };
      int i;
      for (i = 0; i < 5; i++)
      {
         // If we see an element again, then return false 
         if ( visited[Decks[hand][i][0] - min] != false )
           return false;
 
         // If visited first time, then mark the element as visited 
         visited[Decks[hand][i][0] - min] = true;
      }
 
      // If all elements occur once, then return true 
      return true;
  }
 
  return false;
}
// Util functions getMin, getMax, getSum
int getMin(int Decks[2][5][2], int hand)
{
	int i;
	int min = Decks[hand][0][0];
	for ( i = 1; i < 5; i++)
		if (Decks[hand][i][0] < min)
			min = Decks[hand][i][0];
	return min;
}
 
int getMax(int Decks[2][5][2], int hand)
{
	int i;
	int max = Decks[hand][0][0];
	for ( i = 1; i < 5; i++)
		if (Decks[hand][i][0] > max)
			max = Decks[hand][i][0];
	return max;
}

int getSum(int Decks[2][5][2], int hand)
{
	int i, sum = 0;
	
	for ( i = 0; i < 5; i++)
	{
		sum += Decks[hand][i][0];
	}
	return sum;

} 

void evaluate_hand(int Decks[2][5][2], int Hands[2], const char *hNames[])
{
	int i;
	for( i = 0; i < 2; i++)
	{
		if ((check_flush(Decks, i)) && (check_straight(Decks, i)))
			{
			Hands[i] = 9;
			continue;
			}
		else if (check_four(Decks, i))
			{
			Hands[i] = 8;
			continue;
			}
		else if (check_full(Decks, i))
			{
			Hands[i] = 7;
			continue;
			}
		else if (check_flush(Decks, i))
			{
			Hands[i] = 6;
			continue;	
			}
		else if (check_straight(Decks, i))
			{
			Hands[i] = 5;
			continue;
			}
		else if (check_three(Decks, i))
			{
			Hands[i] = 4;
			continue;
			}
		else if (check_two_pair(Decks, i))
			{
			Hands[i] = 3;
			continue;
			}
		else if (check_pair(Decks, i))
			{
			Hands[i] = 2;
			continue;
			}
		else
			Hands[i] = 1;	
		}
	
	if	(Hands[0] > Hands[1])
		printf("HAND 1 WINNER with %s\n ", hNames[Hands[0]-1]);
	else if (Hands[1] > Hands[0])
		printf("HAND 2 WINNER with %s\n", hNames[Hands[1]-1]);
	else if (getMax(Decks, 0) > getMax(Decks, 1))
		printf("HAND 1 WINNER with %s\n ", hNames[Hands[0]-1]);
	else if (getMax(Decks, 1) > getMax(Decks, 0))
		printf("HAND 2 WINNER with %s\n", hNames[Hands[1]-1]);
	else
		printf("Split\n");
}


