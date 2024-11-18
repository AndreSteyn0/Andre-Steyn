#include "defs.h"

int Sq120ToSq64[BRD_SQ_NUM];
int Sq64ToSq120[64];

U64 SetMask[64];
U64 ClearMask[64];

U64 PieceKeys[13][120];
U64 SideKey;
U64 CastleKeys[16];

int FilesBrd[BRD_SQ_NUM];
int RanksBrd[BRD_SQ_NUM];

/*
        This function initializes the arrays FilesBrd and RanksBrd.
        FilesBrd is a 120 element array that contains the file of the square.
        RanksBrd is a 120 element array that contains the rank of the square.
*/
void InitFilesRanksBrd()
{
        int index = 0;
        int file = FILE_A;
        int rank = RANK_1;
        int sq = A1;

        for (index = 0; index < BRD_SQ_NUM; ++index)
        {
                FilesBrd[index] = OFFBOARD;
                RanksBrd[index] = OFFBOARD;
        }

        for (rank = RANK_1; rank <= RANK_8; ++rank)
        {
                for (file = FILE_A; file <= FILE_H; ++file)
                {
                        sq = FR2SQ(file, rank);
                        FilesBrd[sq] = file;
                        RanksBrd[sq] = rank;
                }
        }
}

/*
  This function initializes the arrays PieceKeys, SideKey, and CastleKeys.
  PieceKeys is a 13x120 array that contains random 64 bit numbers for each piece on each square.
  SideKey is a random 64 bit number for the side to move.
  CastleKeys is a 16 element array that contains random 64 bit numbers for each castle permission.
*/
void InitHashKeys()
{
        int index = 0;
        int index2 = 0;
        for (index = 0; index < 13; ++index)
        {
                for (index2 = 0; index2 < 120; ++index2)
                {
                        PieceKeys[index][index2] = RAND_64();
                }
        }
        SideKey = RAND_64();
        for (index = 0; index < 16; ++index)
        {
                CastleKeys[index] = RAND_64();
        }
}

/*
  This function initializes the arrays SetMask and ClearMask.
  SetMask is a 64 element array that contains a bit mask with a single bit set at the index.
  ClearMask is a 64 element array that contains a bit mask with all bits set except for the bit at the index.
*/
void InitBitMasks()
{
        int index = 0;
        for (index = 0; index < 64; index++)
        {
                SetMask[index] = 1ULL << index;
                ClearMask[index] = ~SetMask[index];
        }
}

/*
  This function initializes the arrays Sq120ToSq64 and Sq64ToSq120.
  The former is a 120 element array that maps 120 based squares to 64 based squares.
  The latter is a 64 element array that maps 64 based squares to 120 based squares.
*/
void InitSq120To64()
{

        int index = 0;
        int file = FILE_A;
        int rank = RANK_1;
        int sq = A1;
        int sq64 = 0;

        // Initialize the arrays to invalid values
        for (index = 0; index < BRD_SQ_NUM; ++index)
        {
                Sq120ToSq64[index] = 65;
        }

        // Initialize the arrays to invalid values
        for (index = 0; index < 64; ++index)
        {
                Sq64ToSq120[index] = 120;
        }

        // Loop through the ranks and files to initialize the arrays
        for (rank = RANK_1; rank <= RANK_8; ++rank)
        {
                for (file = FILE_A; file <= FILE_H; ++file)
                {
                        sq = FR2SQ(file, rank);
                        Sq64ToSq120[sq64] = sq;
                        Sq120ToSq64[sq] = sq64;
                        sq64++;
                }
        }
}

void AllInit()
{
        InitSq120To64();
        InitBitMasks();
        InitHashKeys();
        InitFilesRanksBrd();
}