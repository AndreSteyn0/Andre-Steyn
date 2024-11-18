// board.c

#include "defs.h"

<<<<<<< HEAD
int CheckBoard(const S_BOARD *pos)
{
        int t_pceNum[13] = {0};
        int t_bigPce[2] = {0};
        int t_majPce[2] = {0};
        int t_minPce[2] = {0};
        int t_material[2] = {0};

        int sq64, t_piece, t_pceNum2, sq120, color, pcount;

        U64 t_pawns[3] = {0ULL};

        t_pawns[WHITE] = pos->pawns[WHITE];
        t_pawns[BLACK] = pos->pawns[BLACK];
        t_pawns[BOTH] = pos->pawns[BOTH];

        // check piece lists
        for (t_piece = wP; t_piece <= bK; ++t_piece)
        {
                for (t_pceNum2 = 0; t_pceNum2 < pos->pceNum[t_piece]; ++t_pceNum2)
                {
                        sq120 = pos->pceList[t_piece][t_pceNum2];
                        ASSERT(pos->pieces[sq120] == t_piece);
                }
        }

        // check piece count and other counters
        for (sq64 = 0; sq64 < 64; ++sq64)
        {
                sq120 = SQ120(sq64);
                t_piece = pos->pieces[sq120];
                t_pceNum[t_piece]++;
                color = PceCol[t_piece];
                if (PceBig[t_piece] == TRUE)
                {
                        t_bigPce[color]++;
                }
                if (PceMin[t_piece] == TRUE)
                {
                        t_minPce[color]++;
                }
                if (PceMaj[t_piece] == TRUE)
                {
                        t_majPce[color]++;
                }

                t_material[color] += PceVal[t_piece];
        }

        for (t_piece = wP; t_piece <= bK; ++t_piece)
        {
                ASSERT(t_pceNum[t_piece] == pos->pceNum[t_piece]);
        }

        // check bitboards count
        pcount = CNT(t_pawns[WHITE]);
        ASSERT(pcount == pos->pceNum[wP]);
        pcount = CNT(t_pawns[BLACK]);
        ASSERT(pcount == pos->pceNum[bP]);
        pcount = CNT(t_pawns[BOTH]);
        ASSERT(pcount == (pos->pceNum[bP] + pos->pceNum[wP]));

        // check bitboards squares
        while (t_pawns[WHITE])
        {
                sq64 = POP(&t_pawns[WHITE]);
                ASSERT(pos->pieces[SQ120(sq64)] == wP);
        }

        while (t_pawns[BLACK])
        {
                sq64 = POP(&t_pawns[BLACK]);
                ASSERT(pos->pieces[SQ120(sq64)] == bP);
        }

        while (t_pawns[BOTH])
        {
                sq64 = POP(&t_pawns[BOTH]);
                ASSERT((pos->pieces[SQ120(sq64)] == bP) || (pos->pieces[SQ120(sq64)] == wP));
        }

        ASSERT(t_material[WHITE] == pos->material[WHITE] && t_material[BLACK] == pos->material[BLACK]);
        ASSERT(t_minPce[WHITE] == pos->minPce[WHITE] && t_minPce[BLACK] == pos->minPce[BLACK]);
        ASSERT(t_majPce[WHITE] == pos->majPce[WHITE] && t_majPce[BLACK] == pos->majPce[BLACK]);
        ASSERT(t_bigPce[WHITE] == pos->bigPce[WHITE] && t_bigPce[BLACK] == pos->bigPce[BLACK]);

        ASSERT(pos->side == WHITE || pos->side == BLACK);
        ASSERT(GeneratePosKey(pos) == pos->hashKey);

        ASSERT(pos->enPas == NO_SQ || (RanksBrd[pos->enPas] == RANK_6 && pos->side == WHITE) || (RanksBrd[pos->enPas] == RANK_3 && pos->side == BLACK));

        ASSERT(pos->pieces[pos->KingSq[WHITE]] == wK);
        ASSERT(pos->pieces[pos->KingSq[BLACK]] == bK);
}

/*
        This function updates the lists of pieces and material for the board.
*/
void UpdateListsMaterial(S_BOARD *pos)
{
        int piece, sq, index, color;
        for (index = 0; index < BRD_SQ_NUM; ++index)
        {
                sq = index;
                piece = pos->pieces[index];
                if (piece != OFFBOARD && piece != EMPTY && piece != NO_SQ)
                {
                        color = PceCol[piece];

                        ASSERT(color != BOTH);

                        if (PceBig[piece] == TRUE)
                        {
                                pos->bigPce[color]++;
                                if (PceMin[piece] == TRUE)
                                {
                                        pos->minPce[color]++;
                                }
                                else if (PceMaj[piece] == TRUE)
                                {
                                        pos->majPce[color]++;
                                }

                                switch (piece)
                                {
                                case wK:
                                        pos->KingSq[WHITE] = sq;
                                        break;
                                case bK:
                                        pos->KingSq[BLACK] = sq;
                                        break;
                                default:
                                        break;
                                }
                        }
                        else
                        {
                                switch (piece)
                                {
                                case wP:
                                        SETBIT(&pos->pawns[WHITE], SQ64(sq));
                                        SETBIT(&pos->pawns[BOTH], SQ64(sq));
                                        break;
                                case bP:
                                        SETBIT(&pos->pawns[BLACK], SQ64(sq));
                                        SETBIT(&pos->pawns[BOTH], SQ64(sq));
                                        break;

                                default:
                                        break;
                                }
                        }

                        pos->material[color] += PceVal[piece];

                        pos->pceList[piece][pos->pceNum[piece]] = sq;
                        pos->pceNum[piece]++;
                }
        }
}

