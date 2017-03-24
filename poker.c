#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/********************************************************************/
/*                                                                  */
/* Program: Poker                                                   */
/* Author: Mainframe Master                                         */
/* Date: 10/5/15                                                    */
/*                                                                  */
/* Description:                                                     */
/*  This program was written for the Master the Mainframe contest   */
/*  2015. It is similar to the challenge posed by Project Euler     */
/*  Euler problem #54:  (https://projecteuler.net/problem=54)       */
/*                                                                  */
/*  The problem reads as follows:                                   */
/*                                                                  */
/*  In the card game poker, a hand consists of five cards and are   */
/*  ranked, from lowest to highest, in the following way:           */
/*                                                                  */
/*  High Card: Highest value card.                                  */
/*  One Pair: Two cards of the same value.                          */
/*  Two Pairs: Two different pairs.                                 */
/*  Three of a Kind: Three cards of the same value.                 */
/*  Straight: All cards are consecutive values.                     */
/*  Flush: All cards of the same suit.                              */
/*  Full House: Three of a kind and a pair.                         */
/*  Four of a Kind: Four cards of the same value.                   */
/*  Straight Flush: All cards are consecutive values of same suit.  */
/*  Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.         */
/*                                                                  */
/*  The cards are valued in the order:                              */
/*  2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.             */
/*                                                                  */
/*  If two players have the same ranked hands then the rank made up */
/*  of the highest value wins; for example, a pair of eights beats  */
/*  a pair of fives. But if two ranks tie, for example, both        */
/*  players have a pair of queens, then highest cards in each hand  */
/*  are compared; if the highest cards tie then the next highest    */
/*  cards are compared, and so on, until a winner is determined or  */
/*  a tie is declared.                                              */
/*                                                                  */
/*  The input to this program contains random hands dealt to        */
/*  players.  Each record in the input data set contains an array   */
/*  of cards separated by single spaces: the first five are Player  */
/*  1's cards, the next five are Player 2's cards.  You can assume  */
/*  that all hands are valid (no invalid characters, repeated       */
/*  cards, or incomplete hands), each player's hand is in no        */
/*  specific order, and in each hand there is a clear victor.  That */
/*  is, NO RECORDS in the input data set depict poker hands that    */
/*  would end in a tie, though in a real life poker game that is    */
/*  certainly a possibility!                                        */
/*                                                                  */
/*  The output to this program (originally) contains a list of      */
/*  which player is the winner for each set of hands in the input   */
/*  data set.                                                       */
/*                                                                  */
/********************************************************************/

 FILE *inputFile; /* This data type describes the input data set    */

 int debug = 0;   /* This flag controls extra debug data printed to */
                  /* the output file. Change it to 1, recompile,    */
                  /* and rerun the program to see loads of extra    */
                  /* data to help you along! Note that the program  */
                  /* must ultimately be run with debug = 0 to       */
                  /* produce an output file that will be deemed     */
                  /* correct.                                       */

 typedef struct cards {
   char cardvalue;
   char cardsuit;
 };               /* This struct (data structure) describes a       */
                  /* playing card. A card has a value (rank) and a  */
                  /* suit.                                          */

/********************************************************************/
/* The following are arrays of five instances of struct cards       */
/* that depict each player's hand.                                  */
/* There is one array per player.                                   */
/* The cards in the array can be indexed: array[0] is the first     */
/* card in the hand and array[4] is the last card in the hand.      */
/********************************************************************/
 struct cards p1cards[5];
 struct cards p2cards[5];

/********************************************************************/
/* The following are arrays that contain the post-processed poker   */
/* hands. They are output from subroutine countCards and contain    */
/* up to five values indicating the ranks of the cards in the hands.*/
/* See subroutine countCards for an explanation of what the arrays  */
/* contain and how they are used.                                   */
/* There is one array per player.                                   */
/********************************************************************/
 int p1SortedValues[5];
 int p2SortedValues[5];

/********************************************************************/
/* The following are int variables used to hold the "score" that    */
/* each player's hand is "worth" for a particular round.            */
/* The score for a higher value hand is higher than the score for a */
/* lower value hand, but the particular score is unique to this     */
/* program and has nothing to do with the actual game of poker.     */
/********************************************************************/
 int p1Score;
 int p2Score;

