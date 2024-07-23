#include <DxLib.h>
#include <time.h>
#include "variables.h"
#include "funcs.h"

// プレイヤーがクリックしたマス目の座標を取得 (x,yともに0-8)
int PlayerInput::ClickLocation(int* StoneLocate_x, int* StoneLocate_y)
{
	int x, y;

	int x_edge = 309, y_edge = 29;

	int length = 68;

	int interval = 85;

	if (GetMouseInput() != MOUSE_INPUT_LEFT)
	{
		return -1;
	}

	GetMousePoint(&x, &y);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (x_edge + interval * i < x && x < x_edge + interval * i + length &&
				y_edge + interval * j < y && y < y_edge + interval * j + length)
			{
				*StoneLocate_x = i;
				*StoneLocate_y = j;
				return 1;
			}
		}
	}

	return -1;
}

// プレイヤーから合法的なゲーム選択を得る
int PlayerInput::GetChoice(int board[], char color)
{
	int p;
	int x, y;
	int color_n;
	if (color == 'w')
	{
		color_n = 1;
	}
	if (color == 'b')
	{
		color_n = -1;
	}

	if (Othello::Basic::PutAbleAll(board, color_n) == 0)
	{
		return -1;
	}

	for (;;)
	{
		PlayerInput::WaitKeyWithRestart();
		{
			if (PlayerInput::ClickLocation(&x, &y) == 1)
			{
				p = 8 * y + x;
				if (Othello::Basic::PutAble(board, color_n, p) == 1)
				{
					break;
				}
			}
		}

		if (restart)
		{
			return -1;
		}
	}
	return p;
}

void PlayerInput::ProcessInput()
{
	// ESCキーが押されたら
	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		if (MessageBox(NULL, TEXT("ゲームを終了するか？"), TEXT("ずんだもん"), MB_YESNO | MB_SYSTEMMODAL) == IDYES)
		{
			DxLib_End();
			exit(0);
		}
	}
	// CTRL + R が押されたら
	else if (CheckHitKey(KEY_INPUT_LCONTROL) != 0 && CheckHitKey(KEY_INPUT_R) != 0)
	{
		if (MessageBox(NULL, TEXT("最初からやるか？"), TEXT("ずんだもん"), MB_YESNO | MB_SYSTEMMODAL) == IDYES)
		{
			play_num_count++;
			restart = 1;
		}
	}
	// ウィンドウが閉じられたら
	else if (ProcessMessage() == -1)
	{
		DxLib_End();
		exit(0);
	}
}

void PlayerInput::WaitKey()
{
	int old = CheckHitKeyAll();
	for (;;)
	{
		ProcessMessage();
		PlayerInput::ProcessInput();
		int press = CheckHitKeyAll();
		if (press != 0 && old == 0)
		{
			break;
		}
		old = press;
	}
}

void PlayerInput::WaitKeyWithRestart()
{
	int old = CheckHitKeyAll();
	for (;;)
	{
		ProcessMessage();
		PlayerInput::ProcessInput();
		int press = CheckHitKeyAll();
		if (press != 0 && old == 0)
		{
			break;
		}
		old = press;

		if (restart)
		{
			return;
		}
	}
}

void PlayerInput::WaitTimer(int time)
{
	int t = (int)clock();
	for (;;)
	{
		ProcessMessage();
		PlayerInput::ProcessInput();
		if ((int)clock() - t > time)
		{
			break;
		}
	}
}

int PlayerInput::ChosePlayType()
{
	screen.Reset();

	SetFontSize(60);

	ChangeFont(TEXT("ＭＳ ゴシック"));

	int font_handle[2];

	font_handle[0] = CreateFontToHandle(TEXT("ＭＳ ゴシック"), 60, 9, DX_FONTTYPE_EDGE, -1, 4);

	int white = GetColor(255, 255, 255);
	int red = GetColor(255, 0, 0);

	int handle[3][3];

	int down = 80;

	SetFontThickness(4);

	screen.Add("AppData/Images/back1.png", 0, 0, 1280, 720);

	screen.Add("AppData/Images/back2.png", 0, 0, 1280, 720);

	screen.AddStringToHandleWithC(605, 120, white, font_handle[0], "プレイタイプを選択してください");

	handle[0][0] = screen.AddStringWithC(320, 240 + down, red, "ずんだもん");
	handle[0][1] = screen.AddStringWithC(640, 240 + down, red, "VS");
	handle[0][2] = screen.AddStringWithC(960, 240 + down, red, "プレイヤー");

	handle[1][0] = screen.AddStringWithC(320, 360 + down, white, "プレイヤー");
	handle[1][1] = screen.AddStringWithC(640, 360 + down, white, "VS");
	handle[1][2] = screen.AddStringWithC(960, 360 + down, white, "プレイヤー");

	handle[2][0] = screen.AddStringWithC(320, 480 + down, white, "ずんだもん");
	handle[2][1] = screen.AddStringWithC(640, 480 + down, white, "VS");
	handle[2][2] = screen.AddStringWithC(960, 480 + down, white, "中国うさぎ");

	screen.Display();

	int chosed = 0;

	int old = 0;

	for (;;)
	{
		WaitKey();

		if (CheckHitKey(KEY_INPUT_UP))
		{
			if (chosed > 0)
			{
				chosed--;
				for (int i = 0; i < 3; i++)
				{
					screen.ChangeStringColor(handle[chosed][i], red);
					screen.ChangeStringColor(handle[old][i], white);
				}
				old = chosed;
				screen.Display();
			}
			continue;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			if (chosed < 2)
			{
				chosed++;
				for (int i = 0; i < 3; i++)
				{
					screen.ChangeStringColor(handle[chosed][i], red);
					screen.ChangeStringColor(handle[old][i], white);
				}
				old = chosed;
				screen.Display();
			}
			continue;
		}
		if (CheckHitKey(KEY_INPUT_RETURN))
		{
			return chosed;
		}
	}
	return 0;
}
