#include <list>
#include <DxLib.h>
#include "variables.h"
#include "macros.h"
#include "funcs.h"

// RateDpで使われる関数で、仮想画面上にでっかい数字を表示するためのもの。
std::list<int> DispV::DispNum(int num, char color, int locate)
{
	int Num[2];
	float Rate = 1.325;
	int GHandle[2];

	std::list<int> handles;

	if (!(num >= 0 && num <= 64))
	{
		return handles;
	}

	char string[4];

	if (num > 9)
	{
		sprintf_s(string, "%d", num);
		Num[0] = (int)(string[0] - '0');
		Num[1] = (int)(string[1] - '0');
	}
	else
	{
		sprintf_s(string, "%d", num);
		Num[0] = 0;
		Num[1] = (int)(string[0] - '0');
	}

	char FileName[2][50];

	if (locate == 0)
	{
		sprintf_s(FileName[0], "./AppData/Images/g%d.png", Num[0]);

		sprintf_s(FileName[1], "./AppData/Images/g%d.png", Num[1]);
	}
	else
	{
		sprintf_s(FileName[0], "./AppData/Images/%c%d.png", color, Num[0]);

		sprintf_s(FileName[1], "./AppData/Images/%c%d.png", color, Num[1]);
	}

	ProcessMessage();

	if (color == 'w')
	{
		int StdLocateX[4], StdLocateY[4];
		StdLocateX[0] = 1052, StdLocateY[0] = 520;
		StdLocateX[1] = 1064, StdLocateY[1] = 419;
		StdLocateX[2] = 1072, StdLocateY[2] = 328;
		StdLocateX[3] = 1076, StdLocateY[3] = 240;

		int width = 96 * pow(0.9, locate);
		int interval = 64 * pow(0.9, locate);

		handles.emplace_front(
			screen.Add(FileName[0], StdLocateX[locate], StdLocateY[locate],
				StdLocateX[locate] + width, StdLocateY[locate] + width * Rate));

		handles.emplace_front(
			screen.Add(FileName[1], StdLocateX[locate] + interval, StdLocateY[locate],
				StdLocateX[locate] + interval + width, StdLocateY[locate] + width * Rate));
	}
	if (color == 'b')
	{
		int StdLocateX[4], StdLocateY[4];
		StdLocateX[0] = 1052 - 985, StdLocateY[0] = 520;
		StdLocateX[1] = 1064 - 985, StdLocateY[1] = 419;
		StdLocateX[2] = 1072 - 985, StdLocateY[2] = 328;
		StdLocateX[3] = 1076 - 985, StdLocateY[3] = 240;

		int width = 96 * pow(0.9, locate);
		int interval = 64 * pow(0.9, locate);

		handles.emplace_front(
			screen.Add(FileName[0], StdLocateX[locate], StdLocateY[locate],
				StdLocateX[locate] + width, StdLocateY[locate] + width * Rate));

		handles.emplace_front(
			screen.Add(FileName[1], StdLocateX[locate] + interval, StdLocateY[locate],
				StdLocateX[locate] + interval + width, StdLocateY[locate] + width * Rate));
	}
	ProcessMessage();
	return handles;
}

// 何対何かというのを仮想画面に表示する。
std::list<int> DispV::DispRate(int board[], int reset)
{
	const int NOTHING = 100;
	int Rate[2];
	static int init = 1;

	Rate[0] = Othello::Basic::CountColor(board, -1);
	Rate[1] = Othello::Basic::CountColor(board, 1);

	ProcessMessage();

	if (reset)
	{
		init = 1;
	}

	if (init)
	{
		for (int i = 0; i < 4; i++)
		{
			ScreenState.RateNum[0][i] = NOTHING;
			ScreenState.RateNum[1][i] = NOTHING;
		}
	}

	{
		for (int i = 3; i > 0; i--)
		{
			ProcessMessage();
			ScreenState.RateNum[0][i] = ScreenState.RateNum[0][i - 1];
			ScreenState.RateNum[1][i] = ScreenState.RateNum[1][i - 1];
		}

		ScreenState.RateNum[0][0] = Rate[0];
		ScreenState.RateNum[1][0] = Rate[1];
	}

	std::list<int> handles;

	for (int i = 0; i < 4; i++)
	{
		ProcessMessage();
		std::list<int> handles1, handles2;
		handles1 = DispV::DispNum(ScreenState.RateNum[0][i], 'b', i);
		handles2 = DispV::DispNum(ScreenState.RateNum[1][i], 'w', i);

		handles.splice(handles.begin(), handles1);
		handles.splice(handles.begin(), handles2);
	}

	init = 0;
	return handles;
}

