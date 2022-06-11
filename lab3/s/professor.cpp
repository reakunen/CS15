//
// tortoise.cpp
//
// Keith Mehl
// CSCI-15 Sample program, June 7, 2001
//
// The tortoise and the hare race up a hill.  Who will win?
// Illustrate non-deterministic programming with rand(), as well
// as reviewing parameter passing, modular design, more on C-strings.
// Review command-line parameters: int argc and char *argv[]
//

#include <iostream>     // for iostreams cin && cout
#include <cstdlib>      // for standard library function rand(), atol() etc.
#include <ctime>        // for time to seed random number generator
#include <cstring>      // for C-string manipulation, memxxx() functions
using namespace std;

#define MAX 70          // max line length + overflow room, to fit screen

// functions to do "chunks" of work in the program and illustrate points
void CheckPos( int& );       // only check the animal's position in one place
int  MoveHare( int );        // pass-by-value parameter example
void MoveTort( int& );       // pass-by-reference parameter example
void PrintLine( int t, int h );  // print output, ignore return value
void PrintResults( int t, int h );  // print race result (who won, or a tie)
bool RaceOver( int t, int h );   // logical (Yes/No) example

/***************************************************************************/
//
// main()
//
// decode command line arguments
// seed random number generator
// set contestants in starting gate
// start race
// loop until someone has won
//    move hare and tortoise
//    print line showing race status
// end loop
// print final results
//

int main( int argc, char *argv[] )
{
   int t = 0;                           // position of the Tortoise
   int h = 0;                           // and the Hare
   if( argc == 1 ) // did user supply seed for the random number generator?
   {
      srand( time( nullptr ) ); // no, seed random number generator from time
   }
   else // argc > 1
   {
      srand( atol( argv[1] ) ); // yes, seed with set value from command line
   }
   cout << "Bang!\nAnd they're off!\n"; // start the race
   do
   {
      h = MoveHare( h );   // Move the hare -- value parameter and return
      MoveTort( t );       // Move the tortoise -- reference in/out param
      PrintLine( t, h );   // show current positions -- void function
   } while( !RaceOver( t, h ) );
   PrintResults( t, h );   // print out "who won" message
   return 0;
}

/***************************************************************************/
//
// function CheckPos() checks that the position is within the race track
// and fixes it if needed (so as not to write the same code twice)
//

void CheckPos( int &p )
{
   if( p < 1 )     // cannot slip back into the start gate
   {
      p = 1;       // so set to 1st position on track
   }
   else if( p >= MAX )  // past end of track?
   {
      p = MAX - 1; // - 1 because of array index on display line
   }
   return;
}

/***************************************************************************/
//
// function MoveTort(), moves the tortoise randomly
// with these probabilities:
//
// 50% probability of plodding on full speed (3 places)
// 20% probability of slipping left (-6 places)
// 30% probability of slow plod to right (1 place)
//
void MoveTort( int &t )
{
   int r;     // result of random number generator
   r = rand() % 10 + 1; // generate 1...10
   switch( r )  // the labor-intensive way to calculate the move...
   {
      case 1 :
      case 2 :
      case 3 :
      case 4 :
      case 5 : t += 3;  // fast plod to right
               break;

      case 6 :
      case 7 : t -= 6;  // slip to the left
               break;

      default: t++;     // slow plod to the right;
               break;
   }
   CheckPos( t ); // verify tortoise is still on the track
   return;
}

/***************************************************************************/
//
// function MoveHare(), moves the hare randomly
// with these probabilities:
//
// 20% probability of hare sleeping
// 20% probability of big jump to right (9 places)
// 10% probability of big slip down hill (-12 places)
// 30% probability of small hop to right (1 place)
// 20% probability of small slip to left (-2 places)
//
int MoveHare( int h )
{
   int r = rand() % 10; // random 0...9
   // use a table to avoid the complexity (switch, etc.) of MoveTort()
   // static to avoid reloading the table on each function call
   static const int Moves[10] = { 0, 0, 9, 9, -12, 1, 1, 1, -2, -2 };
   h += Moves[r];  // the lazy man's way to calculate the move...
   CheckPos( h );  // verify hare is still on the track
   return h;
}

/***************************************************************************/
//
// Print a line showing the current position in the race
//
// format and display a line showing the contestant's positions
// if currently tied, the tortoise nips the hare and the hare yells OUCH
// the OUCH message may overwrite the end of the buffer, so need to
// keep extra room in buffer for overflow
//

void PrintLine( int t, int h )
{
   static char ouchMsg[] = "OUCH!!!"; // not re-initialized between calls
   char outLine[MAX+10] = ""; // set up empty string at each function call
              // display line + room for overflow + terminating NUL chars
   int i;
   for( i = 0; i < MAX; i++ )  // fill racetrack with dots
   {
      outLine[i] = '.';
   }
   for( i = MAX; i < MAX+10; i++ )
   {
      outLine[i] = '\0'; // terminate string, OUCH!!! may overwrite a single
   }                     // NUL ('\0') at end, so set all 10 remaining bytes
   if( t == h )
   {
      memcpy( &outLine[t], ouchMsg, strlen(ouchMsg) ); // Tortoise nips Hare
   }                                       // may overflow outline[MAX]
   else
   {
      outLine[t] = 'T';  // otherwise, set Tortoise and Hare into race course
      outLine[h] = 'H';
   }
   cout << outLine << endl;  // and print the formatted line to the screen
   return;
}

/***************************************************************************/
//
// Check if the race is over, i.e., is someone at the finish? True/False
//
// If either contestant is over finish line, we're done
//

bool RaceOver( int t, int h )
{
   return t >= MAX - 1 || h >= MAX - 1; // race over?
}

/***************************************************************************/
//
// Print result messages after the race is over
//

void PrintResults( int t, int h )
{
   if( t == h ) // print results
   {
      cout << "\nWow! It's a TIE!!!" << endl;
   }
   else if( t > h )
   {
      cout << "\nYay!!! The Tortoise Wins!!! The crowd goes wild!!!" << endl;
   }
   else // otherwise, it MUST be the case that T < H
   {
      cout << "\nThe Hare Wins... Yuch." << endl;
   }
   return;
}
