# ga-block-cipher

** Basic algorithm work only, pluggable internals in development **

This project aims to evolve novel block ciphers using a genetic algorithm.

## DNA

The encoding will be the pluggable pieces that comprise the final cipher.

An incomplete selection of attributes for the encoding.

1. Feistel/substitution-permutation network
2. Key scheduling algorithm
3. Key derivation function
4. Modified network (unbalanced feistel, modified for half-rounds, etc.)
5. Metamorphic engine (See Stone Cipher paper)
6. Block size
7. Binary operation chains for words in block
8. Magic constants/S-Boxes and P-Boxes
9. Mode of operation
10. ... Allow encoding expansion for novel exploration

## Fitness Rating

A weighted system of the following

1. Successful encryption/decryption
2. Quantitatively measure confusion/diffusion (need to reflect on Shannon's papers)
3. Speed
4. Complexity
5. Fuzzing survival (AFL++ when this stage is reached)

## Clustering of Individuals

Clustering is to be determined by the Damerau-Levenshtein optimal string alignment distance. To ensure diversity while also helping like-individuals, two clusters will be made per similar individual type. One with more like individuals and one with the most unlike individuals in the gene pool.

## Evolution Process

```
- Selection (select most fit parents or create the initial parents)
- Crossover DNA (create the offspring)
- DNA mutation based on defined rate (part of novel exploration)
- Run mutated offspring through survival test (pre-fitness, determines natural selection)
    - Block cipher assembler (reads encoding and pieces together network/binary operations, etc)
    - The LLVM IR (preferred)/C-code output by the assembler is compiled with hooks for the fitness test in place.
- Rate fitness
- Rank in gene pool
- Repeat
```
