#include "stdio.h"
#include "defs.h"

///< The following array contains the index of the least significant bit set in a 64 bit number.
const int BitTable[64] = {
    63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
    51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
    26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
    58, 20, 37, 17, 36, 8};

#pragma region FUNCTIONS

/**
 * This function returns the index of the least significant bit set in the bitboard.
 * @param[in] bb: the bitboard.
 * @param[out] leastSigBit: the index of the least significant bit set in the bitboard.
 */
int PopBit(U64 *bb)
{
        U64 b = *bb ^ (*bb - 1); ///< Extract the isolated least significant bit set in b

        unsigned int fold = (unsigned)((b & 0xffffffff) ^ (b >> 32)); ///< XOR the lower and upper 32 bits and store in fold

        *bb &= (*bb - 1);                                      ///< Remove the least significant bit from the board
        int leastSigBit = BitTable[(fold * 0x783a9b23) >> 26]; ///< Get the index of the least significant bit from the BitTable
        return leastSigBit;
}

/**
 * This function returns the number of bits set in the bitboard.
 * @param[in] b: the bitboard.
 * @param[out] r: the number of bits set in the bitboard.
 */
int CountBits(U64 b)
{
        int r;
        for (r = 0; b; r++, b &= b - 1)
                ;
        return r;
}

/**
 * This function prints the bitboard.
 * @param[in] bb: the bitboard.
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
                        sq = FR2SQ(file, rank);
                        sq64 = SQ64(sq);
                        if ((shiftMe << sq64) & bb)
                                printf("X");
                        else
                                printf("-");
                }
                printf("\n");
        }
}

#pragma endregion FUNCTIONS