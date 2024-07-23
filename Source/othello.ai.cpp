#include <DxLib.h>
#include "variables.h"
#include "macros.h"
#include "funcs.h"

int Othello::AI::Chose::Strong(int board[], char color, int* count, int total)
{
	if (Othello::Basic::PutAbleAll(board, -1) == 0)
	{
		return -1;
	}

	if (total <= 45)
	{
		deepest = 5;
	}
	if ((total <= 48) && (45 < total))
	{
		deepest = 2;
	}
	if (total > 48)
	{
		deepest = 12;
	}

	int depth = deepest - *count;

	int boardex[64][64];
	int i = Othello::AI::ExpandNode(-1, board, boardex);

	int val[64];

	if (total > 48)
	{
		for (int j = 0; j < i; j++)
		{
			ProcessMessage();
			val[j] = Othello::AI::AlphaBetaMost(boardex[j], 1, depth, -10000, 10000);
		}
	}
	if (total <= 48)
	{
		for (int j = 0; j < i; j++)
		{
			ProcessMessage();
			val[j] = Othello::AI::AlphaBetaConer(boardex[j], 1, depth, -10000, 10000);
		}
	}

	lowest = Utility::Arr::Max(val, i);

	int f = Utility::Arr::MaxIndexRand(val, i);

	// àÍéûìIÇ»ÉeÉXÉgóp
	// ----------------------------------------------------------------------

	// for (int j = 0; j < i; j++)
	// {
	//     printf("%d\n", val[j]);
	// }

	// printf("\nf %d\n", f);

	// return Othello::AI::Chose::Rand(board, BLACK);

	// ----------------------------------------------------------------------

	// ç≈Ç‡ï]âøílÇÃçÇÇ¢éüÇÃî’ñ Ç∆åªç›ÇÃî’ñ Çî‰ärÇµÅAÇ«Ç±Ç…íuÇ©ÇÍÇΩÇÃÇ©Çí≤Ç◊ÇÈèàóù
	for (int k = 0; k < 64; k++)
	{
		if ((boardex[f][k] != 0) && (board[k] == 0))
		{
			return k;
		}
	}

	return -1;
}

int Othello::AI::Chose::Weak(int board[], char color)
{
	int p;
	int rs;
	for (int y = 0; y < 64; y++)
	{
		p = Othello::Basic::PutAble(board, color, y);
		if (p == 1)
		{
			rs = y;
			break;
		}
		if (y == 63)
		{
			return -1;
		}
	}
	return rs;
}

int Othello::AI::Chose::Rand(int board[], int color)
{
	int rs;
	int h[64];
	int i = 0;
	int p;

	for (int y = 0; y < 64; y++)
	{
		p = Othello::Basic::PutAble(board, color, y);
		if (p == 1)
		{
			h[i] = y;
			i++;
		}
		if ((y == 63) && (i == 0))
		{
			return -1;
		}
	}
	int rd = Utility::RandBetween(0, i - 1);
	rs = h[rd];

	return rs;
}

