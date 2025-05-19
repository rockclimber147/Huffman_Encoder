# Huffman Encoder & Decoder

This project is a simple C implementation of **Huffman encoding** for compressing and decompressing text files. It was coded as part of the COMP 2510 - Procedural programming course for the CST program at BCIT. 

## Features

- Reads a text file and builds a character frequency table.
- Constructs a Huffman tree from character frequencies.
- Generates Huffman codewords for each character.
- Encodes the input file using the codewords and outputs a compressed file.
- Decodes the compressed file back to the original text.
- Displays size statistics to show compression efficiency.

## File Structure

```
project/
├── main.c               # Main driver file
├── lookups.h            # Header for character frequency and codeword helpers
├── hnode.h              # Header for Huffman tree nodes and related functions
├── priorityQueue.h      # Header for priority queue used in tree construction
├── createTree.h         # Header for building the Huffman tree
├── UnitTests.h          # Header for unit testing utilities
├── LookupTest.txt       # Example input file
├── OUT_LookupTest.txt   # Compressed output file
├── DEC_LookupTest.txt   # Decoded output file
└── README.md            # Project documentation
```

## How It Works

1. **Read Input:** Reads `LookupTest.txt` and builds a frequency table.
2. **Build Tree:** Constructs a Huffman tree using a priority queue.
3. **Generate Codes:** Assigns binary codes to characters based on the tree.
4. **Encode File:** Writes compressed output to `OUT_LookupTest.txt`.
5. **Decode File:** Decodes it back to `DEC_LookupTest.txt`.
6. **Stats:** Displays original/compressed sizes and compression ratio.

## Compile Instructions

Use `gcc` to compile:

```bash
gcc -o huffman main.c lookups.c hnode.c priorityQueue.c createTree.c UnitTests.c
```

## Run Instructions

```bash
./huffman
```

The program uses `"LookupTest.txt"` as the input file by default. You can modify `main.c` to change the filename.

## Example Output

```
LookupTest.txt uses 1190 bits at 7 bits per character

The character counts for LookupTest.txt are:
...

The codewords are:
...

Bits needed to encode: 654
output file is 45.04% smaller than input file

Decoding to DEC_LookupTest.txt
```

## Notes

- Assumes ASCII characters using 7 bits per character.
- Encoded data is stored as text using `'0'` and `'1'` characters.
- Only printable characters are supported.
