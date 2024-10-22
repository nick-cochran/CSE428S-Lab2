# CSE428S-Lab1

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