/********************************************************************/
/* Global counter to Summary                                        */
/********************************************************************/
 int totalHand          = 0;
 int totalRoyalFlush    = 0;
 int totalStraightFlush = 0;
 int totalFourKind      = 0;
 int totalFullHouse     = 0;
 int totalFlush         = 0;
 int ttlStraight        = 0;
 int totalThreeKind     = 0;
 int totalTwoPair       = 0;
 int totalOnePair       = 0;
 int totalHigh          = 0;

/********************************************************************/
/* The following enumerations are used to match up named constants  */
/* to values that are used by the program. An enumeration is a user-*/
/* defined data type consisting of a set of integral constants each */
/* given a name.                                                    */
/*                                                                  */
/* The first enumeration assigns integral constant values to each   */
/* named card rank.  The value of 2 is given to the rank TWO and    */
/* the value of 14 is given to the rank of ACE.                     */
/*                                                                  */
/* The second enumeration assigns numeric values to each named      */
/* hand rank. The value of 0 is given to the rank HIGHCARD and the  */
/* value of 7 is given to the rank FOURKIND. Notice that "straight  */
/* flush" is not listed here. A straight flush hand is both a       */
/* straight and a flush, so it is assigned the value STRAIGHT+FLUSH */
/* of 4+5=9. This only works because the straight flush rank beats  */
/* the four of a kind rank.                                         */
/********************************************************************/
 enum {TWO=2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK,
       QUEEN, KING, ACE};

 enum {HIGHCARD=0, ONEPAIR, TWOPAIR, THREEKIND, STRAIGHT, FLUSH,
       FULLHOUSE, FOURKIND, ROYAL};

