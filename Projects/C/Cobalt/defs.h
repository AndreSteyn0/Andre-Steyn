#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>
#include <stdio.h>

#pragma region TYPE DEFINITIONS

typedef unsigned long long U64;

#pragma endregion TYPE DEFINITIONS

#pragma region CONSTANTS

#define DEBUG ///< TODO: Comment out the DEBUG
#define NAME "Cobalt 1.0"
#define BRD_SQ_NUM 120
#define MAXGAMEMOVES 2048
#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define NUMBER_OF_PIECES 13

#pragma endregion CONSTANTS

#pragma region ENUMS

/**
 * This enum represents the pieces in the game.
 */
enum PieceS
{
        EMPTY,
        wP,
        wN,
        wB,
        wR,
        wQ,
        wK,
        bP,
        bN,
        bB,
        bR,
        bQ,
        bK
};

/**
 * This enum represents the files on the board.
 */
enum FILES
{
        FILE_A,
        FILE_B,
        FILE_C,
        FILE_D,
        FILE_E,
        FILE_F,
        FILE_G,
        FILE_H,
        FILE_NONE
};

/**
 * This enum represents the ranks on the board.
 */
enum RANKS
{
        RANK_1,
        RANK_2,
        RANK_3,
        RANK_4,
        RANK_5,
        RANK_6,
        RANK_7,
        RANK_8,
        RANK_NONE
};

/**
 * This enum represents the sides in the game.
 */
enum COLORS
{
        WHITE,
        BLACK,
        BOTH
};

/**
 * This enum represents the squares on the board.
 */
enum SQUARES
{
        A1 = 21,
        B1,
        C1,
        D1,
        E1,
        F1,
        G1,
        H1,
        A2 = 31,
        B2,
        C2,
        D2,
        E2,
        F2,
        G2,
        H2,
        A3 = 41,
        B3,
        C3,
        D3,
        E3,
        F3,
        G3,
        H3,
        A4 = 51,
        B4,
        C4,
        D4,
        E4,
        F4,
        G4,
        H4,
        A5 = 61,
        B5,
        C5,
        D5,
        E5,
        F5,
        G5,
        H5,
        A6 = 71,
        B6,
        C6,
        D6,
        E6,
        F6,
        G6,
        H6,
        A7 = 81,
        B7,
        C7,
        D7,
        E7,
        F7,
        G7,
        H7,
        A8 = 91,
        B8,
        C8,
        D8,
        E8,
        F8,
        G8,
        H8,
        NO_SQ,
        OFFBOARD
};

/**
 * This enum represents the boolean values.
 */
enum BOOL
{
        FALSE,
        TRUE
};

/**
 * This enum represents the castling permissions for white and black.
 */
enum CASTLE
{
        NONE = 0,
        WKCA = 1,
        WQCA = 2,
        BKCA = 4,
        BQCA = 8
};

#pragma endregion ENUMS

#pragma region STRUCTS

/**
 * This structure contains the history of the game.
 */
typedef struct S_UNDO
{
        int move;       ///< move that was played
        int castlePerm; ///< castle permissions
        int enPas;      ///< en passant square
        int fiftyMove;  ///< fifty move rule
        U64 hashKey;    ///< hash key
} S_UNDO;

/**
 * This structure contains the board state.
 */
typedef struct S_BOARD
{
        ///< General game state
        int side;       ///< Side to move (WHITE or BLACK).
        int enPas;      ///< En passant square, or -1 if not applicable.
        int fiftyMove;  ///< Counter for the fifty-move rule.
        int castlePerm; ///< Bitfield representing castling permissions.
        int ply;        ///< Half-move count for the current search.
        int hisPly;     ///< Full move count in the game history.

        ///< Board representation
        int KingSq[2];          ///< Squares of the kings [WHITE, BLACK].
        int pieces[BRD_SQ_NUM]; ///< Array of pieces on the board, indexed by square (120-based).

        ///< Piece counts
        int pieceNum[NUMBER_OF_PIECES]; ///< Number of each type of piece on the board.
        int bigPiece[2];                ///< Number of "big pieces" (Knights, Bishops, Rooks, Queens, Kings) for each side.
        int majPiece[2];                ///< Number of "major pieces" (Rooks, Queens, Kings) for each side.
        int minPiece[2];                ///< Number of "minor pieces" (Knights, Bishops) for each side.
        int material[2];                ///< Total material score for each side.

        ///< Piece position lists
        int pieceList[NUMBER_OF_PIECES][10]; ///< List of piece positions for each piece type.

        ///< Bitboards
        U64 pawns[3]; ///< Bitboards for pawns: [WHITE, BLACK, ALL].

        ///< Unique identifiers
        U64 hashKey;            ///< Unique Zobrist hash key for the current position.
        U64 PieceKeys[13][120]; ///< Zobrist keys for pieces on each square.
        U64 SideKey;            ///< Zobrist key for the side to move.
        U64 CastleKeys[16];     ///< Zobrist keys for castling permissions.

        ///< History
        S_UNDO history[MAXGAMEMOVES]; ///< Game history for undoing moves.
} S_BOARD;

