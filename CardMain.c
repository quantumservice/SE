/* Fig. 5.24: main.c
Card shuffling dealing program */
#include  #include  #include  
/* prototypes */
void shuffle( int wDeck[][ 13 ] );
void deal( const int wDeck[][ 13 ], const char *wFace[], 
		  const char *wSuit[] );
void check_pair( int Decks[5][2]);
void check_two_pair( int Decks[5][2]);

int main()
{
	/* initialize suit array */
	const char *suit[ 4 ] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	/* initialize face array */
	const char *face[ 13 ] = 
	{ "Ace", "Deuce", "Three", "Four", 
	"Five", "Six", "Seven", "Eight",
	"Nine", "Ten", "Jack", "Queen", "King" };

	/* initialize deck array */
	int deck[ 4 ][ 13 ] = { 0 };
	int Decks[5][2];	
	srand( time( 0 ) ); /* seed random-number generator */

	shuffle( deck );
	deal( deck, face, suit, Decks);
	check_pair(Decks);

	getchar();

	getchar();

	return 0; /* indicates successful termination */

} /* end main */

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



void deal( const int wDeck[][ 13 ], const char *wFace[],
		  const char *wSuit[], int Deck5[5][2] )
{
	int card;   /* card counter */
	int row;    /* row counter */
	int column; /* column counter */	

	/* deal each of the 52 cards */
	for ( card = 1; card <= 5; card++ ) {

		/* loop through rows of wDeck */
		for ( row = 0; row <= 3; row++ ) {

			/* loop through columns of wDeck for current row */
			for ( column = 0; column <= 12; column++ ) {

				/* if slot contains current card, display card */
				if ( wDeck[ row ][ column ] == card ) {
					printf( "%5s of %-8s\r\n", wFace[ column ], wSuit[ row ]); 
					Deck5[card-1][0]= column;
					Deck5[card-1][1]= row ;

				} /* end if */

			} /* end for */

		} /* end for */

	} /* end for */

}/* end function deal */

void check_pair( int Decks[5][2])
{
	int i, j, m = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = i + 1; j < 5; j++)
		{
			if (Decks[i][0] == Decks[j][0])
			{
				m++;
			}
		}
		
	}
	if (m >1) printf("Yes Two Pair \n");
	else if (m == 1) printf("Yes Pair \n");
	
}