/********************************************************************/
/* The function called int main() is where the code begins executing*/
/* when the program is invoked. This is where the magic happens!    */
int main()
{
/********************************************************************/
/* The following are all function prototypes for functions          */
/* (subroutines) that will show up later in the program. The body of*/
/* the functions is omitted here, but can be found below. The       */
/* function prototype is a "preview" of the input and output for    */
/* the function itself!  Either the function prototype or the       */
/* function itself must appear in the file prior to any invocation  */
/* of the function.                                                 */
/********************************************************************/
  int isRoyal(int values[]);
  int isFlush(struct cards[]);
  int isStraight(int values[]);
  int getValue(char val);
  char getPrint(int val);
  void countCards(int values[], int sortedValues[], int frequency[]);
  int scoreHand(struct cards[],int sortedValues[]);
  int chooseWinner(int values0[],int score0, int values1[], int score1);

/********************************************************************/
/* Following are a few variables that are local to int main().      */
/********************************************************************/
  int i;
  char c;
  int total = 0;
  int p1wins = 0;
  int p2wins = 0;

/********************************************************************/
/* Now that we're done defining prototypes and variables, let's get */
/* to work! Open the file to read the input.                        */
/* You'll see that the DDNAME used in the JCL to run the program    */
/* (INPUT) must match the DDNAME used to open the file here.        */
/********************************************************************/
  inputFile = fopen("poker.txt", "r");
  if (inputFile == NULL)
    {
      printf("open error:   %d/%s\n", errno, strerror(errno));
      exit(98);
    }

/********************************************************************/
/* Run program! The basic flow of this program is to read the input */
/* data record by record and process each record until we run out   */
/* of input data. At that point the program will be finished.       */
/********************************************************************/
  while (fscanf(inputFile,
         "%s %s %s %s %s %s %s %s %s %s",
         &p1cards[0],&p1cards[1],&p1cards[2],&p1cards[3],&p1cards[4],
         &p2cards[0],&p2cards[1],&p2cards[2],&p2cards[3],&p2cards[4]
    ) != EOF) {   /* The while statement reads a record and stores  */
                  /* the data (cards) found on the record in a      */
                  /* series of variables (defined above). The body  */
                  /* of the while statement (following) is executed */
                  /* if another record was found (that is, the      */
                  /* fscanf routine which is internal to C did not  */
                  /* produce a return code of EOF, meaning there was*/
                  /* no more data to read).                         */
                  /* fscanf works by reading data from the specified*/
                  /* file (in this case, inputFile), storing the    */
                  /* data according to the parameter format (in this*/
                  /* case, storing the input found as 10 separate   */
                  /* string values) into the locations pointed to by*/
                  /* the remaining arguments.                       */

     if (debug) { /* If the debug flag is enabled (that is, not     */
                  /* equal to zero) then print some diagnostic      */
                  /* information showing what data was read in for  */
                  /* player 1's hand                                */
       printf("\n\nPlayer 1: %.2s %.2s %.2s %.2s %.2s : ",
         &p1cards[0],&p1cards[1],&p1cards[2],&p1cards[3],&p1cards[4]);
     }            /* End of "if (debug)"                            */
     p1Score = scoreHand(&p1cards[0],&p1SortedValues[0]);
                  /* Analyze the hand and store the "score" in to   */
                  /* variable p1Score. Notice that the              */
                  /* p1SortedValues array, which was previously     */
                  /* unused, is filled in with some information by  */
                  /* the scoreHand routine which is used to deterime*/
                  /* the winner in case the "score" is a tie, that  */
                  /* is, both players got the same hand rank.       */
                  /* Note that an entire array is passed to a       */
                  /* function by passing the address of the first   */
                  /* entry (&array[0] is the address of the first   */
                  /* entry, array[0] is the value of the first      */
                  /* entry).                                        */

     if (debug) { /* Do the same thing for player 2 now             */
       printf("Player 2: %.2s %.2s %.2s %.2s %.2s : ",
         &p2cards[0],&p2cards[1],&p2cards[2],&p2cards[3],&p2cards[4]);
     }            /* End of "if (debug)"                            */
     p2Score = scoreHand(&p2cards[0],&p2SortedValues[0]);

     if (debug) { /* If we're in debugging mode, display the scores */
       printf("%d:%d; ",p1Score,p2Score);
     }

     if (chooseWinner(&p1SortedValues[0],p1Score,
                      &p2SortedValues[0],p2Score) == 1)
     {            /* If player 1 is the winner, display an          */
                  /* indication of this. The chooseWinner routine   */
                  /* works by taking input data from two players and*/
                  /* returning a value of 1 if the first of the two */
                  /* players is the winner and returning a value    */
                  /* of zero if the second of the two players is the*/
                  /* winner.                                        */
     /*printf("Player 1 wins!\n"); */
      p1wins += 1;
     }
     else
     {
     /*printf("Player 2 wins!\n");  */
      p2wins += 1;
     }
     total  += 1;

     /* The following code (which is all commented out for now)     */
     /* contains much of the code needed for the first programming  */
     /* exercise.                                                   */
     /*                                                             */
     /* Your challenge will be to create a report at the end of your*/
     /* output showing how many games were played, the number/      */
     /* percentage won by player 1, and the number/percentage won by*/
     /* player 2.                                                   */
     /*                                                             */
     /* These lines of code show examples of how the printf         */
     /* statement, which is used to print stuff in C, works.        */
     /* Printf writes the C string specified by the first parameter */
     /* to the standard output (which our JCL routes to an output   */
     /* data set member). If the string includes format specifiers, */
     /* the additional parameters following the first parameter are */
     /* formatted (if necessary) and substituted in to the output   */
     /* string in place of the format specifier.                    */
     /*                                                             */
     /* The only format specifier used in the following printf      */
     /* statements is %d, which indicates that a decimal value will */
     /* be printed. For each %d in the printf statement, there will */
     /* be a variable containing a numeric value whose value will   */
     /* be substituted in the output string in place of the %d.     */
     /*                                                             */
     /* Format specifiers can be very fancy, causing the value to be*/
     /* formatted to a specified width, precision, or length. A     */
     /* detailed description can be found here:                     */
     /*    http://www.cplusplus.com/reference/cstdio/printf/        */
     /*                                                             */
     /* For our purposes, a plain old %d will suffice, which prints */
     /* a signed decimal integer, right justified, with no preceding*/
     /* spaces or zeros.                                            */
     /*                                                             */
     /* You may notice a few other peculiar things in the C string: */
     /* \n is an escape character used to advance to the beginning  */
     /* of the next line (which can easily be used to insert a blank*/
     /* line in the output!)                                        */
     /* %% is the method used to print an actual percent sign in the*/
     /* output. When the compiler sees two % in a row (%%) it knows */
     /* that we're not giving it a format specifier like %d, but    */
     /* that we actually want a percent sign in our output!         */

     /***************************************************************/
     /* Reset variables to zero before reading/processing next hand */
     /***************************************************************/
     memset(p1SortedValues, 0, sizeof(p1SortedValues));
     memset(p2SortedValues, 0, sizeof(p2SortedValues));

    /* Suck up anything left at the end of the current record and   */
    /* discard                                                      */
    do
    {
      c = fgetc(inputFile);
    } while ( c != '\n');
  }               /* End of loop that processes each record         */

  printf("Arthur Henrique's Poker Program");
  printf("\n\nSummary:\n");
  printf("Total games: %d\n",total);
  printf("Player 1 total wins: %d Percentage %d%%\n",p1wins,
          p1wins*100/total);
  printf("Player 2 total wins: %d Percentage %d%%\n",p2wins,
          p2wins*100/total);

  printf("\nHand Occurrences: \n");
  printf("Total Hands Analyzed: %d\n",totalHand);
  printf("Royal Flushes: %d (%d%%) \n",totalRoyalFlush,
          totalRoyalFlush*100/totalHand);
  printf("Straight Flushes: %d (%d%%)\n",totalStraightFlush,
          totalStraightFlush*100/totalHand);
  printf("Four of a Kinds: %d (%d%%) \n",totalFourKind,
          totalFourKind*100/totalHand);
  printf("Full Houses: %d (%d%%)\n",totalFullHouse,
          totalFullHouse*100/totalHand);
  printf("Flushes: %d (%d%%)\n",totalFlush,
          totalFlush*100/totalHand);
  printf("Straights: %d (%d%%)\n",ttlStraight,
          ttlStraight*100/totalHand);
  printf("Three of a Kinds: %d (%d%%)\n",totalThreeKind,
          totalThreeKind*100/totalHand);
  printf("Two Pairs: %d (%d%%)\n",totalTwoPair,
          totalTwoPair*100/totalHand);
  printf("One Pairs: %d (%d%%)\n",totalOnePair,
          totalOnePair*100/totalHand);
  printf("High Cards: %d (%d%%)\n",totalHigh,
          totalHigh*100/totalHand);


/********************************************************************/
/*     Close input file                                             */
/********************************************************************/
  fclose(inputFile);
/********************************************************************/
/*     Return from the program                                      */
/********************************************************************/
  return 0;
}
/********************************************************************/
/*  Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.         */
/*  receives values[] -> return 0 or 1                              */
/********************************************************************/
int isRoyal(int values[])
{
   int i;
   int cardCount = 0;

   for (i=TEN; i <= ACE ;i++)
   {
      if (values[i]==1)
    {
      cardCount++;
      if (cardCount==5)
        return 1;
      }
      else
      cardCount =  0;
   }
   return 0;
}
/********************************************************************/
/*                                                                  */
/* Subroutine isFlush returns 1 if the input hand is a Flush (all   */
/* cards of the same suit) and returns 0 if the input hand is not a */
/* Flush.                                                           */
/*                                                                  */
/* The input for this function is an array of five items of the type*/
/* "cards" -- this is the hand itself as read from the input file   */
/*                                                                  */
/********************************************************************/
int isFlush(struct cards hand[])
{
  if (hand[0].cardsuit==hand[1].cardsuit &
      hand[0].cardsuit==hand[2].cardsuit &
      hand[0].cardsuit==hand[3].cardsuit &
      hand[0].cardsuit==hand[4].cardsuit)
    return 1;
  return 0;
}