// 仮想画面上に石を置く。戻り値は石の仮想画面上でのハンドル。
int DispV::PutStone(int x, int y, char color)
{
	int GHandle;

	int x_edge = 271, y_edge = -10;

	int length = 145;

	int interval = 85;

	if (!(x <= 7 && x >= 0 && y <= 7 && y >= 0))
	{
		return -1;
	}

	int handle;

	if (color == 'w')
	{
		handle = screen.Add("./AppData/Images/white.png", x_edge + interval * x, y_edge + interval * y,
			x_edge + interval * x + length, y_edge + interval * y + length);
	}
	else
	{
		if (color == 'b')
		{
			handle = screen.Add("./AppData/Images/black.png", x_edge + interval * x, y_edge + interval * y,
				x_edge + interval * x + length, y_edge + interval * y + length);
		}
		else
		{
			return -1;
		}
	}

	return handle;
}

int DispV::PutPoint(int x, int y, int color)
{
	if (!(x <= 7 && x >= 0 && y <= 7 && y >= 0))
	{
		return -1;
	}

	int handle;

	int x_coner = 343, y_coner = 63;

	int interval = 85;

	handle = screen.AddCircle(5, x_coner + x * interval, y_coner + y * interval, color);

	return handle;
}

int DispV::PrintBoard1(int board[], int reset, int turn_before)
{
	// turn_bは何のターン（色）が選択した直後かということ
	// turn_bに0が引き渡された場合特に特別な処理はせずにデフォルトの画像を表示する。

	static std::list<int> old_handles;
	static int init = 1;

	if (init)
	{
		screen.Reset();
	}

	if (init == 0)
	{
		for (int i : old_handles)
		{
			screen.Remove(i);
		}
		old_handles.clear();
	}

	if (Othello::Basic::IsEnd(board))
	{
		old_handles.emplace_front(
			screen.Add("./AppData/Images/ai_vs_player_basic.jpg", 0, 0, 1280, 720));
	}
	else
	{
		if (turn_before == BLACK)
		{
			if (!Othello::Basic::PutAbleAll(board, -turn_before))
			{
				old_handles.emplace_front(
					screen.Add("./AppData/Images/ai_vs_player_zun.jpg", 0, 0, 1280, 720));
			}
			else
			{
				old_handles.emplace_front(
					screen.Add("./AppData/Images/ai_vs_player_you.jpg", 0, 0, 1280, 720));
			}
		}
		if (turn_before == WHITE)
		{
			if (!Othello::Basic::PutAbleAll(board, -turn_before))
			{
				old_handles.emplace_front(
					screen.Add("./AppData/Images/ai_vs_player_you.jpg", 0, 0, 1280, 720));
			}
			else
			{
				old_handles.emplace_front(
					screen.Add("./AppData/Images/ai_vs_player_zun.jpg", 0, 0, 1280, 720));
			}
		}
		if (!turn_before)
		{
			old_handles.emplace_front(
				screen.Add("./AppData/Images/ai_vs_player_basic.jpg", 0, 0, 1280, 720));
		}
	}

	for (int i = 0; i < 64; i++)
	{
		ProcessMessage();
		int x = i % 8, y = i / 8;
		if (board[i] == 1)
		{
			old_handles.emplace_front(
				DispV::PutStone(x, y, 'w'));
		}
		if (board[i] == -1)
		{
			old_handles.emplace_front(
				DispV::PutStone(x, y, 'b'));
		}
	}
	if (reset)
	{
		old_handles.splice(old_handles.begin(),
			DispV::DispRate(board, TRUE));
	}
	else
	{
		old_handles.splice(old_handles.begin(),
			DispV::DispRate(board, FALSE));
	}

	// 石を置ける箇所を表示する関数
	int put_able_all = Othello::Basic::PutAbleAll(board, -turn_before);
	for (int i = 0; i < 64; i++)
	{
		if (board[i] == 0)
		{
			if (put_able_all == 1)
			{
				if (Othello::Basic::PutAble(board, -turn_before, i) == 1)
				{
					if (-turn_before == WHITE)
					{
						old_handles.emplace_front(DispV::PutPoint(i % 8, i / 8, GetColor(120, 220, 120)));
					}
					if (-turn_before == BLACK)
					{
						old_handles.emplace_front(DispV::PutPoint(i % 8, i / 8, GetColor(10, 60, 10)));
					}
				}
			}
			else
			{
				if (Othello::Basic::PutAble(board, turn_before, i) == 1)
				{
					if (turn_before == WHITE)
					{
						old_handles.emplace_front(DispV::PutPoint(i % 8, i / 8, GetColor(120, 220, 120)));
					}
					if (turn_before == BLACK)
					{
						old_handles.emplace_front(DispV::PutPoint(i % 8, i / 8, GetColor(10, 60, 10)));
					}
				}
			}
		}
	}

	init = 0;
	return 0;
}