int Othello::AI::Chose::Most(int board[], int color)
{
	int a1[64];
	int rs;
	int h[64];
	int i = 0;
	int p;

	for (int y = 0; y < 64; y++)
	{
		p = Othello::Basic::PutAble(board, color, y);
		if (p == 1)
		{
			h[i] = y;
			// ÂêàÊ≥ïÊâã„ÅÆ‰ΩçÁΩÆÊÉ?Â†±„ÇíÊ?ºÁ¥ç„Ä?

			i++;
		}
		if ((y == 63) && (i == 0))
		{
			return -1;
		}
	}

	int j[64];

	for (int k = 0; k < i; k++)
	{
		for (int k = 0; k < 64; k++)
		{
			a1[k] = board[k];
		}
		if (color == -1)
		{
			a1[h[k]] = -1;
		}
		if (color == 1)
		{
			a1[h[k]] = 1;
		}
		Othello::Basic::ChangeBoard(a1, color, h[k]);
		j[k] = Othello::Basic::CountColor(a1, color);
	}

	int mxn = Utility::Arr::MaxIndex(j, i);
	// printf ("mxn %d\n",mxn);

	rs = h[mxn];

	if ((h[mxn] == 1) || (h[mxn] == 9) || (h[mxn] == 8) ||
		(h[mxn] == 6) || (h[mxn] == 14) || (h[mxn] == 15) ||
		(h[mxn] == 48) || (h[mxn] == 49) || (h[mxn] == 57) ||
		(h[mxn] == 55) || (h[mxn] == 54) || (h[mxn] == 62))
	{
		int tasi = 0;
		int* h2;
		h2 = new int[i];
		int mmm = 0;
		for (int kj = 0; kj < i; kj++)
		{
			if ((h[kj] != 1) && (h[kj] != 9) && (h[kj] != 8) &&
				(h[kj] != 6) && (h[kj] != 14) && (h[kj] != 15) &&
				(h[kj] != 48) && (h[kj] != 49) && (h[kj] != 57) &&
				(h[kj] != 55) && (h[kj] != 54) && (h[kj] != 62))
			{
				tasi++;
				h2[mmm] = h[kj];
				// rs = h[kj];
				mmm++;
				// break;
			}
		}
		for (int k = 0; k < mmm; k++)
		{
			for (int k = 0; k < 64; k++)
			{
				a1[k] = board[k];
			}
			if (color == -1)
			{
				a1[h2[k]] = -1;
			}
			Othello::Basic::ChangeBoard(a1, color, h2[k]);
			j[k] = Othello::Basic::CountColor(a1, color);
		}

		mxn = Utility::Arr::MaxIndex(j, mmm);

		if (tasi != 0)
		{
			rs = h2[mxn];
		}
	}
	for (int ku = 0; ku < i; ku++)
	{
		if (h[ku] == 0)
		{
			rs = h[ku];
			break;
		}
		if (h[ku] == 7)
		{
			rs = h[ku];
			break;
		}
		if (h[ku] == 56)
		{
			rs = h[ku];
			break;
		}
		if (h[ku] == 63)
		{
			rs = h[ku];
			break;
		}
	}
	return rs;
}

// ok
int Othello::AI::ExpandNode(int turn, int board[], int boardex[][64])
{
	// ñﬂÇËílÇÕägí£Ç∑ÇÈÇ±Ç∆Ç™Ç≈Ç´ÇΩÉpÉ^Å[ÉìÇÃêî
	// about turn, 1 mens white, -1 means black.
	int boardbu[64]; // this arry is back up for board arry.
	Othello::Basic::BoardCpy(boardbu, board);
	int count = 0;

	if (turn == 1)
	{
		for (int i = 0; i < 64; i++)
		{
			if (Othello::Basic::PutAble(board, 1, i) == 1)
			{
				Othello::Basic::ChangeBoard(board, 1, i);
				Othello::Basic::BoardCpy(boardex[count], board);
				Othello::Basic::BoardCpy(board, boardbu);
				count++;
			}
		}
	}
	if (turn == -1)
	{
		for (int i = 0; i < 64; i++)
		{
			if (Othello::Basic::PutAble(board, -1, i) == 1)
			{
				Othello::Basic::ChangeBoard(board, -1, i);
				Othello::Basic::BoardCpy(boardex[count], board);
				Othello::Basic::BoardCpy(board, boardbu);
				count++;
			}
		}
	}
	return count;
}