/********************************************************************/
/*                                                                  */
/* Subroutine isStraight returns 1 if the input hand is a Straight  */
/* (values of all cards are sequential) and returns 0 if the input  */
/* hand is not a Straight.                                          */
/*                                                                  */
/* The input for this function is an array of 14 int values         */
/* (one for each card rank) depicting how many times the correspond-*/
/* ing card rank was found in the hand.                             */
/********************************************************************/
int isStraight(int values[])
{
  int i;
  int cardCount;          /* How many consecutive neighboring       */
                          /* entries in the values array have been  */
                          /* found with a value of 1. If we get up  */
                          /* to five, then we know the hand is a    */
                          /* straight.                              */

  if (values[ACE]==1)     /* Account for the A-2-3-4-5 straight     */
    cardCount = 1;
  else
    cardCount = 0;

  for (i=0;i<=ACE;i++)
  {
    if (values[i]==1)
      {
        cardCount++;
        if (cardCount == 5)
          return 1;
      }
    else
      cardCount = 0;      /* Back to zero cards in a row            */
  }
  return 0;
}

/********************************************************************/
/*                                                                  */
/* Subroutine getValue returns the value (of enumerated data type   */
/* VALUES) corresponding with the input character.                  */
/*                                                                  */
/********************************************************************/
int getValue(char val)
{

  if (val=='A')
    return ACE;
  if (val=='K')
    return KING;
  if (val=='Q')
    return QUEEN;
  if (val=='J')
    return JACK;
  if (val=='T')
    return TEN;
  if (val=='9')
    return NINE;
  if (val=='8')
    return EIGHT;
  if (val=='7')
    return SEVEN;
  if (val=='6')
    return SIX;
  if (val=='5')
    return FIVE;
  if (val=='4')
    return FOUR;
  if (val=='3')
    return THREE;
  if (val=='2')
    return TWO;
  return 0;
}

