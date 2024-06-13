# File-Compression-Tool-Huffman

Overview
This project implements a file compression tool using Huffman coding in C++. Huffman coding is a fundamental algorithm used for lossless data compression, where frequently occurring characters are assigned shorter codes, and less frequent characters are assigned longer codes. This approach minimizes the overall size of the encoded data, enabling efficient storage and transmission of information.
What is Huffman Coding?
Huffman coding is a prefix-free encoding technique that assigns variable-length codes to input characters based on their frequencies of occurrence. The key idea behind Huffman coding is to use shorter codes for more frequent characters and longer codes for less frequent characters, thus minimizing the average number of bits required to encode the data.

# How Huffman Coding Works
Frequency Analysis: Calculate the frequency of each character in the input text.
Priority Queue: Build a priority queue of nodes, where each node represents a character along with its frequency.
Huffman Tree Construction: Build the Huffman tree by repeatedly merging the two nodes with the lowest frequencies until only one node remains.
Generate Huffman Codes: Traverse the Huffman tree to generate unique binary codes (Huffman codes) for each character. These codes are used for compression and decompression.
Encoding: Replace each character in the input text with its corresponding Huffman code to create the encoded binary data.
Decoding: Traverse the Huffman tree again using the encoded binary data to reconstruct the original text.
Usage
The compressed binary file (encoded.bin) will be generated in the same directory.
The decoded text file (decoded.txt) will be created to verify the decoding process.