int Othello::AI::MinMaxConer(int board[], int turn, int depth)
{
	// Ç∆ÇËÇ†Ç¶Ç∏ÅAturn Ç™Å@-1Å@ÇÃÇ‚Ç¬ÇæÇØçÏÇÈÅB

	if ((depth == 0) || (Othello::Basic::IsEnd(board) == 1))
	{
		countpattern++;
		return Othello::AI::EvalueCalcConer(board);
	}

	int boardex[64][64];

	int best;

	int ct = Othello::AI::ExpandNode(turn, board, boardex);

	if (ct == 0)
	{
		turn *= -1;
		ct = Othello::AI::ExpandNode(turn, board, boardex);
	}

	int val[64];

	for (int i = 0; i < ct; i++)
	{
		val[i] = Othello::AI::MinMaxConer(boardex[i], -turn, depth - 1);
	}

	if (turn == 1)
	{
		best = Utility::Arr::Min(val, ct);
	}
	if (turn == -1)
	{
		best = Utility::Arr::Max(val, ct);
	}

	return best;
}

int Othello::AI::MinMaxMost(int board[], int turn, int depth)
{
	// Ç∆ÇËÇ†Ç¶Ç∏ÅAturn Ç™Å@-1Å@ÇÃÇ‚Ç¬ÇæÇØçÏÇÈÅB

	if ((depth == 0) || (Othello::Basic::IsEnd(board) == 1))
	{
		countpattern++;
		return Othello::AI::EvalueCalcMost(board);
	}

	int boardex[64][64];

	int best;

	int ct = Othello::AI::ExpandNode(turn, board, boardex);

	if (ct == 0)
	{
		turn *= -1;
		ct = Othello::AI::ExpandNode(turn, board, boardex);
	}

	int val[64];

	for (int i = 0; i < ct; i++)
	{
		val[i] = Othello::AI::MinMaxMost(boardex[i], -turn, depth - 1);
	}

	if (turn == 1)
	{
		best = Utility::Arr::Min(val, ct);
	}
	if (turn == -1)
	{
		// my turn
		best = Utility::Arr::Max(val, ct);
	}

	return best;
}

// ok
int Othello::AI::AlphaBetaMost(int board[], int turn, int depth, int alpha, int beta)
{
	// Ç∆ÇËÇ†Ç¶Ç∏ÅAturn Ç™Å@-1Å@ÇÃÇ‚Ç¬ÇæÇØçÏÇÈÅB
	// alpha = -infinity, beta = inifinity

	if ((depth == 0) || (Othello::Basic::IsEnd(board) == 1))
	{
		// countpattern++;
		return Othello::AI::EvalueCalcMost(board);
	}

	int boardex[64][64];

	int best;

	int ct = Othello::AI::ExpandNode(turn, board, boardex);

	if (ct == 0)
	{
		turn *= -1;
		ct = Othello::AI::ExpandNode(turn, board, boardex);
	}

	int count = 0;

	int val[64];

	if (turn == -1)
	{
		// my turn
		for (int i = 0; i < ct; i++)
		{
			val[i] = Othello::AI::AlphaBetaMost(boardex[i], -turn, depth - 1, alpha, beta);
			count++;

			alpha = Utility::Arr::Max(val, count);
			if (alpha >= beta)
			{
				break;
			}
		}
		return alpha;
	}
	if (turn == 1)
	{
		for (int i = 0; i < ct; i++)
		{
			val[i] = Othello::AI::AlphaBetaMost(boardex[i], -turn, depth - 1, alpha, beta);
			count++;

			beta = Utility::Arr::Min(val, count);
			if (alpha >= beta)
			{
				break;
			}
		}
		return beta;
	}
	return beta;
}

