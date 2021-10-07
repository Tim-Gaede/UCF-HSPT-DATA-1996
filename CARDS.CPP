/*=========================================================================

    cards.cpp   -  Don Cross, 2 May 1996.

    Borland C++ sample solution to CARDS problem from
    1996 High School Programming Tournament.

=========================================================================*/

#include <fstream.h>
#include <string.h>


class CardDeck
{
public:
    CardDeck()
    {
        reset();
    }

    void reset();                        // initialize to be an empty deck
    void addCard ( const char *card )
    {
        isPresent [ cardToIndex(card) ] = 1;
    }

    int haveCard ( int cardIndex ) const
    {
        return isPresent [cardIndex];
    }

    int cardToIndex ( const char *card ) const;

    // The following defines an output operator for the class CardDeck.
    // It's a little funny because it shows the cards that are missing,
    // not the cards that are present.
    friend ostream & operator<< ( ostream &, const CardDeck & );

private:
    int isPresent [52];
};


void CardDeck::reset()
{
    for ( int i=0; i<52; i++ )
    {
        isPresent[i] = 0;
    }
}


int CardDeck::cardToIndex ( const char *card ) const
{
    // In this function we convert the value of a card (2 through Ace)
    // into an integer from 0 to 12.  These are the 13 different possible
    // values of a card.  We add in the suit of the card (a multiple of 13),
    // resulting in a "card index" with a value anywhere from 0 to 51
    // inclusive.  We use the "card index" to index the array to tell
    // whether or not a certain card is present.

    //-----------------------------------------------------------------
    // First calculate the value...

    int value = 0;
    if ( card[0] >= '2' && card[0] <= '9' )
    {
        value = card[0] - '2';
    }
    else switch ( card[0] )
    {
        case 'T':   value =  8;   break;
        case 'J':   value =  9;   break;
        case 'Q':   value = 10;   break;
        case 'K':   value = 11;   break;
        case 'A':   value = 12;   break;
    }

    //-----------------------------------------------------------------
    // Second, calculate the suit value.

    int suit = 0;
    switch ( card[1] )
    {
        case 'S':  suit = 0;  break;
        case 'H':  suit = 1;  break;
        case 'D':  suit = 2;  break;
        case 'C':  suit = 3;  break;
    }

    return value + suit*13;
}


ostream & operator<< ( ostream &output, const CardDeck &deck )
{
    const char * const suit[] =
        { "Spade", "Heart", "Diamond", "Club" };

    for ( int s=0; s<4; s++ )
    {
        output << "   " << suit[s] << "s:";
        for ( int i=0; i<13; i++ )
        {
            if ( !deck.haveCard(i+13*s) )
            {
                char value = i>7 ? "TJQKA"[i-8] : i+'2';
                cout << " " << value;
            }
        }
        output << endl;
    }

    return output;
}


//-------------------------------------------------------------------------



int main()
{
    ifstream infile("cards.in");

    CardDeck deck;
    int counter = 0;

    while ( !infile.eof() )
    {
        char card [80];
        infile >> card;
        if ( strcmp(card,"**") == 0 )
        {
            // end of a data set, so print out the results ...

            cout << "Data set " << ++counter << ":" << endl << deck << endl;

            // ... and start over with an empty deck.
            deck.reset();
        }
        else
        {
            // a card in the current deck...
            deck.addCard ( card );
        }
    }

    return 0;
}

/*--- end of file cards.cpp ---*/
