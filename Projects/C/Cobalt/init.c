#include "defs.h"

#pragma region BOARD DATA

int Sq120ToSq64[BRD_SQ_NUM];
int Sq64ToSq120[64];

U64 SetMask[64];
U64 ClearMask[64];

U64 PieceKeys[13][120];
U64 SideKey;
U64 CastleKeys[16];

int FilesBrd[BRD_SQ_NUM];
int RanksBrd[BRD_SQ_NUM];

#pragma endregion BOARD DATA

#pragma region INLINE FUNCTIONS

/**
 * This function generates a random 64 bit number.
 * @return A random 64 bit number.
 */
static inline U64 RAND_64()
{
        return (U64)rand() | ((U64)rand() << 15) | ((U64)rand() << 30) | ((U64)rand() << 45) | (((U64)rand() & 0xf) << 60);
}

#pragma endregion INLINE FUNCTIONS

#pragma region FUNCTIONS

/**
 * This function initializes the arrays FilesBrd and RanksBrd.
 * FilesBrd contains the file of the square.
 * RanksBrd contains the rank of the square.
 */
void InitFilesRanksBrd()
{
        int index = 0;
        int file = FILE_A;
        int rank = RANK_1;
        int sq = A1;

        ///< Initialize the arrays to invalid values
        for (index = 0; index < BRD_SQ_NUM; ++index)
        {
                FilesBrd[index] = OFFBOARD;
                RanksBrd[index] = OFFBOARD;
        }

        ///< Loop through the ranks and files to initialize the arrays
        for (rank = RANK_1; rank <= RANK_8; ++rank)
        {
                for (file = FILE_A; file <= FILE_H; ++file)
                {
                        sq = FileRankToSquare(file, rank);
                        FilesBrd[sq] = file;
                        RanksBrd[sq] = rank;
                }
        }
}

/**
 *This function initializes the arrays PieceKeys, SideKey, and CastleKeys.
 *PieceKeys is a 13x120 array that contains random 64 bit numbers for each piece on each square.
 *SideKey is a random 64 bit number for the side to move.
 *CastleKeys is a 16 element array that contains random 64 bit numbers for each castle permission.
 */
void InitHashKeys()
{
        int index = 0;
        int index2 = 0;

        ///< Loop through the pieces and squares to initialize the PieceKeys array
        for (index = 0; index < NUMBER_OF_PIECES; ++index)
        {
                for (index2 = 0; index2 < BRD_SQ_NUM; ++index2)
                {
                        PieceKeys[index][index2] = RAND_64();
                }
        }

        SideKey = RAND_64(); ///< Initialize the SideKey

        ///< Loop through the castle permissions to initialize the CastleKeys array
        for (index = 0; index < ARRLEN(CastleKeys); ++index)
        {
                CastleKeys[index] = RAND_64();
        }
}

/**
 *This function initializes the arrays SetMask and ClearMask.
 *SetMask is a 64 element array that contains a bit mask with a single bit set at the index.
 *ClearMask is a 64 element array that contains a bit mask with all bits set except for the bit at the index.
 */
void InitBitMasks()
{
        int index = 0;
        ///< Loop through the indices to initialize the arrays
        for (index = 0; index < ARRLEN(SetMask); index++)
        {
                SetMask[index] = 1ULL << index;
                ClearMask[index] = ~SetMask[index];
        }
}

/**
 *This function initializes the arrays Sq120ToSq64 and Sq64ToSq120.
 *The former is a 120 element array that maps 120 based squares to 64 based squares.
 *The latter is a 64 element array that maps 64 based squares to 120 based squares.
 */
void InitSq120To64()
{

        int index = 0;
        int file = FILE_A;
        int rank = RANK_1;
        int sq = A1;
        int sq64 = 0;

        ///< Initialize the arrays to invalid values
        for (index = 0; index < BRD_SQ_NUM; ++index)
        {
                Sq120ToSq64[index] = 65;
        }

        ///< Initialize the arrays to invalid values
        for (index = 0; index < ARRLEN(Sq64ToSq120); ++index)
        {
                Sq64ToSq120[index] = 120;
        }

        ///< Loop through the ranks and files to initialize the arrays
        for (rank = RANK_1; rank <= RANK_8; ++rank)
        {
                for (file = FILE_A; file <= FILE_H; ++file)
                {
                        sq = FileRankToSquare(file, rank);
                        Sq64ToSq120[sq64] = sq;
                        Sq120ToSq64[sq] = sq64;
                        sq64++;
                }
        }
}

/**
 * This function initializes all the arrays.
 */
void AllInit()
{
        InitSq120To64();
        InitBitMasks();
        InitHashKeys();
        InitFilesRanksBrd();
}

#pragma endregion FUNCTIONS