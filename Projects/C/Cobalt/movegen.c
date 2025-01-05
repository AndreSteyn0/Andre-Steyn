/**
 * @file movegen.c
 * @brief This file contains the functions that generate moves.
 */

#include "defs.h"

const int LoopSlidePce[2][3] = {
    {wB, wR, wQ},
    {bB, bR, bQ}};

const int LoopNonSlidePce[2][2] = {
    {wN, wK},
    {bN, bK}};

const int PceDir[13][8] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {-8, -19, -21, -12, 8, 19, 21, 12},
    {-9, -11, 11, 9, 0, 0, 0, 0},
    {-1, -10, 1, 10, 0, 0, 0, 0},
    {-1, -10, 1, 10, -9, -11, 11, 9},
    {-1, -10, 1, 10, -9, -11, 11, 9},
    {0, 0, 0, 0, 0, 0, 0},
    {-8, -19, -21, -12, 8, 19, 21, 12},
    {-9, -11, 11, 9, 0, 0, 0, 0},
    {-1, -10, 1, 10, 0, 0, 0, 0},
    {-1, -10, 1, 10, -9, -11, 11, 9},
    {-1, -10, 1, 10, -9, -11, 11, 9}};

#pragma region INLINE FUNCTIONS

/**
 * This function creates an integer that stores the move information.
 * @param[in] from: the from square.
 * @param[in] to: the to square.
 * @param[in] captured: the captured piece.
 * @param[in] promoted: the promoted piece.
 * @param[in] flag: the flag.
 * @return The move.
 */
static inline int
MOVE(int from, int to, int captured, int promoted, int flag)
{
        return (from) | (to << 7) | (captured << 14) | (promoted << 20) | flag;
}

/**
 * This function checks if a square is off the board.
 * @param[in] sq: the square.
 * @return 1 if the square is off the board, 0 otherwise.
 */
static inline int SQOFFBOARD(const int sq)
{
        return FilesBrd[sq] == OFFBOARD ? 1 : 0;
}

#pragma endregion INLINE FUNCTIONS

#pragma region FUNCTIONS

/**
 *
 */
static void AddQuietMove(const S_BOARD *pos, int move, S_MOVELIST *moveList)
{
        moveList->moves[moveList->count].move = move;
        moveList->moves[moveList->count].score = 0;
        moveList->count++;
}

/**
 * This function adds a capture move to the move list.
 * @param[in] pos: the board.
 * @param[in] move: the move.
 * @param[out] moveList: the move list.
 */
static void AddCaptureMove(const S_BOARD *pos, int move, S_MOVELIST *moveList)
{
        moveList->moves[moveList->count].move = move;
        moveList->moves[moveList->count].score = 0;
        moveList->count++;
}

/**
 * This function adds an en passant move to the move list.
 * @param[in] pos: the board.
 * @param[in] move: the move.
 * @param[out] moveList: the move list.
 */
static void AddEnPassantMove(const S_BOARD *pos, int move, S_MOVELIST *moveList)
{
        moveList->moves[moveList->count].move = move;
        moveList->moves[moveList->count].score = 0;
        moveList->count++;
}

/**
 * This function generates the all the possible moves for the pawns.
 * @param[in] pos: the board.
 * @param[in] from: the from square.
 * @param[in] side: the side to move.
 * @param[out] moveList: the move list.
 */
