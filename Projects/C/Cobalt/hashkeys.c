///< hashkeys.c

#include "defs.h"

/**
 * This function generates a random 64 hash key.
 * @param[in] pos: the board.
 * @param[out] finalKey: A random 64 hash key.
 */
U64 GeneratePosKey(const S_BOARD *pos)
{
        int sq = 0;
        U64 finalKey = 0;
        int piece = EMPTY;

        ///< Loop through the squares to generate the hash key
        for (sq = 0; sq < BRD_SQ_NUM; ++sq)
        {
                piece = pos->pieces[sq];
                if (piece != NO_SQ && piece != OFFBOARD && piece != EMPTY)
                {
                        ASSERT(piece >= wP && piece <= bK);
                        finalKey ^= PieceKeys[piece][sq];
                }
        }

        ///< If it is white's turn, xor the SideKey
        if (pos->side == WHITE)
        {
                finalKey ^= SideKey;
        }

        ///< If there is an en passant square, xor the PieceKeys array with the en passant square
        if (pos->enPas != NO_SQ)
        {
                ASSERT(pos->enPas >= 0 && pos->enPas < BRD_SQ_NUM);
                finalKey ^= PieceKeys[EMPTY][pos->enPas];
        }

        ASSERT(pos->castlePerm >= 0 && pos->castlePerm <= 15);

        finalKey ^= CastleKeys[pos->castlePerm]; ///< xor the CastleKeys array with the castle permissions

        return finalKey;
}