void DispV::PrintBoard2(int board[], int reset, int turn_before)
{
	// turn_bは何のターン（色）が選択した直後かということ
	// turn_bに0が引き渡された場合特に特別な処理はせずにデフォルトの画像を表示する。

	static std::list<int> old_handles;
	static int init = 1;

	if (init)
	{
		screen.Reset();
	}

	if (init == 0)
	{
		for (int i : old_handles)
		{
			screen.Remove(i);
		}
		old_handles.clear();
	}

	if (Othello::Basic::IsEnd(board))
	{
		old_handles.emplace_front(
			screen.Add("./AppData/Images/player_vs_player_basic.jpg", 0, 0, 1280, 720));
	}
	else
	{
		if (turn_before == BLACK)
		{
			if (!Othello::Basic::PutAbleAll(board, -turn_before))
			{
				old_handles.emplace_front(
					screen.Add("./AppData/Images/player_vs_player_black.jpg", 0, 0, 1280, 720));
			}
			else
			{
				old_handles.emplace_front(
					screen.Add("./AppData/Images/player_vs_player_white.jpg", 0, 0, 1280, 720));
			}
		}
		if (turn_before == WHITE)
		{
			if (!Othello::Basic::PutAbleAll(board, -turn_before))
			{
				old_handles.emplace_front(
					screen.Add("./AppData/Images/player_vs_player_white.jpg", 0, 0, 1280, 720));
			}
			else
			{
				old_handles.emplace_front(
					screen.Add("./AppData/Images/player_vs_player_black.jpg", 0, 0, 1280, 720));
			}
		}
		if (!turn_before)
		{
			old_handles.emplace_front(
				screen.Add("./AppData/Images/player_vs_player_basic.jpg", 0, 0, 1280, 720));
		}
	}

	for (int i = 0; i < 64; i++)
	{
		ProcessMessage();
		int x = i % 8, y = i / 8;
		if (board[i] == 1)
		{
			old_handles.emplace_front(
				DispV::PutStone(x, y, 'w'));
		}
		if (board[i] == -1)
		{
			old_handles.emplace_front(
				DispV::PutStone(x, y, 'b'));
		}
	}
	if (reset)
	{
		old_handles.splice(old_handles.begin(),
			DispV::DispRate(board, TRUE));
	}
	else
	{
		old_handles.splice(old_handles.begin(),
			DispV::DispRate(board, FALSE));
	}

	// 石を置ける箇所を表示する関数
	int put_able_all = Othello::Basic::PutAbleAll(board, -turn_before);
	for (int i = 0; i < 64; i++)
	{
		if (board[i] == 0)
		{
			if (put_able_all == 1)
			{
				if (Othello::Basic::PutAble(board, -turn_before, i) == 1)
				{
					if (-turn_before == WHITE)
					{
						old_handles.emplace_front(DispV::PutPoint(i % 8, i / 8, GetColor(120, 220, 120)));
					}
					if (-turn_before == BLACK)
					{
						old_handles.emplace_front(DispV::PutPoint(i % 8, i / 8, GetColor(10, 60, 10)));
					}
				}
			}
			else
			{
				if (Othello::Basic::PutAble(board, turn_before, i) == 1)
				{
					if (turn_before == WHITE)
					{
						old_handles.emplace_front(DispV::PutPoint(i % 8, i / 8, GetColor(120, 220, 120)));
					}
					if (turn_before == BLACK)
					{
						old_handles.emplace_front(DispV::PutPoint(i % 8, i / 8, GetColor(10, 60, 10)));
					}
				}
			}
		}
	}

	init = 0;
}