void AddPawnMoves(const S_BOARD *pos, int from, int side, S_MOVELIST *moveList)
{
        int forward = (side == WHITE) ? 10 : -10;
        int startRank = (side == WHITE) ? RANK_2 : RANK_7;
        int promoteRank = (side == WHITE) ? RANK_7 : RANK_2;

        ///< Check for quiet moves
        if (pos->pieces[from + forward] == EMPTY)
        {
                ///< Check for promotions
                if (RanksBrd[from] == promoteRank)
                {
                        AddQuietMove(pos, MOVE(from, from + forward, EMPTY, wQ, 0), moveList);
                        AddQuietMove(pos, MOVE(from, from + forward, EMPTY, wR, 0), moveList);
                        AddQuietMove(pos, MOVE(from, from + forward, EMPTY, wB, 0), moveList);
                        AddQuietMove(pos, MOVE(from, from + forward, EMPTY, wN, 0), moveList);
                }
                else
                {
                        AddQuietMove(pos, MOVE(from, from + forward, EMPTY, EMPTY, 0), moveList);

                        ///< Check for double pawn moves
                        if (RanksBrd[from] == startRank && pos->pieces[from + 2 * forward] == EMPTY)
                        {
                                AddQuietMove(pos, MOVE(from, from + 2 * forward, EMPTY, EMPTY, MFLAGPS), moveList);
                        }
                }
        }

        ///< Check for captures
        int captures[] = {forward - 1, forward + 1};
        for (int i = 0; i < 2; i++)
        {
                int to = from + captures[i];
                ///< Check for off board and if the piece is of the opposite color
                if (!SQOFFBOARD(to) && PieceCol[pos->pieces[to]] == (side ^ 1))
                {
                        ///< Check for promotions
                        if (RanksBrd[from] == promoteRank)
                        {
                                AddCaptureMove(pos, MOVE(from, to, pos->pieces[to], wQ, 0), moveList);
                                AddCaptureMove(pos, MOVE(from, to, pos->pieces[to], wR, 0), moveList);
                                AddCaptureMove(pos, MOVE(from, to, pos->pieces[to], wB, 0), moveList);
                                AddCaptureMove(pos, MOVE(from, to, pos->pieces[to], wN, 0), moveList);
                        }
                        else
                        {
                                AddCaptureMove(pos, MOVE(from, to, pos->pieces[to], EMPTY, 0), moveList);
                        }
                }

                ///< Check for en passant captures
                if (to == pos->enPas)
                {
                        AddEnPassantMove(pos, MOVE(from, to, EMPTY, EMPTY, MFLAGEP), moveList);
                }
        }
}

/**
 * This function generates the all the possible moves for the castling.
 * @param[in] pos: the board.
 * @param[in] side: the side to move.
 * @param[out] moveList: the move list.
 */
void AddCastleMove(const S_BOARD *pos, int side, S_MOVELIST *moveList)
{
        ///< Calculate the castling sides
        int kingSideCastlingSide = side == WHITE ? WKCA : BKCA;
        int queenSideCastlingSide = side == WHITE ? WQCA : BQCA;

        ///< Check if the castling squares are empty
        int kingSideCastlingSquaresEmpty = side == WHITE ? pos->pieces[F1] == EMPTY && pos->pieces[G1] == EMPTY : pos->pieces[F8] == EMPTY && pos->pieces[G8] == EMPTY;
        int queenSideCastlingSquaresEmpty = side == WHITE ? pos->pieces[D1] == EMPTY && pos->pieces[C1] == EMPTY && pos->pieces[B1] == EMPTY : pos->pieces[D8] == EMPTY && pos->pieces[C8] == EMPTY && pos->pieces[B8] == EMPTY;

        ///< Check if the castling squares are attacked
        int kingSideAttacked = side == WHITE ? SqAttacked(E1, side ^ 1, pos) || SqAttacked(F1, side ^ 1, pos) : SqAttacked(E8, side ^ 1, pos) || SqAttacked(F8, side ^ 1, pos);
        int queenSideAttacked = side == WHITE ? SqAttacked(E1, side ^ 1, pos) || SqAttacked(D1, side ^ 1, pos) : SqAttacked(E8, side ^ 1, pos) || SqAttacked(D8, side ^ 1, pos);

        int from, to;

        ///< Check for king side castling moves
        if (pos->castlePerm & (kingSideCastlingSide) && kingSideCastlingSquaresEmpty && !kingSideAttacked)
        {
                from = side == WHITE ? E1 : E8;
                to = side == WHITE ? G1 : G8;
                AddQuietMove(pos, MOVE(from, to, EMPTY, EMPTY, MFLAGCA), moveList);
        }

        ///< Check for queen side castling moves
        if (pos->castlePerm & (queenSideCastlingSide) && queenSideCastlingSquaresEmpty && !queenSideAttacked)
        {
                from = side == WHITE ? E1 : E8;
                to = side == WHITE ? C1 : C8;
                AddQuietMove(pos, MOVE(from, to, EMPTY, EMPTY, MFLAGCA), moveList);
        }
}

