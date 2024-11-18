#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>
#include <stdio.h>

typedef unsigned long long U64;

#pragma region CONSTANTS

#define DEBUG // TODO: Remove the DEBUG
#define NAME "Cobalt 1.0"
#define BRD_SQ_NUM 120
#define MAXGAMEMOVES 2048
#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#pragma endregion CONSTANTS

#pragma region ENUMS

<<<<<<< HEAD
enum PIECES
=======
enum
>>>>>>> 0da313e85660c338b912763091b7765692c2a88a
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
}; // Piece values

<<<<<<< HEAD
enum FILES
=======
enum
>>>>>>> 0da313e85660c338b912763091b7765692c2a88a
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
}; // File values

<<<<<<< HEAD
enum RANKS
=======
enum
>>>>>>> 0da313e85660c338b912763091b7765692c2a88a
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
}; // Rank values

<<<<<<< HEAD
enum COLORS
=======
enum
>>>>>>> 0da313e85660c338b912763091b7765692c2a88a
{
        WHITE,
        BLACK,
        BOTH
}; // Side values

<<<<<<< HEAD
enum SQUARES
=======
enum
>>>>>>> 0da313e85660c338b912763091b7765692c2a88a
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
}; // Board square values

<<<<<<< HEAD
enum BOOL
=======
enum
>>>>>>> 0da313e85660c338b912763091b7765692c2a88a
{
        FALSE,
        TRUE
};

<<<<<<< HEAD
enum CASTLE
=======
enum
>>>>>>> 0da313e85660c338b912763091b7765692c2a88a
{
        NONE = 0,
        WKCA = 1,
        WQCA = 2,
        BKCA = 4,
        BQCA = 8
}; // Castling permissions

#pragma endregion ENUMS

#pragma region STRUCTS

<<<<<<< HEAD
/*
        This structure contains the history of the game.
*/
typedef struct S_UNDO
{
        int move;       // move that was played
        int castlePerm; // castle permissions
        int enPas;      // en passant square
        int fiftyMove;  // fifty move rule
        U64 hashKey;
} S_UNDO;

/*
        This structure contains the board state.
*/
typedef struct S_BOARD
{
        int pieces[BRD_SQ_NUM]; // pieces on the board
=======
typedef struct S_UNDO
{
        int move;
        int castlePerm;
        int enPas;
        int fiftyMove;
        U64 hashKey;
} S_UNDO;

typedef struct S_BOARD
{
        int pieces[BRD_SQ_NUM];
>>>>>>> 0da313e85660c338b912763091b7765692c2a88a
        U64 pawns[3];

        int KingSq[2];

<<<<<<< HEAD
        int side;       // side to move
        int enPas;      // En passant square
        int fiftyMove;  // fifty move rule
        int castlePerm; // castle permissions

        int ply; // half moves
=======
        int side;
        int enPas;
        int fiftyMove;
        int castlePerm;

        int ply;
>>>>>>> 0da313e85660c338b912763091b7765692c2a88a
        int hisPly;

        U64 hashKey;

<<<<<<< HEAD
        int pceNum[13];      // number of pieces
        int bigPce[2];       // big pieces (knigts, bishops, rooks, queens, and kings)
        int majPce[2];       // major pieces (rooks, queens, and kings)
        int minPce[2];       // minor pieces (bishops, and knights)
        int material[2];     // material score
        int pceList[13][10]; // piece list

        S_UNDO history[MAXGAMEMOVES]; // history of the game
=======
        int pceNum[13];
        int bigPce[3];
        int majPce[3]; // major pieces (rooks and queens)
        int minPce[3]; // minor pieces (bishops and knights)

        S_UNDO history[MAXGAMEMOVES];

        // piece list
        int pceList[13][10];
>>>>>>> 0da313e85660c338b912763091b7765692c2a88a
} S_BOARD;

#pragma endregion STRUCTS

#pragma region GLOBALS

// init.c
extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];
extern U64 SetMask[64];
extern U64 ClearMask[64];
extern U64 PieceKeys[13][120];
extern U64 SideKey;
extern U64 CastleKeys[16];
<<<<<<< HEAD
extern int FilesBrd[BRD_SQ_NUM];
extern int RanksBrd[BRD_SQ_NUM];
=======
>>>>>>> 0da313e85660c338b912763091b7765692c2a88a

// data.c
extern char PceChar[];
extern char SideChar[];
extern char RankChar[];
extern char FileChar[];
<<<<<<< HEAD
extern int PceBig[13];
extern int PceMaj[13];
extern int PceMin[13];
extern int PceVal[13];
extern int PceCol[13];
=======
>>>>>>> 0da313e85660c338b912763091b7765692c2a88a

#pragma endregion GLOBALS

#pragma region FUNCTIONS DECLARATIONS

// init.c
extern void AllInit();

// bitboards.c
extern void PrintBitBoard(U64 bb);
extern int PopBit(U64 *bb);
extern int CountBits(U64 b);

// hashkeys.c
extern U64 GeneratePosKey(const S_BOARD *pos);

// board.c
extern void ResetBoard(S_BOARD *pos);
extern int ParseFen(char *fen, S_BOARD *pos);
extern void PrintBoard(const S_BOARD *pos);
<<<<<<< HEAD
extern int CheckBoard(const S_BOARD *pos);
=======
>>>>>>> 0da313e85660c338b912763091b7765692c2a88a

#pragma endregion FUNCTIONS DECLARATIONS

#pragma region MACROS

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

/*
  This function converts a file and rank to a 120 based square.
*/
static inline int FR2SQ(int f, int r)
{
        return ((21 + (f)) + ((r) * 10));
}

/*
  This function converts a 120 based square to a 64 based square.
*/
static inline int SQ64(int sq120)
{
        return Sq120ToSq64[(sq120)];
}

/*
  This function converts a 64 based square to a 120 based square.
*/
static inline int SQ120(int sq64)
{
        return Sq64ToSq120[(sq64)];
}

/*
  This function pops the least significant bit set in the bitboard.
*/
static inline int POP(U64 *b)
{
        return (PopBit(b));
}

/*
  This function returns the number of bits set in the bitboard.
*/
static inline int CNT(U64 b)
{
        return (CountBits(b));
}

/*
  This function clears the bit at the square in the bitboard.
*/
static inline void CLRBIT(U64 *bb, int sq)
{
        *bb &= ClearMask[sq];
}

/*
  This function sets the bit at the square in the bitboard.
*/
static inline void SETBIT(U64 *bb, int sq)
{
        *bb |= SetMask[sq];
}

static inline U64 RAND_64()
{
        return (U64)rand() | ((U64)rand() << 15) | ((U64)rand() << 30) | ((U64)rand() << 45) | (((U64)rand() & 0xf) << 60);
}

#pragma endregion INLINE FUNCTIONS

#endif