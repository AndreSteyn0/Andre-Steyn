/**
 * @file makemove.c
 * @brief This file contains the functions that make a move.
 */

#include "defs.h"

const int CastlePerm[120] = {
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 13, 15, 15, 15, 12, 15, 15, 14, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 7, 15, 15, 15, 3, 15, 15, 11, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15};

#pragma region INLINE FUNCTIONS

/**
 * This function XORs the piece on the board with the hash key.
 * @param[in] pos: the board.
 * @param[in] pce: the piece to XOR.
 * @param[in] sq: the square that the piece is on.
 */
static inline void HashPce(S_BOARD *pos, int pce, int sq)
{
        pos->hashKey ^= PieceKeys[pce][sq];
}

/**
 * This function XORs the castle permissions with the hash key.
 * @param[in] pos: the board.
 */
static inline void HashCA(S_BOARD *pos)
{
        pos->hashKey ^= CastleKeys[pos->castlePerm];
}

/**
 * This function XORs the side to move with the hash key.
 * @param[in] pos: the board.
 */
static inline void HashSide(S_BOARD *pos)
{
        pos->hashKey ^= SideKey;
}

/**
 * This function XORs the en passant square with the hash key.
 * @param[in] pos: the board.
 */
static inline void HashEP(S_BOARD *pos)
{
        pos->hashKey ^= PieceKeys[EMPTY][pos->enPas];
}

#pragma endregion INLINE FUNCTIONS

#pragma region FUNCTIONS

/**
 * This function clears a piece from the board.
 * @param[in] sq: the square to clear the piece from.
 * @param[in] pos: the board.
 */
static void ClearPiece(const int sq, S_BOARD *pos)
{
        ASSERT(SqOnBoard(sq));

        int pce = pos->pieces[sq];

        ASSERT(PieceValid(pce));

        int color = PieceCol[pce];
        int index = 0;
        int t_pceNum = -1; ///< Temporary piece index

        HashPce(pos, pce, sq); ///< Hash out the piece on the square

        pos->pieces[sq] = EMPTY;
        pos->material[color] -= PieceVal[pce];

        ///< Update the piece lists
        if (PieceMaj[pce])
        {
                pos->bigPiece[color]--;
                pos->majPiece[color]--;
        }
        else if (PieceMin[pce])
        {
                pos->bigPiece[color]--;
                pos->minPiece[color]--;
        }
        else
        {
                ClearBit(&pos->pawns[color], SQ64(sq));
                ClearBit(&pos->pawns[BOTH], SQ64(sq));
        }

        ///< Update the piece number
        for (index = 0; index < pos->pieceNum[pce]; ++index)
        {
                if (pos->pieceList[pce][index] == sq) ///< Find the piece in the piece list
                {
                        t_pceNum = index;
                        break;
                }
        }

        ASSERT(t_pceNum != -1);

        pos->pieceNum[pce]--;                                                    ///< Decrement the piece number
        pos->pieceList[pce][t_pceNum] = pos->pieceList[pce][pos->pieceNum[pce]]; ///< Move the last piece to the removed piece's place
}

/**
 * This function adds a piece to the board.
 * @param[in] sq: the square to add the piece to.
 * @param[in] pos: the board.
 */
static void AddPiece(const int sq, S_BOARD *pos, const int piece)
{
        ASSERT(PieceValid(piece));
        ASSERT(SqOnBoard(sq));

        int color = PieceCol[piece];

        HashPce(pos, piece, sq); ///< Hash in the piece on the square

        pos->pieces[sq] = piece;

        ///< Update the piece lists
        if (PieceMaj[piece])
        {
                pos->majPiece[color]++;
                pos->bigPiece[color]++;
        }
        else if (PieceMin[piece])
        {
                pos->minPiece[color]++;
                pos->bigPiece[color]++;
        }
        else
        {
                SetBit(&pos->pawns[color], SQ64(sq));
                SetBit(&pos->pawns[BOTH], SQ64(sq));
        }

        pos->material[color] += PieceVal[piece]; ///< Update the material

        ASSERT(pos->pieceNum[piece] >= 0 && pos->pieceNum[piece] < 10);

        pos->pieceList[piece][pos->pieceNum[piece]++] = sq; ///< Add the piece to the piece list
}