// ok
int Othello::AI::AlphaBetaConer(int board[], int turn, int depth, int alpha, int beta)
{
	// Ç∆ÇËÇ†Ç¶Ç∏ÅAturn Ç™Å@-1Å@ÇÃÇ‚Ç¬ÇæÇØçÏÇÈÅB
	// alpha = -infinity, beta = inifinity
	// ÇøÇ»Ç›Ç…turnÇÕçïîíÇ«ÇøÇÁÇÃÉ^Å[ÉìÇ©Ç∆Ç¢Ç§Ç±Ç∆Ç≈Ç†ÇÈÅB
	// åàÇµÇƒâΩï˚Ç™ëIëÇµÇΩíºå„Ç©Ç∆Ç¢Ç§à”ñ°Ç≈ÇÕÇ»Ç¢ÅB

	if ((depth == 0) || (Othello::Basic::IsEnd(board) == 1))
	{
		// countpattern++;
		if (Othello::Basic::CountColor(board, -1) == 0)
		{
			return -10000;
		}
		if (turn == WHITE)
		{
			// íTçıÇ≈Ç´ÇÈç≈ê[ÇÃóÃàÊÇ…ÇƒÅAéüÇÃÉ^Å[ÉìÇ≈ëSñ≈Ç∑ÇÈÉäÉXÉNÇ
			// âÒîÇ∑ÇÈÇΩÇﬂÇÃèàóùÅB
			int boardex[64][64];
			int pt = Othello::AI::ExpandNode(turn, board, boardex);
			for (int i = 0; i < pt; i++)
			{
				if (Othello::Basic::CountColor(boardex[i], BLACK) == 0)
				{
					return -10000;
				}
			}
		}
		return Othello::AI::EvalueCalcConer(board);
	}

	int boardex[64][64];

	int best;

	int ct = Othello::AI::ExpandNode(turn, board, boardex);

	if (ct == 0)
	{
		turn *= -1;
		ct = Othello::AI::ExpandNode(turn, board, boardex);
	}

	int count = 0;

	int val[64];

	if (turn == -1)
	{
		// my turn
		for (int i = 0; i < ct; i++)
		{
			val[i] = Othello::AI::AlphaBetaConer(boardex[i], -turn, depth - 1, alpha, beta);
			count++;

			alpha = Utility::Arr::Max(val, count);
			if (alpha >= beta)
			{
				break;
			}
		}
		return alpha;
	}
	if (turn == 1)
	{
		for (int i = 0; i < ct; i++)
		{
			val[i] = Othello::AI::AlphaBetaConer(boardex[i], -turn, depth - 1, alpha, beta);
			count++;

			beta = Utility::Arr::Min(val, count);
			if (alpha >= beta)
			{
				break;
			}
		}
		return beta;
	}
	return beta;
}

// Evalueån

