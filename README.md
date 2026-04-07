gantvergBuddysort

gantvergBuddysort is an implementation of the Buddy Sort algorithm written in C.

The project builds upon a base framework originally developed by the GBS team at the Technical University of Munich. The algorithmic logic and implementation of Buddy Sort were developed by the author.

📌 Overview

Buddy Sort is a memory-block-based sorting approach that operates on fixed-size blocks. This implementation allows configurable block sizes and numbers of blocks, both of which must be powers of two.

⚙️ Compilation & Execution

Make sure buddy.c is included in your project and compiled as an executable.

Compile
gcc buddy.c -o buddy.out
Run
./buddy.out [OPTIONS]
🧾 Usage
./buddy.out [-b BLOCKSIZE] [-n NUM_BLOCKS]
Parameters
-b BLOCKSIZE
Block size in KiB (kibibytes).
Must be a power of 2
Default: 4 (i.e., 4096 bytes)
-n NUM_BLOCKS
Number of blocks used in the algorithm.
Must be a power of 2
Default: 32
▶️ Example

Run the program with a block size of 4 KiB and 8 blocks:

./buddy.out -b 4 -n 8
⚠️ Notes
Both BLOCKSIZE and NUM_BLOCKS must be powers of two.
Invalid inputs may result in undefined behavior if not properly handled.

Ensure the executable has permission to run:

chmod +x buddy.out
🔗 Repository

GitHub repository:
https://github.com/Dgantverg/gantvergBuddysort

👤 Author

Developed by D. Gantverg

Base framework provided by the GBS team, Technical University of Munich.