/**
 * This function moves a piece on the board.
 * @param[in] from: the square to move from.
 * @param[in] to: the square to move to.
 * @param[in] pos: the board.
 */
static void MovePiece(const int from, const int to, S_BOARD *pos)
{
        ASSERT(SqOnBoard(from));
        ASSERT(SqOnBoard(to));

        int index = 0;
        int piece = pos->pieces[from];
        int color = PieceCol[piece];

#ifdef DEBUG
        int t_PieceNum = FALSE; ///< For debugging purposes. TODO: Can be removed.
#endif

        ASSERT(PieceValid(piece));

        HashPce(pos, piece, from); ///< Hash out the piece on the old square
        pos->pieces[from] = EMPTY;

        HashPce(pos, piece, to); ///< Hash in the piece on the new square
        pos->pieces[to] = piece;

        ///< Update the pawn bitboards
        if (!PieceBig[piece])
        {
                ClearBit(&pos->pawns[color], SQ64(from));
                ClearBit(&pos->pawns[BOTH], SQ64(from));
                SetBit(&pos->pawns[color], SQ64(to));
                SetBit(&pos->pawns[BOTH], SQ64(to));
        }

        for (index = 0; index < pos->pieceNum[piece]; ++index)
        {
                if (pos->pieceList[piece][index] == from)
                {
                        pos->pieceList[piece][index] = to; ///< Move the piece to the new square
#ifdef DEBUG
                        t_PieceNum = TRUE; ///< For debugging purposes. TODO: Can be removed.
#endif
                        break;
                }
        }

        ASSERT(t_PieceNum);
}

void TakeBackMove(S_BOARD *pos)
{
        ASSERT(CheckBoard(pos));

        pos->hisPly--;
        pos->ply--;

        ASSERT(CheckBoard(pos));

        int move = pos->history[pos->hisPly].move;
        int from = FromSquare(move);
        int to = ToSquare(move);

        ASSERT(SqOnBoard(from));
        ASSERT(SqOnBoard(to));

        if (pos->enPas != NO_SQ)
                HashEP(pos); ///< Hash out the en pessant square
        HashCA(pos);         ///< Hash out the castling permissions

        pos->castlePerm = pos->history[pos->hisPly].castlePerm;
        pos->fiftyMove = pos->history[pos->hisPly].fiftyMove;
        pos->enPas = pos->history[pos->hisPly].enPas;

        if (pos->enPas != NO_SQ)
                HashEP(pos); ///< Hash in the en pessant square
        HashCA(pos);         ///< Hash in the castling permissions

        pos->side ^= 1;
        HashSide(pos);

        if (move & MFLAGEP)
        {
                if (pos->side == WHITE)
                {
                        AddPiece(to - 10, pos, bP);
                }
                else
                {
                        AddPiece(to + 10, pos, wP);
                }
        }
        else if (move & MFLAGCA)
        {
                switch (to)
                {
                case C1:
                        MovePiece(D1, A1, pos);
                        break;
                case C8:
                        MovePiece(D8, A8, pos);
                        break;
                case G1:
                        MovePiece(F1, H1, pos);
                        break;
                case G8:
                        MovePiece(F8, H8, pos);
                        break;
                default:
                        ASSERT(FALSE);
                        break;
                }
        }

        MovePiece(to, from, pos);

        ///< TODO: This might be redundant. Remove after tests have been setup.
        if (PieceKing[pos->pieces[from]])
        {
                pos->KingSq[pos->side] = from;
        }

        int capturedPiece = Captured(move);
        if (capturedPiece != EMPTY)
        {
                ASSERT(PieceValid(capturedPiece));
                AddPiece(to, pos, capturedPiece);
        }

        int promotedPiece = Promoted(move);
        if (promotedPiece != EMPTY)
        {
                ASSERT(PieceValid(promotedPiece) && !PiecePawn[promotedPiece]);
                ClearPiece(from, pos);
                AddPiece(from, pos, pos->side == BLACK ? wP : bP);
        }

        printf("CheckBoard 2 from TakeBackMove\n");
        ASSERT(CheckBoard(pos));
}

