#include "stdio.h"
#include "stdlib.h"
#include "defs.h"

#define FEN1 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPPP1PP/RNBQKBNR w KQkq e3 0 1"
#define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/2P5/PP1P1PPP/RNBQKBNR b KQkq - 0 2"
#define FEN4 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define PAWNMOVESWHITE "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"
#define PAWNMOVESBLACK "rnbqkbnr/p1p1p3/3p3p/1p1p4/2P1Pp2/8/PP1P1PpP/RNBQKB1R b KQkq e3 0 1"
#define KNIGHTSKINGSBLACK "5k2/1n6/4n3/6N1/8/3N4/8/5K2 b - - 0 1"
#define KNIGHTSKINGSWHITE "5k2/1n6/4n3/6N1/8/3N4/8/5K2 w - - 0 1"
#define ROOKS "6k1/8/5r2/8/1nR5/5N2/8/6K1 b - - 0 1"
#define QUEENS "6k1/8/4nq2/8/1nQ5/5N2/1N6/6K1 w - - 0 1"
#define BISHOPS "6k1/1b6/4n3/8/1n4B1/1B3N2/1N6/2b3K1 b - - 0 1"
#define CASTLE1 "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"
#define CASTLE2 "3rk2r/8/8/8/8/8/6p1/R3K2R b KQk - 0 1"

/**
 * This is the main function.
 */
int main()
{
        AllInit();

        S_BOARD board[1];
        S_MOVELIST list[1];

        // ParseFen(PAWNMOVESWHITE, board);
        // ParseFen(PAWNMOVESBLACK, board);
        // ParseFen(KNIGHTSKINGSBLACK, board);
        // ParseFen(KNIGHTSKINGSWHITE, board);
        // ParseFen(ROOKS, board);
        // ParseFen(QUEENS, board);
        // ParseFen(BISHOPS, board);
        // ParseFen(CASTLE1, board);
        // ParseFen(CASTLE2, board);
        // ParseFen(FEN4, board);
        ParseFen(START_FEN, board);
        GenerateAllMoves(board, list);

        int MoveNum = 0;
        int move = 0;
        PrintBoard(board);
        getchar();
        printf("MoveList:\n");
        for (MoveNum = 0; MoveNum < list->count; ++MoveNum)
        {
                move = list->moves[MoveNum].move;
                if (!MakeMove(board, move))
                {
                        continue;
                }
                printf("Move:%d > %s\n", MoveNum + 1, PrMove(move));

                PrintBoard(board);

                TakeBackMove(board);
                printf("\nMove Taken Back:%d > %s\n", MoveNum + 1, PrMove(move));

                PrintBoard(board);
                getchar();
        }

        return 0;
}