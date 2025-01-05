/**
 * @file validate.c
 * @brief This file contains the functions that validate the board.
 */

#include "defs.h"

/**
 * This function validates a square.
 * @param[in] sq: the square.
 * @return 1 if the square is valid, 0 otherwise.
 */
int SqOnBoard(const int sq)
{
        return FilesBrd[sq] == OFFBOARD ? 0 : 1;
}

/**
 * This function validates a side.
 * @param[in] side: the side.
 * @return 1 if the side is valid, 0 otherwise.
 */
int SideValid(const int side)
{
        return side == WHITE || side == BLACK ? 1 : 0;
}

/**
 * This function validates a file.
 * @param[in] file: the file.
 * @return 1 if the file is valid, 0 otherwise.
 */
int FileRankValid(const int fr)
{
        return fr >= RANK_1 && fr <= RANK_8 ? 1 : 0;
}

/**
 * This function validates a piece.
 * @param[in] pce: the piece.
 * @return 1 if the piece is valid, 0 otherwise.
 */
int PieceValidEmpty(const int pce)
{
        return pce >= EMPTY && pce <= bK ? 1 : 0;
}

/**
 * This function validates a piece.
 * @param[in] pce: the piece.
 * @return 1 if the piece is valid, 0 otherwise.
 */
int PieceValid(const int pce)
{
        return pce >= wP && pce <= bK ? 1 : 0;
}