/**
 * This function makes a move on the board.
 * @param[in] pos: the board.
 * @param[in] move: the move to make.
 * @return 0 if the function executed successfully, -1 otherwise.
 */
int MakeMove(S_BOARD *pos, const int move)
{
        printf("CheckBoard 1\n");
        ASSERT(CheckBoard(pos));

        int from = FromSquare(move);
        int to = ToSquare(move);
        int side = pos->side;

        ASSERT(SqOnBoard(from));
        ASSERT(SqOnBoard(to));
        ASSERT(SideValid(side));
        ASSERT(PieceValid(pos->pieces[from]));

        pos->history[pos->hisPly].hashKey = pos->hashKey; ///< Save the hash key to the move history

        ///< Check if this is an en passant move and remove the capturedPiece pawn
        if (move & MFLAGEP)
        {
                if (side == WHITE)
                {
                        ClearPiece(to - 10, pos);
                }
                else
                {
                        ClearPiece(to + 10, pos);
                }
        }
        ///< Check if this is a castling move and move the rook
        else if (move & MFLAGCA)
        {
                switch (to)
                {
                case C1:
                        MovePiece(A1, D1, pos);
                        break;
                case C8:
                        MovePiece(A8, D8, pos);
                        break;
                case G1:
                        MovePiece(H1, F1, pos);
                        break;
                case G8:
                        MovePiece(H8, F8, pos);
                        break;
                default:
                        ASSERT(FALSE);
                        break;
                }
        }

        if (pos->enPas != NO_SQ)
        {
                HashEP(pos); ///< Hash out the en passant square
        }
        HashCA(pos); ///< Hash out the current castle permissions

        pos->history[pos->hisPly].move = move;
        pos->history[pos->hisPly].fiftyMove = pos->fiftyMove;
        pos->history[pos->hisPly].enPas = pos->enPas;
        pos->history[pos->hisPly].castlePerm = pos->castlePerm;

        pos->castlePerm &= CastlePerm[from];
        pos->castlePerm &= CastlePerm[to];
        pos->enPas = NO_SQ;

        HashCA(pos); ///< Hash in the new castle permissions

        int capturedPiece = Captured(move);
        pos->fiftyMove++;

        if (capturedPiece != EMPTY)
        {
                ASSERT(PieceValid(capturedPiece));
                ClearPiece(to, pos);
                pos->fiftyMove = 0;
        }

        pos->hisPly++;
        pos->ply++;

        if (PiecePawn[pos->pieces[from]])
        {
                pos->fiftyMove = 0;
                if (move & MFLAGPS)
                {
                        if (side == WHITE)
                        {
                                pos->enPas = from + 10;
                                ASSERT(RanksBrd[pos->enPas] == RANK_3);
                        }
                        else
                        {
                                pos->enPas = from - 10;
                                ASSERT(RanksBrd[pos->enPas] == RANK_6);
                        }
                        HashEP(pos); ///< Hash in the en passant square
                }
        }

        MovePiece(from, to, pos);

        int promotedPiece = Promoted(move);
        if (promotedPiece != EMPTY)
        {
                ASSERT(PieceValid(promotedPiece) && !PiecePawn[promotedPiece]);
                ClearPiece(to, pos);
                AddPiece(to, pos, promotedPiece);
        }

        ///< TODO: This might be redundant. Remove after tests have been setup.
        if (PieceKing[pos->pieces[to]])
        {
                pos->KingSq[pos->side] = to;
        }

        pos->side ^= 1;
        HashSide(pos); ///< Hash in the new side.

        printf("CheckBoard 2\n");
        ASSERT(CheckBoard(pos))

        if (SqAttacked(pos->KingSq[side], pos->side, pos))
        {
                TakeBackMove(pos);
                return FALSE;
        }

        return TRUE;
}

#pragma endregion FUNCTIONS