/********************************************************************/
/*                                                                  */
/* Subroutine getPrint returns the character representation         */
/* corresponding with the input int value.                          */
/*                                                                  */
/********************************************************************/
char getPrint(int val)
{

  if (val==ACE)
    return 'A';
  if (val==KING)
    return 'K';
  if (val==QUEEN)
    return 'Q';
  if (val==JACK)
    return 'J';
  if (val==TEN)
    return 'T';
  if (val==NINE)
    return '9';
  if (val==EIGHT)
    return '8';
  if (val==SEVEN)
    return '7';
  if (val==SIX)
    return '6';
  if (val==FIVE)
    return '5';
  if (val==FOUR)
    return '4';
  if (val==THREE)
    return '3';
  if (val==TWO)
    return '2';
  return 'X';
}

/********************************************************************/
/*                                                                  */
/* Subroutine countCards processes the values[] array and produces  */
/* two output arrays: sortedValues[] and frequency[].               */
/*                                                                  */
/* sortedValues will be an array of up to five int values           */
/* representing the values of the cards in the hand.                */
/*                                                                  */
/* frequency will be an array of up to 5 int values representing    */
/* how often each value in the sortedValues array appears in the    */
/* hand.  The values in frequency will be largest to smallest.      */
/*                                                                  */
/* Examples:                                                        */
/*   If the hand is 5D 4D 7H 2S 2C then:                            */
/*     values[] = {1,0,1,1,0,1,0,0,0,0,0,0,0}                       */
/*     sortedValues[] = {2,7,5,4}                                   */
/*     frequency[] = {2,1,1,1}                                      */
/*     The hand contains a pair.                                    */
/*                                                                  */
/*   If the hand is 3D 3C 3H 3S AC then:                            */
/*     values[] = {0,4,0,0,0,0,0,0,0,0,0,0,1}                       */
/*     sortedValues[] = {3,14}                                      */
/*     frequency[] = {4,1}                                          */
/*     The hand contains a four of a kind.                          */
/*                                                                  */
/*   If the hand is 3D 4D 8D JD AH then:                            */
/*     values[] = {0,1,1,0,0,0,1,0,0,1,0,0,1}                       */
/*     sortedValues[] = {14,11,8,4,3}                               */
/*     frequency[] = {1,1,1,1,1}                                    */
/*     The hand contains a high-card ace.                           */
/*                                                                  */
/*   If the hand is 4D 2H 4H 4S 2D then:                            */
/*     values[] = {2,0,3,0,0,0,0,0,0,0,0,0,0}                       */
/*     sortedValues[] = {4,2}                                       */
/*     frequency[] = {3,2}                                          */
/*     The hand contains a full house.                              */
/*                                                                  */
/********************************************************************/
void countCards(int values[], int sortedValues[], int frequency[])
{

  int i,j;

  j = 0;
  for (i=ACE;i>=TWO;i--)
  {
    if (values[i]==4)
    {
      /* Player got a 4 of a kind */
      frequency[j] = 4;
      sortedValues[j] = i;
      j++;
    }
  }

  for (i=ACE;i>=TWO;i--)
  {
    if (values[i]==3)
    {
      /* Player got a 3 of a kind */
      frequency[j] = 3;
      sortedValues[j] = i;
      j++;
    }
  }
  for (i=ACE;i>=TWO;i--)
  {
    if (values[i]==2)
    {
      frequency[j] = 2;
      sortedValues[j] = i;
      j++;
    }
  }
  for (i=ACE;i>=TWO;i--)
  {
    if (values[i]==1)
    {
      frequency[j] = 1;
      sortedValues[j] = i;
      j++;
    }
  }
  return;
}

