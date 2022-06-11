//
// linkList.cpp
//
// Keith Mehl
// 04/28/03
// CSCI-15 Example program
// a simple singly-linked linked list example using carriers
// this is a C-style linked list, but implemented in a class.
//

#include <iostream>
using namespace std;

// The user manages the data elements
// the list routines can only see (but not change) the keys
struct DATA
{
    int key;
    char data[31]; // or whatever fields you need...
};

// the linked list class - a 'container class'
// it holds data objects used by the client
class LINKLIST
{
private:
    // the linked list routines manage the list "carrier" elements
    // they are not used by the client. They are the actual nodes in the list
    // in a C++ list, this could be a class with a DATA as a field, for example
    struct CARRIER        // This is composition (vs. aggregation)
    {
        DATA *ptr;        // pointer to client's data node
        CARRIER *next;    // next node link
    };    CARRIER *head;  // pointer to the first element in the list
    CARRIER *free;        // keep unused carriers for re-use (for heap manager)
    CARRIER *getListEl( void );    // get a carrier
    void freeListEl( CARRIER *p ); // release a carrier
    void PrintRevHelper( CARRIER *p ); // recursive print helper method
    bool iterateOK;      // if iterating, did we change the list?
public:
    const static int Forward; // shared const literals for list print direction
    const static int Reverse; // public since the client can use them
    LINKLIST( void );         // constructor, empty list
    ~LINKLIST( void );        // destructor, free all memory
    void AddEl( DATA *e );    // add element, sorted in ascending order
    DATA *removeByKey( int key );
    void PrintList( int direction );
    int IsInList( int key);
    int IsEmpty( void );
    DATA *iterate( int first );  // iterator
};

// static class member initializers - executed at load time
const int LINKLIST::Forward = 1;
const int LINKLIST::Reverse = -1;

LINKLIST::LINKLIST( void )
{
    cout << "In constructor" << endl;
    free = head = NULL;
}

// get a carrier node - check free list first, else allocate
// Noitce I have to scope CARRIER to the LINKLIST class: it's private
LINKLIST::CARRIER *LINKLIST::getListEl( void )
{
    CARRIER *p;
    if( free != NULL )
    {
        p = free;
        free = free->next;
    }
    else
    {
        p = new CARRIER;
    }
    p->ptr = NULL;
    p->next = NULL;
    return p;
}

// free element - just stash it on the free
// list to try to minimize heap fragmentation
void LINKLIST::freeListEl( CARRIER *p )
{
    p->next = free;
    p->ptr = NULL;  // element is unlinked already to be returned to client
    free = p;
    return;
}

// destructor - free list elements and carriers
// and free list of carriers
LINKLIST::~LINKLIST( void )
{
    cout << "In destructor" << endl;
    CARRIER *p = head, *q;
    while( p != NULL )
    {
        q = p;
        p = p->next;
        delete q->ptr;      // destruct data element
        delete q;           // and carrier element
    }
    p = free;               // the free list of carriers
    while( p != NULL )
    {
        q = p;
        p = p->next;
        delete q;
    }
}
// recursive helper to print list in reverse sequence
void LINKLIST::PrintRevHelper( CARRIER *p )
{
    if( p != NULL )
    {
        PrintRevHelper( p->next );
        // in a "real" OO environment, we would use a "call-back"
        // function into the client here to print the data...
        cout << p->ptr->key << '\t' << p->ptr->data << endl;
    }
    return;
}

// user supplies data element *e to add to list by key
void LINKLIST::AddEl( DATA *e )
{
    CARRIER *d = getListEl(), *p, *q;
    d->ptr = e;
    // "inchworm" down the list to find where to insert the element
    // empty for() loop bode - do the work in the loop header
    for( p = head, q = NULL;
         p != NULL && p->ptr->key < d->ptr->key;
         q = p, p = p->next );
    if( q == NULL )
    {
        d->next = head;
        head = d;
    }
    else
    {
        d->next = p;
        q->next = d;
    }
    iterateOK = false; // cannot iterate any more
    return;
}

