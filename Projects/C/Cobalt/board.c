///< board.c

#include "defs.h"

/**
 * This function checks the board for any errors.
 * @param[in] pos: the board.
 * @return 0 if the function executed successfully, -1 otherwise.
 */
int CheckBoard(const S_BOARD *pos)
{
        ///< Temporary variables
        int t_pieceNum[NUMBER_OF_PIECES] = {0};
        int t_bigPiece[2] = {0};
        int t_majPiece[2] = {0};
        int t_minPiece[2] = {0};
        int t_material[2] = {0};

        U64 t_pawns[3] = {0ULL};
        t_pawns[WHITE] = pos->pawns[WHITE];
        t_pawns[BLACK] = pos->pawns[BLACK];
        t_pawns[BOTH] = pos->pawns[BOTH];

        int sq64, t_piece, t_pieceNum2, sq120, color, pcount;

        ///< Check piece lists
        for (t_piece = wP; t_piece <= bK; ++t_piece)
        {
                for (t_pieceNum2 = 0; t_pieceNum2 < pos->pieceNum[t_piece]; ++t_pieceNum2)
                {
                        sq120 = pos->pieceList[t_piece][t_pieceNum2];
                        ASSERT(pos->pieces[sq120] == t_piece);
                }
        }

        ///< Check piece count and other counters
        for (sq64 = 0; sq64 < 64; ++sq64)
        {
                sq120 = SQ120(sq64);
                t_piece = pos->pieces[sq120];
                t_pieceNum[t_piece]++;
                color = PieceCol[t_piece];
                t_material[color] += PieceVal[t_piece];

                if (PieceMin[t_piece] == TRUE)
                {
                        t_minPiece[color]++;
                        t_bigPiece[color]++;
                        continue;
                }

                if (PieceMaj[t_piece] == TRUE)
                {
                        t_majPiece[color]++;
                        t_bigPiece[color]++;
                        continue;
                }
        }

        ///< Check piece numbers
        for (t_piece = wP; t_piece <= bK; ++t_piece)
        {
                ASSERT(t_pieceNum[t_piece] == pos->pieceNum[t_piece]);
        }

        ///< Check bitboards count
        pcount = CNT(t_pawns[WHITE]);
        ASSERT(pcount == pos->pieceNum[wP]);
        pcount = CNT(t_pawns[BLACK]);
        ASSERT(pcount == pos->pieceNum[bP]);
        pcount = CNT(t_pawns[BOTH]);
        ASSERT(pcount == (pos->pieceNum[bP] + pos->pieceNum[wP]));

        ///< Check bitboards squares
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

        ///< Check the material
        ASSERT(t_material[WHITE] == pos->material[WHITE] && t_material[BLACK] == pos->material[BLACK]);
        ASSERT(t_minPiece[WHITE] == pos->minPiece[WHITE] && t_minPiece[BLACK] == pos->minPiece[BLACK]);
        ASSERT(t_majPiece[WHITE] == pos->majPiece[WHITE] && t_majPiece[BLACK] == pos->majPiece[BLACK]);
        ASSERT(t_bigPiece[WHITE] == pos->bigPiece[WHITE] && t_bigPiece[BLACK] == pos->bigPiece[BLACK]);

        ASSERT(pos->side == WHITE || pos->side == BLACK); ///< Check the side to move
        ASSERT(GeneratePosKey(pos) == pos->hashKey);      ///< Check the hash key

        ///< Check the en passant square
        ASSERT(pos->enPas == NO_SQ || (RanksBrd[pos->enPas] == RANK_6 && pos->side == WHITE) || (RanksBrd[pos->enPas] == RANK_3 && pos->side == BLACK));

        ///< Check that the kings are on the correct squares
        ASSERT(pos->pieces[pos->KingSq[WHITE]] == wK);
        ASSERT(pos->pieces[pos->KingSq[BLACK]] == bK);
}

/**
 * This function updates the lists of pieces and material for the board.
 * @param[in] pos: the board.
 */
