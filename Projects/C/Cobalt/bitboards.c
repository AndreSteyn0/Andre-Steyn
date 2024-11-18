#include "stdio.h"
#include "defs.h"

// TODO: The BitTable and PopBit function can be optimized:
// 1. The BitTable can be removed and the PopBit function can be converted to an inline function.
// 2. The BitTable table can be initialized in the init.c file.
const int BitTable[64] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};

/*
  This function returns the index of the least significant bit set in the bitboard.
*/
int PopBit(U64 *bb)
{
        U64 b = *bb ^ (*bb - 1);                                      // Extract the isolated least significant bit set in b
        unsigned int fold = (unsigned)((b & 0xffffffff) ^ (b >> 32)); // XOR the lower and upper 32 bits and store in fold
        *bb &= (*bb - 1);                                             // Remove the least significant bit from the board
        return BitTable[(fold * 0x783a9b23) >> 26];                   // Get the index of the least significant bit from the BitTable
}

/*
  This function returns the number of bits set in the bitboard.
*/
int CountBits(U64 b)
{
        int r;
        for (r = 0; b; r++, b &= b - 1)
                ;
        return r;
}

/*
  This function prints the bitboard.
*/
void PrintBitBoard(U64 bb)
{
        U64 shiftMe = 1ULL;

        int rank, file, sq, sq64;

        printf("\n");
        for (rank = RANK_8; rank >= RANK_1; rank--)
        {
                for (file = FILE_A; file <= FILE_H; file++)
                {
                        sq = FR2SQ(file, rank); // 120 based
                        sq64 = SQ64(sq);        // 64 based
                        if ((shiftMe << sq64) & bb)
                                printf("X");
                        else
                                printf("-");
                }
                printf("\n");
        }
}