/**
 * @file attack.c
 * @brief This file contains the functions that check if a square is attacked.
 */

#include "defs.h"

///< The following arrays contain the directions that each piece can move in.
const int KnDir[8] = {-8, -19, -21, -12, 8, 19, 21, 12};
const int RkDir[4] = {-1, -10, 1, 10};
const int BiDir[4] = {-9, -11, 11, 9};
const int KiDir[8] = {-1, -10, 1, 10, -9, -11, 11, 9};

/**
 * This function checks if a square is attacked by a piece.
 * @param[in] sq: the square to check.
 * @param[in] attackingSide: the side that is attacking.
 * @param[in] pos: the board.
 * @return TRUE if the square is attacked, FALSE otherwise.
 */
int SqAttacked(const int sq, const int attackingSide, const S_BOARD *pos)
{
        int piece, index, t_sq, dir;

        ASSERT(SqOnBoard(sq));
        ASSERT(SideValid(attackingSide));
        ASSERT(CheckBoard(pos));

        ///< Check for pawns
        if (attackingSide == WHITE)
        {
                if (pos->pieces[sq - 11] == wP || pos->pieces[sq - 9] == wP)
                {
                        return TRUE;
                }
        }
        else
        {
                if (pos->pieces[sq + 11] == bP || pos->pieces[sq + 9] == bP)
                {
                        return TRUE;
                }
        }

        ///< Check for knights
        for (index = 0; index < ARRLEN(KnDir); ++index)
        {
                piece = pos->pieces[sq + KnDir[index]];
                if (piece != OFFBOARD && IsKn(piece) && PieceCol[piece] == attackingSide)
                {
                        return TRUE;
                }
        }

        ///< Check for rooks and queens
        for (index = 0; index < ARRLEN(RkDir); ++index)
        {
                dir = RkDir[index];
                t_sq = sq + dir;
                piece = pos->pieces[t_sq];
                while (piece != OFFBOARD)
                {
                        if (piece != EMPTY)
                        {
                                if (IsRQ(piece) && PieceCol[piece] == attackingSide)
                                {
                                        return TRUE;
                                }
                                break;
                        }
                        t_sq += dir;
                        piece = pos->pieces[t_sq];
                }
        }

        ///< Check for bishops and queens
        for (index = 0; index < ARRLEN(BiDir); ++index)
        {
                dir = BiDir[index];
                t_sq = sq + dir;
                piece = pos->pieces[t_sq];
                while (piece != OFFBOARD)
                {
                        if (piece != EMPTY)
                        {
                                if (IsBQ(piece) && PieceCol[piece] == attackingSide)
                                {
                                        return TRUE;
                                }
                                break;
                        }
                        t_sq += dir;
                        piece = pos->pieces[t_sq];
                }
        }

        ///< Check for kings
        for (index = 0; index < ARRLEN(KiDir); ++index)
        {
                piece = pos->pieces[sq + KiDir[index]];
                if (piece != OFFBOARD && IsKn(piece) && PieceCol[piece] == attackingSide)
                {
                        return TRUE;
                }
        }

        return FALSE;
}