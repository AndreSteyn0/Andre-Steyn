/**
 * @file perft.c
 */

#include "defs.h"

#define MAX_FEN_STR_LEN 80

long Perft(const int depth, S_BOARD *pos, long *leafNodes)
{
        ASSERT(CheckBoard(pos));

        if (depth == 0)
        {
                leafNodes++;
                return;
        }

        S_MOVELIST moveList[1];
        GenerateAllMoves(pos, moveList);

        int moveNum = 0;
        for (moveNum = 0; moveNum < moveList->count; ++moveNum)
        {
                if (!MakeMove(pos, moveList->moves[moveNum].move))
                {
                        continue;
                }
                Perft(depth - 1, pos, &leafNodes);
                TakeBackMove(pos);
        }

        return leafNodes;
}

void SinglePerftTest(const int depth, S_BOARD *pos, long *leafNodes)
{
        ASSERT(CheckBoard(pos));
        PrintBoard(pos);

        printf("\nStarting Test To Depth:%d\n", depth);

        S_MOVELIST moveList[1];
        GenerateAllMoves(pos, moveList);

        int move = 0;
        int moveNum = 0;
        for (moveNum = 0; moveNum < moveList->count; ++moveNum)
        {
                move = moveList->moves[moveNum].move;
                if (!MakeMove(pos, move))
                {
                        continue;
                }
                long sumNodes = leafNodes;
                Perft(depth - 1, pos, leafNodes);
                TakeBackMove(pos);
                long oldnodes = leafNodes - sumNodes;
                printf("Move %d: %s : %ld\n", moveNum + 1, PrMove(move), oldnodes);
        }

        printf("\nTest Complete : %ld nodes visited\n", leafNodes);

        return;
}

void BulkPerftTest()
{
        AllInit();

        S_BOARD board[1];
        S_MOVELIST list[1];

        char fen[MAX_FEN_STR_LEN];
        int depth = 0;
        long leafNodes = 0;
        int cnt = 0;

        ///< read the perft test file
        FILE *file = fopen("perft.txt", "r");
        if (file == NULL)
        {
                printf("Error opening file\n");
                return;
        }

        char ch;
        while ((ch = fgetc(file)) != EOF)
        {
                if (ch == '\n')
                {
                }
        }
}