/**
 * This function generates all the possible moves for the board.
 * @param[in] pos: the board.
 * @param[in] moveList: the move list.
 */
void GenerateAllMoves(const S_BOARD *pos, S_MOVELIST *moveList)
{
        ASSERT(CheckBoard(pos));

        moveList->count = 0;

        int pce = EMPTY;
        int side = pos->side;
        int sq = 0;
        int t_sq = 0;
        int pceNum = 0;
        int dir = 0;
        int index = 0;
        int pceIndex = 0;

        ///< Loop for pawns
        for (pceNum = 0; pceNum < pos->pieceNum[side == WHITE ? wP : bP]; ++pceNum)
        {
                sq = pos->pieceList[side == WHITE ? wP : bP][pceNum];
                ASSERT(SqOnBoard(sq));
                AddPawnMoves(pos, sq, side, moveList);
        }

        ///< Loop for slide pieces
        for (pceIndex = 0; pceIndex < ARRLEN(LoopSlidePce[side]); ++pceIndex)
        {
                pce = LoopSlidePce[side][pceIndex]; ///< Get the piece
                ASSERT(PieceValid(pce));

                for (pceNum = 0; pceNum < pos->pieceNum[pce]; ++pceNum)
                {
                        sq = pos->pieceList[pce][pceNum]; ///< Get the square of the piece
                        ASSERT(SqOnBoard(sq));

                        for (index = 0; index < ARRLEN(PceDir[pce]); ++index)
                        {
                                dir = PceDir[pce][index]; ///< Get the direction that the piece can move
                                if (dir == 0)
                                {
                                        break;
                                }

                                t_sq = sq + dir; ///< Get the target square

                                while (!SQOFFBOARD(t_sq))
                                {
                                        if (pos->pieces[t_sq] != EMPTY)
                                        {
                                                ///< Check if the piece is of the opposite color
                                                if (PieceCol[pos->pieces[t_sq]] == side ^ 1)
                                                {
                                                        AddCaptureMove(pos, MOVE(sq, t_sq, pos->pieces[t_sq], EMPTY, 0), moveList);
                                                }
                                                break;
                                        }
                                        AddQuietMove(pos, MOVE(sq, t_sq, EMPTY, EMPTY, 0), moveList);
                                        t_sq += dir;
                                }
                        }
                }
        }

        ///< Loop for non slide pieces
        for (pceIndex = 0; pceIndex < ARRLEN(LoopNonSlidePce[side]); ++pceIndex)
        {
                pce = LoopNonSlidePce[side][pceIndex];
                ASSERT(PieceValid(pce));

                for (pceNum = 0; pceNum < pos->pieceNum[pce]; ++pceNum)
                {
                        sq = pos->pieceList[pce][pceNum];
                        ASSERT(SqOnBoard(sq));

                        for (index = 0; index < ARRLEN(PceDir[pce]); ++index)
                        {
                                dir = PceDir[pce][index];
                                if (dir == 0)
                                {
                                        break;
                                }

                                t_sq = sq + dir;
                                if (SQOFFBOARD(t_sq))
                                {
                                        continue;
                                }

                                if (pos->pieces[t_sq] != EMPTY)
                                {
                                        if (PieceCol[pos->pieces[t_sq]] == side ^ 1)
                                        {
                                                AddCaptureMove(pos, MOVE(sq, t_sq, pos->pieces[t_sq], EMPTY, 0), moveList);
                                        }
                                        continue;
                                }
                                AddQuietMove(pos, MOVE(sq, t_sq, EMPTY, EMPTY, 0), moveList);
                        }
                }
        }

        ///< Loop for castle moves
        AddCastleMove(pos, side, moveList);
}
#pragma endregion FUNCTIONS