#pragma endregion STRUCTS

#pragma region GLOBALS

///< init.c
extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];
extern U64 SetMask[64];
extern U64 ClearMask[64];
extern U64 PieceKeys[NUMBER_OF_PIECES][BRD_SQ_NUM];
extern U64 SideKey;
extern U64 CastleKeys[16];
extern int FilesBrd[BRD_SQ_NUM];
extern int RanksBrd[BRD_SQ_NUM];

///< data.c
extern char PieceChar[];
extern char SideChar[];
extern char RankChar[];
extern char FileChar[];
extern int PieceBig[NUMBER_OF_PIECES];
extern int PieceMaj[NUMBER_OF_PIECES];
extern int PieceMin[NUMBER_OF_PIECES];
extern int PieceVal[NUMBER_OF_PIECES];
extern int PieceCol[NUMBER_OF_PIECES];
extern int PiecePawn[NUMBER_OF_PIECES];
extern int PieceKnight[NUMBER_OF_PIECES];
extern int PieceKing[NUMBER_OF_PIECES];
extern int PieceRookQueen[NUMBER_OF_PIECES];
extern int PieceBishopQueen[NUMBER_OF_PIECES];
extern int PieceSlides[NUMBER_OF_PIECES];

#pragma endregion GLOBALS

#pragma region FUNCTIONS DECLARATIONS

///< init.c
extern void AllInit();

///< bitboards.c
extern void PrintBitBoard(U64 bb);
extern int PopBit(U64 *bb);
extern int CountBits(U64 b);

///< hashkeys.c
extern U64 GeneratePosKey(const S_BOARD *pos);

///< board.c
extern void ResetBoard(S_BOARD *pos);
extern int ParseFen(char *fen, S_BOARD *pos);
extern void PrintBoard(const S_BOARD *pos);
extern int CheckBoard(const S_BOARD *pos);

///< attack.c
extern int SqAttacked(const int sq, const int attackingSide, const S_BOARD *pos);

#pragma endregion FUNCTIONS DECLARATIONS

#pragma region MACROS

/**
 * This Macro calculates the length of an array.
 * @param[in] arr: the array.
 * @return The length of the array.
 */
#define ARRLEN(arr) (sizeof(arr) / sizeof((arr)[0]))

/**
 * This Macro does some assertions. This should only be used in debug mode.
 * @param[in] n: the condition to check.
 */
#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n)                                 \
        if (!(n))                                 \
        {                                         \
                printf("%s - Failed", #n);        \
                printf("On %s ", __DATE__);       \
                printf("At %s ", __TIME__);       \
                printf("In File %s ", __FILE__);  \
                printf("At Line %d\n", __LINE__); \
                exit(1);                          \
        }
#endif

#pragma endregion MACROS

#pragma region INLINE FUNCTIONS

/**
 * This function converts a file and rank to a 120 based square.
 * @param[in] f: the file.
 * @param[in] r: the rank.
 * @return The 120 based square.
 */
static inline int FR2SQ(int f, int r)
{
        return ((21 + (f)) + ((r) * 10));
}

/**
 * This function converts a 120 based square to a 64 based square.
 * @param[in] sq120: the 120 based square.
 * @return The 64 based square.
 */
static inline int SQ64(int sq120)
{
        return Sq120ToSq64[(sq120)];
}

/**
 * This function converts a 64 based square to a 120 based square.
 * @param[in] sq64: the 64 based square.
 * @return The 120 based square.
 */
static inline int SQ120(int sq64)
{
        return Sq64ToSq120[(sq64)];
}

/**
 * This function pops the least significant bit set in the bitboard.
 * @param[in] b: the bitboard.
 * @return The index of the least significant bit set in the bitboard.
 */
static inline int POP(U64 *b)
{
        return (PopBit(b));
}

/**
 * This function returns the number of bits set in the bitboard.
 * @param[in] b: the bitboard.
 * @return The number of bits set in the bitboard.
 */
static inline int CNT(U64 b)
{
        return (CountBits(b));
}

/**
 * This function clears the bit at the square in the bitboard.
 * @param[in] bb: the bitboard.
 * @param[in] sq: the square.
 */
static inline void CLRBIT(U64 *bb, int sq)
{
        *bb &= ClearMask[sq];
}

/**
 * This function sets the bit at the square in the bitboard.
 * @param[in] bb: the bitboard.
 * @param[in] sq: the square.
 */
static inline void SETBIT(U64 *bb, int sq)
{
        *bb |= SetMask[sq];
}

#pragma endregion INLINE FUNCTIONS

#endif