// ok
void Othello::AI::EvalueCpy(int board[])
{
	board[0] = 30;
	board[7] = 30;
	board[56] = 30;
	board[63] = 30; // 4

	board[Othello::Basic::ExchangeXY(4, 8)] = -1;
	board[Othello::Basic::ExchangeXY(5, 8)] = -1;
	board[Othello::Basic::ExchangeXY(4, 6)] = -1;
	board[Othello::Basic::ExchangeXY(5, 6)] = -1;
	board[Othello::Basic::ExchangeXY(1, 5)] = -1;
	board[Othello::Basic::ExchangeXY(3, 5)] = -1;
	board[Othello::Basic::ExchangeXY(4, 5)] = -1;
	board[Othello::Basic::ExchangeXY(5, 5)] = -1;
	board[Othello::Basic::ExchangeXY(6, 5)] = -1;
	board[Othello::Basic::ExchangeXY(8, 5)] = -1;
	board[Othello::Basic::ExchangeXY(1, 4)] = -1;
	board[Othello::Basic::ExchangeXY(3, 4)] = -1;
	board[Othello::Basic::ExchangeXY(4, 4)] = -1;
	board[Othello::Basic::ExchangeXY(5, 4)] = -1;
	board[Othello::Basic::ExchangeXY(6, 4)] = -1;
	board[Othello::Basic::ExchangeXY(8, 4)] = -1;
	board[Othello::Basic::ExchangeXY(4, 3)] = -1;
	board[Othello::Basic::ExchangeXY(5, 3)] = -1;
	board[Othello::Basic::ExchangeXY(4, 1)] = -1;
	board[Othello::Basic::ExchangeXY(5, 1)] = -1; // 2_exchange
	board[Othello::Basic::ExchangeXY(3, 8)] = 0;
	board[Othello::Basic::ExchangeXY(6, 8)] = 0;
	board[Othello::Basic::ExchangeXY(1, 6)] = 0;
	board[Othello::Basic::ExchangeXY(3, 6)] = 0;
	board[Othello::Basic::ExchangeXY(6, 6)] = 0;
	board[Othello::Basic::ExchangeXY(8, 6)] = 0;
	board[Othello::Basic::ExchangeXY(1, 3)] = 0;
	board[Othello::Basic::ExchangeXY(3, 3)] = 0;
	board[Othello::Basic::ExchangeXY(6, 3)] = 0;
	board[Othello::Basic::ExchangeXY(8, 3)] = 0;
	board[Othello::Basic::ExchangeXY(3, 1)] = 0;
	board[Othello::Basic::ExchangeXY(6, 1)] = 0; // 1_exchange
	board[Othello::Basic::ExchangeXY(3, 7)] = -3;
	board[Othello::Basic::ExchangeXY(4, 7)] = -3;
	board[Othello::Basic::ExchangeXY(5, 7)] = -3;
	board[Othello::Basic::ExchangeXY(6, 7)] = -3;
	board[Othello::Basic::ExchangeXY(2, 6)] = -3;
	board[Othello::Basic::ExchangeXY(2, 5)] = -3;
	board[Othello::Basic::ExchangeXY(2, 4)] = -3;
	board[Othello::Basic::ExchangeXY(2, 3)] = -3;
	board[Othello::Basic::ExchangeXY(7, 6)] = -3;
	board[Othello::Basic::ExchangeXY(7, 5)] = -3;
	board[Othello::Basic::ExchangeXY(7, 4)] = -3;
	board[Othello::Basic::ExchangeXY(7, 3)] = -3;
	board[Othello::Basic::ExchangeXY(3, 2)] = -3;
	board[Othello::Basic::ExchangeXY(4, 2)] = -3;
	board[Othello::Basic::ExchangeXY(5, 2)] = -3;
	board[Othello::Basic::ExchangeXY(6, 2)] = -3; // 1_exchange
	board[Othello::Basic::ExchangeXY(2, 7)] = -15;
	board[Othello::Basic::ExchangeXY(7, 7)] = -15;
	board[Othello::Basic::ExchangeXY(2, 2)] = -15;
	board[Othello::Basic::ExchangeXY(7, 2)] = -15; // _exchange
	board[Othello::Basic::ExchangeXY(2, 8)] = -12;
	board[Othello::Basic::ExchangeXY(7, 8)] = -12;
	board[Othello::Basic::ExchangeXY(1, 7)] = -12;
	board[Othello::Basic::ExchangeXY(8, 7)] = -12;
	board[Othello::Basic::ExchangeXY(1, 2)] = -12;
	board[Othello::Basic::ExchangeXY(8, 2)] = -12;
	board[Othello::Basic::ExchangeXY(2, 1)] = -12;
	board[Othello::Basic::ExchangeXY(7, 1)] = -12; // 8
}

// ok
int Othello::AI::EvalueCalcMost(int board[])
{
	int val = 0;
	for (int oi = 0; oi < 64; oi++)
	{
		if (board[oi] == -1)
		{
			val += 1;
		}
		if (board[oi] == 1)
		{
			val += -1;
		}
	}
	return val;
}

// ok
int Othello::AI::EvalueCalcConer(int board[])
{
	int value[64];
	Othello::AI::EvalueCpy(value);

	int val = 0;
	for (int oi = 0; oi < 64; oi++)
	{
		if (board[oi] == -1)
		{
			val += value[oi];
		}
		if (board[oi] == 1)
		{
			val += -value[oi];
		}
	}
	return val;
}
