#include <DxLib.h>
#include <time.h>
#include "variables.h"
#include "funcs.h"

// �v���C���[���N���b�N�����}�X�ڂ̍��W���擾 (x,y�Ƃ���0-8)
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

// �v���C���[���獇�@�I�ȃQ�[���I���𓾂�
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
	// ESC�L�[�������ꂽ��
	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		if (MessageBox(NULL, TEXT("�Q�[�����I�����邩�H"), TEXT("���񂾂���"), MB_YESNO | MB_SYSTEMMODAL) == IDYES)
		{
			DxLib_End();
			exit(0);
		}
	}
	// CTRL + R �������ꂽ��
	else if (CheckHitKey(KEY_INPUT_LCONTROL) != 0 && CheckHitKey(KEY_INPUT_R) != 0)
	{
		if (MessageBox(NULL, TEXT("�ŏ������邩�H"), TEXT("���񂾂���"), MB_YESNO | MB_SYSTEMMODAL) == IDYES)
		{
			play_num_count++;
			restart = 1;
		}
	}
	// �E�B���h�E������ꂽ��
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

	ChangeFont(TEXT("�l�r �S�V�b�N"));

	int font_handle[2];

	font_handle[0] = CreateFontToHandle(TEXT("�l�r �S�V�b�N"), 60, 9, DX_FONTTYPE_EDGE, -1, 4);

	int white = GetColor(255, 255, 255);
	int red = GetColor(255, 0, 0);

	int handle[3][3];

	int down = 80;

	SetFontThickness(4);

	screen.Add("AppData/Images/back1.png", 0, 0, 1280, 720);

	screen.Add("AppData/Images/back2.png", 0, 0, 1280, 720);

	screen.AddStringToHandleWithC(605, 120, white, font_handle[0], "�v���C�^�C�v��I�����Ă�������");

	handle[0][0] = screen.AddStringWithC(320, 240 + down, red, "���񂾂���");
	handle[0][1] = screen.AddStringWithC(640, 240 + down, red, "VS");
	handle[0][2] = screen.AddStringWithC(960, 240 + down, red, "�v���C���[");

	handle[1][0] = screen.AddStringWithC(320, 360 + down, white, "�v���C���[");
	handle[1][1] = screen.AddStringWithC(640, 360 + down, white, "VS");
	handle[1][2] = screen.AddStringWithC(960, 360 + down, white, "�v���C���[");

	handle[2][0] = screen.AddStringWithC(320, 480 + down, white, "���񂾂���");
	handle[2][1] = screen.AddStringWithC(640, 480 + down, white, "VS");
	handle[2][2] = screen.AddStringWithC(960, 480 + down, white, "����������");

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
