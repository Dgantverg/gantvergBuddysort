# gantvergBuddysort
Gantverg's implementation of buddy sort algorithm written in C. The base was created by the GBS team at the TU Munich, the algorithmic idea was implemented by me. 

Form:
$./ buddy . out -h

Usage : ./ buddy . out [-b BLOCKSIZE ] [-n NUM_BLOCKS ]
BLOCKSIZE : integer , interpreted as kiB (i.e. -b 4 => 4096 Bytes ). Has to be power of 2! The default
is 4.
NUM_BLOCKS : integer , number of blocks to be used . Has to be power of 2! The default is 32.

Example: for b = block of 4 (4Kilibytes) and 32 blocks:
$./ buddy . out -b 4 -n 8

Use with run buddy.c, add buddy.c as a runnable file in c/c++ files