/********************************************************************/
/*                                                                  */
/* Subroutine scoreHand processes the hand[] array, which is the    */
/* input read from the file cast as five objects of type "cards"    */
/* and produces two outputs: the sortedValues[] array, which is an  */
/* array of up to five integer values showing how up to five unique */
/* card values that were found in the hand, and the return value for*/
/* the subroutine, which is the score assigned to the hand.         */
/*                                                                  */
/********************************************************************/
int scoreHand(struct cards hand[], int sortedValues[])
{
  int handVal = 0;        /* Return value - score for the hand      */
  int i;
  int values[15] = { 0 }; /* Values array - how many times each     */
                          /* card rank appears in the hand. The     */
                          /* first two items in this array          */
                          /* (values[0] and values[1] are not used  */
                          /* so that the position in the array      */
                          /* matches up to the card's value, ie     */
                          /* values[2] is the number of 2s in the   */
                          /* hand and can be expressed as           */
                          /* values[TWO] (remember that TWO = 2 as  */
                          /* defined in the enumeration, and        */
                          /* remember that arrays in C are zero-    */
                          /* origin, that is the first entry is     */
                          /* always array[0]).                      */
  int frequency[5] = { 0 }; /* Frequency array - how many times     */
                          /* each entry in the sortedValues array   */
                          /* appears in the hand.                   */

  for (i=0;i<=sizeof(hand);i++) /* For each card in the hand, tick  */
                          /* up the entry in the values array that  */
                          /* corresponds to the matching card rank. */
  {
    values[getValue(hand[i].cardvalue)]++;
  }

  /* Now call countCards to generate the sortedValues and frequency */
  /* arrays. The prolog to countCards gives a few examples of how   */
  /* this works.                                                    */
  countCards(&values[0],&sortedValues[0],&frequency[0]);
                          /* Note that an entire array is passed    */
                          /* to a function by passing the address   */
                          /* of the first entry (&array[0] is the   */
                          /* address of the first entry, array[0] is*/
                          /* the value of the first entry).         */

  /* Now see if the hand is a flush and/or a straight, which are the*/
  /* hand types for which all five cards matter (ie all must be the */
  /* same suit, or all five values must be consecutive). Note that  */
  /* the hand could be a straight flush OR just a straight OR just  */
  /* a flush. Note also that the hand could be a royal flush (ie    */
  /* it is a straight flush where the highest card is an ace) but   */
  /* that distinction is not (yet) made in the code.                */

  totalHand++;

  if (isStraight(&values[0]) && !isRoyal(&values[0]))
  {
    handVal += STRAIGHT;
    if (isFlush(&hand[0]))
    {
      totalStraightFlush++;

      handVal += FLUSH;
      if (debug)
        printf("Straight Flush, high card %c",
               getPrint(sortedValues[0]));
    }
    else
    {
      ttlStraight++;
      if (debug)
        printf("Straight, high card %c",getPrint(sortedValues[0]));
    }

  }
  /* Royal Flush */
  else if (isRoyal(&values[0]))
  {
    if (isFlush(&hand[0]))
    {
      totalRoyalFlush++;
      handVal += ROYAL;
      handVal += FLUSH;
      if (debug)
        printf("Royal Flush, high card %c",
               getPrint(sortedValues[0]));
    }
    else
      if (debug)
        printf("No Royal, high card %c",getPrint(sortedValues[0]));
  }
  /* Flush */
  else if (isFlush(&hand[0]))
  {
    totalFlush++;

    handVal += FLUSH;
    if (debug)
      printf("Flush, high card %c",getPrint(sortedValues[0]));
  }

  /* After we see if the hand is a flush and/or a straight, we can  */
  /* evaluate it to see if it is a different hand type.             */
  /* Note that the following is a giant if-else if-else if-else     */
  /* clause: only one will be true                                  */
  if (frequency[0]==4)
  {
    totalFourKind++;

    handVal += FOURKIND;
    if (debug)
      printf("Four of a kind %c",getPrint(sortedValues[0]));
  }
  else if (frequency[0]==3)
    {
      if (frequency[1]==2)
      {
        totalFullHouse++;

        handVal += FULLHOUSE;
        if (debug)
          printf("Full house %cs and %cs",getPrint(sortedValues[0]),
                 getPrint(sortedValues[1]));
      }
      else
      {
        totalThreeKind++;

        handVal += THREEKIND;
        if (debug)
          printf("Three of a kind %cs with a %c and a %c",
                 getPrint(sortedValues[0]),getPrint(sortedValues[1]),
                 getPrint(sortedValues[2]));
      }
    }
  else if (frequency[0]==2)
    {
      if (frequency[1]==2)
      {
        totalTwoPair++;

        handVal += TWOPAIR;
        if (debug)
          printf("Two pair %cs and %cs with a %c",
                 getPrint(sortedValues[0]),getPrint(sortedValues[1]),
                 getPrint(sortedValues[2]));
      }
      else
      {
        totalOnePair++;

        handVal += ONEPAIR;
        if (debug)
          printf("One pair %cs with a %c and a %c and a %c",
                 getPrint(sortedValues[0]),getPrint(sortedValues[1]),
                 getPrint(sortedValues[2]),getPrint(sortedValues[3]));
      }
    }

  /* If handVal is still zero, that means the hand wasn't any other */
  /* rank and therefore will only win against another "high card"   */
  /* hand if it has the highest valued card.                        */
  if (handVal == 0)
  {
    totalHigh++;

    if (debug)
      printf("High Card %c %c %c %c %c",getPrint(sortedValues[0]),
             getPrint(sortedValues[1]),getPrint(sortedValues[2]),
             getPrint(sortedValues[3]),getPrint(sortedValues[4]));
  }

  if (debug)
    printf("\n");
  /* Return the value (score) of the hand                           */
  return handVal;

  }

/********************************************************************/
/*                                                                  */
/* Subroutine chooseWinner determines which of two input players is */
/* the winner for a hand.                                           */
/*                                                                  */
/* If score0 differs from score1 that means the players had         */
/* different hands (for example, a full house and a three of a      */
/* kind). If score0 is the same as score1 then the players had the  */
/* same hand (two straights, for example) and the ranks of the cards*/
/* must be analyzed.                                                */
/*                                                                  */
/* If the first value/score pair is the winner, then the subroutine */
/* returns 1.                                                       */
/* If the second value/score pair is the winner, then the subroutine*/
/* returns 0.                                                       */
/*                                                                  */
/********************************************************************/
int chooseWinner(int values0[],int score0,int values1[],int score1)
{
  int i;

    if (score0 > score1) /* The first player had a better hand     */
        return 1;
    else if (score1 > score0) /* The second player had a better    */
                          /* hand                                   */
        return 0;
    else                 /* The players had the same hand. Compare */
                          /* values of the cards to determine       */
                          /* winner.                                */
    {
       for (i=0;i<5;i++)
       {
         if (values0[i]>values1[i])
            return 1;
         else if (values1[i]>values0[i])
            return 0;
        }
    }
}
}