void DispV::PrintBoard3(int board[], int reset, int turn_before)
{
	// turn_bは何のターン（色）が選択した直後かということ
	// turn_bに0が引き渡された場合特に特別な処理はせずにデフォルトの画像を表示する。

	static std::list<int> old_handles;
	static int init = 1;

	if (init)
	{
		screen.Reset();
	}

	if (init == 0)
	{
		for (int i : old_handles)
		{
			screen.Remove(i);
		}
		old_handles.clear();
	}

	if (Othello::Basic::IsEnd(board))
	{
		old_handles.emplace_front(
			screen.Add("./AppData/Images/ai_vs_ai_basic.jpg", 0, 0, 1280, 720));
	}
	else
	{
		if (turn_before == BLACK)
		{
			if (!Othello::Basic::PutAbleAll(board, -turn_before))
			{
				old_handles.emplace_front(
					screen.Add("./AppData/Images/ai_vs_ai_zun.jpg", 0, 0, 1280, 720));
			}
			else
			{
				old_handles.emplace_front(
					screen.Add("./AppData/Images/ai_vs_ai_chu.jpg", 0, 0, 1280, 720));
			}
		}
		if (turn_before == WHITE)
		{
			if (!Othello::Basic::PutAbleAll(board, -turn_before))
			{
				old_handles.emplace_front(
					screen.Add("./AppData/Images/ai_vs_ai_chu.jpg", 0, 0, 1280, 720));
			}
			else
			{
				old_handles.emplace_front(
					screen.Add("./AppData/Images/ai_vs_ai_zun.jpg", 0, 0, 1280, 720));
			}
		}
		if (!turn_before)
		{
			old_handles.emplace_front(
				screen.Add("./AppData/Images/ai_vs_ai_basic.jpg", 0, 0, 1280, 720));
		}
	}

	for (int i = 0; i < 64; i++)
	{
		ProcessMessage();
		int x = i % 8, y = i / 8;
		if (board[i] == 1)
		{
			old_handles.emplace_front(
				DispV::PutStone(x, y, 'w'));
		}
		if (board[i] == -1)
		{
			old_handles.emplace_front(
				DispV::PutStone(x, y, 'b'));
		}
	}
	if (reset)
	{
		old_handles.splice(old_handles.begin(),
			DispV::DispRate(board, TRUE));
	}
	else
	{
		old_handles.splice(old_handles.begin(),
			DispV::DispRate(board, FALSE));
	}

	// 石を置ける箇所を表示する関数
	int put_able_all = Othello::Basic::PutAbleAll(board, -turn_before);
	for (int i = 0; i < 64; i++)
	{
		if (board[i] == 0)
		{
			if (put_able_all == 1)
			{
				if (Othello::Basic::PutAble(board, -turn_before, i) == 1)
				{
					if (-turn_before == WHITE)
					{
						old_handles.emplace_front(DispV::PutPoint(i % 8, i / 8, GetColor(120, 220, 120)));
					}
					if (-turn_before == BLACK)
					{
						old_handles.emplace_front(DispV::PutPoint(i % 8, i / 8, GetColor(10, 60, 10)));
					}
				}
			}
			else
			{
				if (Othello::Basic::PutAble(board, turn_before, i) == 1)
				{
					if (turn_before == WHITE)
					{
						old_handles.emplace_front(DispV::PutPoint(i % 8, i / 8, GetColor(120, 220, 120)));
					}
					if (turn_before == BLACK)
					{
						old_handles.emplace_front(DispV::PutPoint(i % 8, i / 8, GetColor(10, 60, 10)));
					}
				}
			}
		}
	}

	init = 0;
}
