/*=========================================================================

    security.cpp -  Don Cross, 2 May 1996.

    Borland C++ sample solution to SECURITY problem from
    1996 High School Programming Tournament.

=========================================================================*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

static char * CopyString ( const char *s )
{
    char *copy = new char [strlen(s) + 1];
    strcpy ( copy, s );
    return copy;
}


struct PlaceEntry
{
    PlaceEntry *next;   // link to next PlaceEntry in list
    char *place;        // name of place

    PlaceEntry(): next(0), place(0) {}

    ~PlaceEntry()
    {
        if ( place )
        {
            delete[] place;
            place = 0;
        }
    }
};


void Intersect ( PlaceEntry * &target, PlaceEntry *other )
{
    // delete every entry in this list which is not in the other list.

    if ( !target )
    {
        return;
    }

    Intersect ( target->next, other );   // recursively handle rest of list

    int found = 0;

    for ( PlaceEntry *t=other; t && !found; t = t->next )
    {
        if ( strcmp ( target->place, t->place ) == 0 )
        {
            found = 1;
        }
    }

    if ( !found )
    {
        PlaceEntry *temp = target;
        target = target->next;
        delete temp;
    }
}


PlaceEntry *Copy ( PlaceEntry *x )
{
    PlaceEntry *y = 0;

    if ( x )
    {
        y = new PlaceEntry;
        y->place = CopyString ( x->place );
        y->next = Copy ( x->next );
        }

        return y;
}


void Delete ( PlaceEntry *places )
{
    PlaceEntry *temp, *next;
    for ( temp=places; temp; temp = next )
    {
        next = temp->next;
        delete temp;
    }
}


struct SecurityEntry
{
    SecurityEntry *next;   // link to next person in database
    char *name;            // name of person
    PlaceEntry *places;    // linked list of places allowed access

    SecurityEntry(): next(0), name(0), places(0) {}
    ~SecurityEntry();
};


SecurityEntry::~SecurityEntry()
{
    if ( name )
    {
        delete[] name;
        name = 0;
    }

    Delete ( places );
}


class SecurityDatabase
{
public:
    SecurityDatabase(): front(0) {}
    ~SecurityDatabase()
    {
        if ( front )
        {
            delete front;
            front = 0;
        }
    }

    void addName ( const char *name );     // adds new name to database
    void addPlace ( const char *place );   // add place to most recent name

    PlaceEntry *findPerson ( const char *name );

private:
    SecurityEntry *front;
};



PlaceEntry *SecurityDatabase::findPerson ( const char *name )
{
    for ( SecurityEntry *t = front; t; t = t->next )
    {
        if ( strcmp ( t->name, name ) == 0 )
        {
            // found the person

            return Copy ( t->places );
        }
    }

    return 0;   // could not find the person
}



void SecurityDatabase::addName ( const char *name )
{
    SecurityEntry *s = new SecurityEntry;
    s->next = front;
    s->name = CopyString(name);
    s->places = 0;
    front = s;
}


void SecurityDatabase::addPlace ( const char *place )
{
    PlaceEntry *places = new PlaceEntry;
    places->next = front->places;
    places->place = CopyString(place);
    front->places = places;
}


static void ScanName ( const char *line, char *name )
{
    strcpy ( name, line );
    char *t = name + strlen(name) - 1;
    if ( *t == '\n' ) *t = '\0';
}


int main()
{
    FILE *input = fopen ( "security.in", "rt" );
    char line [256];

    fgets ( line, sizeof(line), input );
    int n;  // number of people in the database
    sscanf ( line, "%d", &n );

    SecurityDatabase sd;
    char name [80];

    // First read in the security database...

    for ( int i=0; i<n; i++ )
    {
        fgets ( line, sizeof(line), input );   // read name of person
        ScanName ( line, name );

        sd.addName (name);

        fgets ( line, sizeof(line), input );
        char place [80];
        char *p = place;
        for ( int k=0; ; k++ )
        {
            if ( !line[k] || isspace(line[k]) )
            {
                *p = '\0';
                                sd.addPlace (p = place);
                        }
            else
            {
                *p++ = line[k];
            }

            if ( !line[k] || line[k] == '\n' )
                break;
        }
    }

    // Then process security requests...

    fgets ( line, sizeof(line), input );
    int m;  // number of security requests.
    sscanf ( line, "%d", &m );

    for ( i=0; i<m; i++ )
    {
        int np;   // number of people in possible-list
        fgets ( line, sizeof(line), input );
        sscanf ( line, "%d", &np );
                PlaceEntry *places = 0;
                for ( int j=0; j<np; j++ )
                {
                        fgets ( line, sizeof(line), input );
                        ScanName ( line, name );
                        if ( j == 0 )
                        {
                                places = sd.findPerson (name);
                        }
                        else
                        {
                                PlaceEntry *temp = sd.findPerson (name);
                                Intersect ( places, temp );
                                Delete (temp);
                        }
                }

                if ( places )
                {
                        printf ( "Grant access to " );
                        int first = 1;
                        for ( PlaceEntry *temp = places; temp; temp = temp->next )
                        {
                                if ( !first )
                                {
                                        printf ( ", " );
                                }
                                else
                                {
                                        first = 0;
                                }

                                printf ( "%s", temp->place );
                        }
                        printf ( ".\n" );
                        Delete (places);
                }
                else
                {
                        printf ( "Do not grant access to any areas.\n" );
                }
        }

    fclose ( input );
    return 0;
}


/*--- end of file security.cpp ---*/