// remove the first match to key (may have duplicates)
DATA *LINKLIST::removeByKey( int key )
{
    CARRIER*p = head, *q = NULL;
    DATA *d;
    // equivalent while() loop to for() loop above
    while( p != NULL && p->ptr->key != key )
    {
        q = p;
        p = p->next;
    }
    if( p == NULL )
    {
        return NULL;  // indicate key not found
    }
    else if( q == NULL )
    {
        head = head->next;
    }
    else
    {
        q->next = p->next;
    }
    d = p->ptr;
    freeListEl( p ); // don't delete here, manage fragmentation on heap!
    iterateOK = false; // cannot iterate any more
    return d;
}

// forward can be iterative, reverse needs help (or use a stack)
void LINKLIST::PrintList( int direction )
{
    CARRIER *p = head;
    if( direction == Forward )
    {
        while( p != NULL )
        {
            // in a "real" OO environment, we would use a "call-back"
            // function into the client here to print the data...
            cout << p->ptr->key << '\t' << p->ptr->data << endl;
            p = p->next;
        }
    }
    else
    {
        PrintRevHelper( p );
    }
    return;
}

// return true if key is in list, else false
int LINKLIST::IsInList( int key )
{
    CARRIER *p = head;
    while( p != NULL && p->ptr->key < key )
    {
        p = p->next;
    }
    return p != NULL && p->ptr->key == key;
}

int LINKLIST::IsEmpty( void )
{
    return head == NULL;
}

// iterator - each call after first=true advances pointer
// down the list returning the assuciated data pointer,
// until end of list when you get NULL back
// by agreement with the client, DATA cannot be changed
DATA * LINKLIST::iterate( int first )
{
    // a static local variable has permanent duration
    static CARRIER *p = NULL;
    if( first )
    {
        p = head;
        iterateOK = true; // new iteration is always O.K.
    }
    else if( !iterateOK )
    {
        p = NULL; // can't keep iterating a modified list
    }
    else if( p != NULL )
    {
        p = p->next;
    }
    if( p != NULL )
    {
        return p->ptr;
    }
    return NULL;
}

// a simple menu-driven client
int main()
{
    int choice = 0, key;
    DATA d, *e;
    LINKLIST list;

    while( choice != 8 )
    {
        cout << "\n1. add an element\n"
             << "2. see if an element exists\n"
             << "3. remove an element by key\n"
             << "4. print forward\n"
             << "5. print reverse\n"
             << "6. iterate (first)\n"
             << "7. iterate (next)\n"
             << "8. quit\n" << "\nEnter choice : "
             << flush;
        cin >> choice;
        switch( choice )
        {
        case 1:
            cout << "Enter key and data (max 30 chars, with NO SPACES) : "
                 << flush;
            cin >> d.key >> d.data;
            cin.ignore( 100, '\n' ); // get rid of any garbage in input
            e = new DATA;
            (*e) = d;
            list.AddEl( e );
            break;
        case 2:
            cout << "Enter key : " << flush;
            cin >> key;
            if( list.IsInList( key ) )
            {
                cout << "Key " << key << " is in the list\n";
            }
            else
            {
                cout << "Nope, the key " << key << " isn't there\n";
            }
            break;
        case 3:
            cout << "Enter key : " << flush;
            cin >> key;
            e = list.removeByKey( key );
            if( e == NULL )
            {
                cout << "The key " << key << " wasn't there!\n";
            }
            else
            {
                cout << "Key " << key << " has data " << e->data << endl;
                delete e;
            }
            break;
        case 4:
            list.PrintList( LINKLIST::Forward );
            break;
        case 5:
            list.PrintList( LINKLIST::Reverse );
            break;
        case 6:
            e = list.iterate( true );
            if( e == NULL )
            {
                cout << "There is no first key!\n";
            }
            else
            {
                cout << "Key " << e->key << " has data " << e->data << endl;
            }
            break;
        case 7:
            e = list.iterate( false );
            if( e == NULL )
            {
                cout << "There is no next key!\n";
            }
            else
            {
                cout << "Key " << e->key << " has data " << e->data << endl;
            }
            break;
        case 8:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "What???\n\n" << flush;  // should not happen, but...
        }
    }
    return 0;
}