void UpdateListsMaterial(S_BOARD *pos)
{
        int piece, sq, index, color;
        for (index = 0; index < BRD_SQ_NUM; ++index)
        {
                sq = index;
                piece = pos->pieces[index]; ///< Get the piece on the square

                if (piece == OFFBOARD || piece == EMPTY)
                {
                        continue;
                }

                color = PieceCol[piece]; ///< Get the color of the piece

                ASSERT(color != BOTH);

                pos->material[color] += PieceVal[piece];

                pos->pieceList[piece][pos->pieceNum[piece]] = sq;
                pos->pieceNum[piece]++;

                if (PieceBig[piece] == FALSE)
                {

                        SETBIT(&pos->pawns[color], SQ64(sq));
                        SETBIT(&pos->pawns[BOTH], SQ64(sq));
                        continue;
                }

                ASSERT(PieceBig[piece] == TRUE);

                pos->bigPiece[color]++;
                if (piece == wK || piece == bK)
                {
                        pos->KingSq[color] = sq;
                        pos->majPiece[color]++;
                        continue;
                }

                if (PieceMin[piece] == TRUE)
                {
                        pos->minPiece[color]++;
                        continue;
                }

                if (PieceMaj[piece] == TRUE)
                {
                        pos->majPiece[color]++;
                        continue;
                }
        }
}

/**
 * This function parses the FEN string and sets the board to the position described in the FEN string.
 * @param[in] fen: the FEN string.
 * @param[in] pos: the board.
 * @return 0 if the function executed successfully, -1 otherwise.
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

        ///< Parse the pieces on the board
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
                        count = *fen - '0'; ///< Convert the character to an integer
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

                ///< Set the pieces on the board
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

        ///< Parse the side to move
        pos->side = (*fen == 'w') ? WHITE : BLACK;
        fen += 2;

        ///< Parse the castling permissions
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

        ///< Parse the en passant square
        if (*fen != '-')
        {
                file = fen[0] - 'a';
                rank = fen[1] - '1';

                ASSERT(file >= FILE_A && file <= FILE_H);
                ASSERT(rank >= RANK_1 && rank <= RANK_8);

                pos->enPas = FR2SQ(file, rank);
        }

        pos->hashKey = GeneratePosKey(pos);

        UpdateListsMaterial(pos);

        return 0;
}

/**
 * This function resets the board to the starting position.
 * @param[in] pos: the board.
 */
void ResetBoard(S_BOARD *pos)
{
        int index = 0;

        ///< Set all pieces to OFFBOARD
        for (index = 0; index < BRD_SQ_NUM; ++index)
        {
                pos->pieces[index] = OFFBOARD;
        }

        ///< Set all pieces to EMPTY
        for (index = 0; index < 64; ++index)
        {
                pos->pieces[SQ120(index)] = EMPTY;
        }

        ///< Set all pawns to 0ULL
        for (index = 0; index < ARRLEN(pos->pawns); ++index)
        {
                pos->pawns[index] = 0ULL;
        }

        ///< Set all the piece lists to 0
        for (index = 0; index < ARRLEN(pos->bigPiece); ++index)
        {
                pos->bigPiece[index] = 0;
                pos->majPiece[index] = 0;
                pos->minPiece[index] = 0;
        }

        ///< Set all the piece numbers to 0
        for (index = 0; index < NUMBER_OF_PIECES; ++index)
        {
                pos->pieceNum[index] = 0;
        }

        ///< Set all the king squares to NO_SQ
        pos->KingSq[WHITE] = pos->KingSq[BLACK] = NO_SQ;

        ///< Reset the rest of the board state
        pos->side = BOTH;
        pos->enPas = NO_SQ;
        pos->fiftyMove = 0;
        pos->ply = 0;
        pos->hisPly = 0;
        pos->castlePerm = NONE;
        pos->hashKey = 0ULL;
}

/**
 * This function prints the board.
 * @param[in] pos: the board.
 */
void PrintBoard(const S_BOARD *pos)
{
        int sq, file, rank, piece;

        ///< Print the Game Board
        printf("\nGame Board:\n\n");
        for (rank = RANK_8; rank >= RANK_1; rank--)
        {
                printf("%d  ", rank + 1);
                for (file = FILE_A; file <= FILE_H; file++)
                {
                        sq = FR2SQ(file, rank);
                        piece = pos->pieces[sq];
                        printf("%3c", PieceChar[piece]);
                }
                printf("\n");
        }

        printf("\n   ");

        ///< Print the files
        for (file = FILE_A; file <= FILE_H; file++)
        {
                printf("%3c", FileChar[file]);
        }
        printf("\n");

        ///< Print some additional state information
        printf("side:%c\n", SideChar[pos->side]);
        printf("enPas:%d\n", pos->enPas);
        printf("castle:%c%c%c%c\n",
               pos->castlePerm & WKCA ? 'K' : '-',
               pos->castlePerm & WQCA ? 'Q' : '-',
               pos->castlePerm & BKCA ? 'k' : '-',
               pos->castlePerm & BQCA ? 'q' : '-');
        printf("PosKey:%llX\n", pos->hashKey);
}