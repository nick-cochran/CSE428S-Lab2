# CSE428S-Lab2

### Name: Nick Cochran

#### Email: c.nick@wustl.edu

---

## Testing

### Pinochle Melds

- I ran the program using the Pinochle parameters until I found at least 1 of each
    of the most common melds, and then I ran it until I found 1 of the much rarer 8 card melds.
    I also wanted to find at least one instance where a player had multiple melds.
    The first occurrence of each of these is below.
  - Player p2 has hand:
    
    K♣ Q♦ A♠ Q♥ A♥ J♠ A♦ 9♥ 10♥ K♦ Q♣ Q♠ 

    p2's melds: sixty queens 60
  - Player p3 has hand: 

    9♣ J♣ Q♥ Q♠ 9♦ K♥ J♠ A♣ K♠ J♦ K♥ K♦ 

    p3's melds: pinochle 40
  - Player p3 has hand: 

    9♥ K♦ Q♠ J♠ Q♣ 9♦ Q♠ K♠ Q♥ 10♣ K♣ K♥ 

    p3's melds: eighty kings 80
  - Player p3 has hand: 

    Q♣ K♥ 9♦ J♥ A♦ A♠ 10♠ J♠ J♣ K♣ A♥ A♣ 

    p3's melds: hundred aces 100 
  - Player p2 has hand: 

    K♦ J♣ J♠ 9♥ J♥ J♦ 9♦ A♣ 10♣ K♥ A♠ A♦ 

    p2's melds: forty jacks 40 
  - Player p4 has hand: 

    9♦ Q♠ Q♥ J♦ J♣ J♠ J♥ A♦ Q♠ K♥ J♦ Q♣ 
  
    p4's melds: forty jacks 40 double pinochle 300
  - Player p4 has hand: 

    K♥ K♥ Q♥ 10♦ A♦ K♠ K♠ K♦ J♥ K♣ K♦ K♣ 

    p4's melds: eight hundred kings 800 
    - Of note: This took a (probably broken) script and a long time to get.



## Design Choices

### Miscellaneous Changes/Choice

- I changed the Card Template, Suit, and both Pinochle and HoldEm Deck implementations
    of the << operator to print the cards in a more readable way, 
    also using the unicode and a red color (for hearts and diamonds) for each of the card suits.

### HoldEmGame Printing and Dealing

- The previous lab instructed me to print the hands and deal the hands inside of the play method,
    but I felt it important to note that I did this slightly differently.  In order to properly
    print the board before the state of the board changed, I called the printBoard method inside of 
    the deal method.

### CardSet Copy Constructor

- I decided to implement my own copy constructor for the CardSet class because I felt like that
    was the safer implementation.  This ensures the copy constructor does what I want it to do.

### Meld Values Static Variable

- For the static variable in the PinochleGame Class that holds the values for each of the melds,
    I decided to go with the recommended implementation from the instructions. With this,
    I did hardcode the values on initialization, but because arrays are const,
    it is not at risk of being altered from this correct mapping of each meld to its value,
    therefore, there is still something making it clear what each of these hardcoded values means.

### Suit Independent Evaluation Function

- When implementing this function there were many design choices made that I felt
    I should document here. 
- I chose to create a map of Pinochle ranks to a vector of suits, 
    where each card of that rank would have its rank stored.  I then filled this map's vectors, 
    and was ready to find the melds a hand may have.  To do this, I first check if there are 
    enough of each suit to possibly have a meld for that rank.  If there are, I check
    if there are 8 suits, in which case that hand has all of the cards of that rank,
    meaning they have one of the 8 card melds.  Otherwise, I call a helper function that checks
    if the vector holds at least one of each suit, and if so add one of the 4 card melds
    to the passed in reference of melds.  Finally, I go through and count the number of
    Jacks of Diamonds and Queens of Spades to evaluate if there is a pinochle or double pinochle.
- I also thought about modularity at many times while implementing this function which ended up quite long.
    In the end, I didn't break most things out into other functions that I considered doing so with,
    because I felt it would be more complicated and difficult to follow with the way I had implemented it,
    and the requirements for breaking something off into a separate function.

## Notes

- When using or not using auto could be a good thing to note in here.

___

___

# CSE428S-Lab1 OLD README

--- 

## Name: Nick Cochran

### Email: c.nick@wustl.edu


## Errors

I ran into a number of errors while working on this code.  Two that were particularly challenging
were linker errors which were caused by forgetting to remove the print method from the Deck class
and also forgetting to change Deck to a template header that includes the source.  I also ran into 
errors with the >> operator a few times that I fixed fairly quickly each time, but it took some
research to make sure I was using it right.  I also forgot to put a reference in the >> operator 
which took a bit to find and was fairly confusing as to why it wasn't working. 

# Trial Runs

I ran the program many times.  I started with Pinochle, first checking that it adequately checks
for the right amount of players, and then making sure the program was running correctly, with all
shuffling and cards given out making sense.  I then did the same with HoldEm with many different
runs checking each of those invariants.  All of these passed or were quickly fixed (the last error in that section).