///< io.c

#include "defs.h"

/**
 * This function prints the square in algebraic notation.
 * @param[in] sq: the square.
 * @param[out] sqStr: the square in algebraic notation.
 */
char *PrSq(const int sq)
{
        static char sqStr[3];
        int file = FilesBrd[sq];
        int rank = RanksBrd[sq];
        sprintf(sqStr, "%c%c", ('a' + file), ('1' + rank));
        return sqStr;
}

/**
 * This function prints the move in algebraic notation.
 * @param[in] move: the move.
 * @param[out] moveStr: the move in algebraic notation.
 */
char *PrMove(const int move)
{
        static char MvStr[6];

        int ff = FilesBrd[FromSquare(move)];
        int rf = RanksBrd[FromSquare(move)];
        int ft = FilesBrd[ToSquare(move)];
        int rt = RanksBrd[ToSquare(move)];

        int promoted = Promoted(move);

        if (promoted)
        {
                char pchar = 'q';
                if (IsKn(promoted))
                {
                        pchar = 'n';
                }
                else if (IsRQ(promoted) && !IsBQ(promoted))
                {
                        pchar = 'r';
                }
                else if (!IsRQ(promoted) && IsBQ(promoted))
                {
                        pchar = 'b';
                }
                sprintf(MvStr, "%c%c%c%c%c", ('a' + ff), ('1' + rf), ('a' + ft), ('1' + rt), pchar);
        }
        else
        {
                sprintf(MvStr, "%c%c%c%c", ('a' + ff), ('1' + rf), ('a' + ft), ('1' + rt));
        }

        return MvStr;
}

/**
 * This function prints the move list.
 * @param[in] list: the move list.
 */
void PrintMoveList(const S_MOVELIST *list)
{
        int index = 0;
        int score = 0;
        int move = 0;
        printf("MoveList:\n");

        for (index = 0; index < list->count; ++index)
        {
                move = list->moves[index].move;
                score = list->moves[index].score;
                printf("Move:%d > %s (score:%d)\n", index + 1, PrMove(move), score);
        }
        printf("MoveList Total %d Moves:\n\n", list->count);
}