=======
>>>>>>> 0da313e85660c338b912763091b7765692c2a88a
/*
        This function parses the FEN string and sets the board to the position described in the FEN string.
*/
int ParseFen(char *fen, S_BOARD *pos)
{
        ASSERT(fen != NULL);
        ASSERT(pos != NULL);

        int rank = RANK_8;
        int file = FILE_A;
        int piece = 0;
        int count = 0;
        int i = 0;
        int sq64 = 0;
        int sq120 = 0;

        ResetBoard(pos);

        // parse the pieces on the board
        while ((rank >= RANK_1) && *fen)
        {
                count = 1;
                switch (*fen)
                {
                case 'p':
                        piece = bP;
                        break;
                case 'r':
                        piece = bR;
                        break;
                case 'n':
                        piece = bN;
                        break;
                case 'b':
                        piece = bB;
                        break;
                case 'k':
                        piece = bK;
                        break;
                case 'q':
                        piece = bQ;
                        break;
                case 'P':
                        piece = wP;
                        break;
                case 'R':
                        piece = wR;
                        break;
                case 'N':
                        piece = wN;
                        break;
                case 'B':
                        piece = wB;
                        break;
                case 'K':
                        piece = wK;
                        break;
                case 'Q':
                        piece = wQ;
                        break;

                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                        piece = EMPTY;
                        count = *fen - '0';
                        break;

                case '/':
                case ' ':
                        rank--;
                        file = FILE_A;
                        fen++;
                        continue;

                default:
                        printf("FEN error \n");
                        return -1;
                }

                for (i = 0; i < count; i++)
                {
                        sq64 = rank * 8 + file;
                        sq120 = SQ120(sq64);
                        if (piece != EMPTY)
                        {
                                pos->pieces[sq120] = piece;
                        }
                        file++;
                }
                fen++;
        }

        ASSERT(*fen == 'w' || *fen == 'b');

        // parse the side to move
        pos->side = (*fen == 'w') ? WHITE : BLACK;
        fen += 2;

        // parse the castling permissions
        for (i = 0; i < 4; i++)
        {
                if (*fen == ' ')
                {
                        break;
                }
                switch (*fen)
                {
                case 'K':
                        pos->castlePerm |= WKCA;
                        break;
                case 'Q':
                        pos->castlePerm |= WQCA;
                        break;
                case 'k':
                        pos->castlePerm |= BKCA;
                        break;
                case 'q':
                        pos->castlePerm |= BQCA;
                        break;
                case '-':
                        pos->castlePerm = NONE;
                        break;
                default:
                        printf("FEN error \n");
                        return -1;
                }
                *fen++;
        }
        fen++;

        ASSERT(pos->castlePerm >= 0 && pos->castlePerm <= 15);

        // parse the en passant square
        if (*fen != '-')
        {
                file = fen[0] - 'a';
                rank = fen[1] - '1';

                ASSERT(file >= FILE_A && file <= FILE_H);
                ASSERT(rank >= RANK_1 && rank <= RANK_8);

                pos->enPas = FR2SQ(file, rank);
        }

        // set the hash key
        pos->hashKey = GeneratePosKey(pos);
<<<<<<< HEAD

        UpdateListsMaterial(pos);

=======
>>>>>>> 0da313e85660c338b912763091b7765692c2a88a
        return 0;
}

/*
        This function resets the board to the starting position.
*/
void ResetBoard(S_BOARD *pos)
{
        int index = 0;

        // set all pieces to OFFBOARD
        for (index = 0; index < BRD_SQ_NUM; ++index)
        {
                pos->pieces[index] = OFFBOARD;
        }

        // set all pieces to EMPTY
        for (index = 0; index < 64; ++index)
        {
                pos->pieces[SQ120(index)] = EMPTY;
        }

        // set all pawns to 0ULL and all big, major, and minor pieces to 0
        for (index = 0; index < 3; ++index)
        {
                pos->pawns[index] = 0ULL;
                pos->bigPce[index] = 0;
                pos->majPce[index] = 0;
                pos->minPce[index] = 0;
        }

        // set all the piece numbers to 0
        for (index = 0; index < 13; ++index)
        {
                pos->pceNum[index] = 0;
        }

        // set all the king squares to NO_SQ
        pos->KingSq[WHITE] = pos->KingSq[BLACK] = NO_SQ;

        // Reset side, enPas, fiftyMove, ply, hisPly, castlePerm, and hashKey
        pos->side = BOTH;
        pos->enPas = NO_SQ;
        pos->fiftyMove = 0;
        pos->ply = 0;
        pos->hisPly = 0;
        pos->castlePerm = NONE;
        pos->hashKey = 0ULL;
}

void PrintBoard(const S_BOARD *pos)
{
        int sq, file, rank, piece;

        printf("\nGame Board:\n\n");

        for (rank = RANK_8; rank >= RANK_1; rank--)
        {
                printf("%d  ", rank + 1);
                for (file = FILE_A; file <= FILE_H; file++)
                {
                        sq = FR2SQ(file, rank);
                        piece = pos->pieces[sq];
                        printf("%3c", PceChar[piece]);
                }
                printf("\n");
        }

        printf("\n   ");

        for (file = FILE_A; file <= FILE_H; file++)
        {
                printf("%3c", FileChar[file]);
        }
        printf("\n");
        printf("side:%c\n", SideChar[pos->side]);
        printf("enPas:%d\n", pos->enPas);
        printf("castle:%c%c%c%c\n",
               pos->castlePerm & WKCA ? 'K' : '-',
               pos->castlePerm & WQCA ? 'Q' : '-',
               pos->castlePerm & BKCA ? 'k' : '-',
               pos->castlePerm & BQCA ? 'q' : '-');
        printf("PosKey:%llX\n", pos->hashKey);
}