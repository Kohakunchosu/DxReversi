#include<list>
#include "funcs.h"
#include "screen.h"
#include "variables.h"
#include "macros.h"

// �Ֆʂ̏�Ԃ����ۂ̉�ʏ�ɕ\������
int DispR::PrintBoard(int board[], int reset, int turn_b)
{
	// turn_b�͉��̃^�[���i�F�j���I���������ォ�Ƃ�������
	// turn_b��0�������n���ꂽ�ꍇ���ɓ��ʂȏ����͂����Ƀf�t�H���g�̉摜��\������B

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

	// screen.Reset();

	if (Othello::Basic::IsEnd(board))
	{
		old_handles.emplace_front(
			screen.Add("./AppData/Images/OthelloGame.jpg", 0, 0, 1280, 720));
	}
	else
	{
		if (turn_b == BLACK)
		{
			if (!Othello::Basic::PutAbleAll(board, -turn_b))
			{
				old_handles.emplace_front(
					screen.Add("./AppData/Images/ZunTurn.jpg", 0, 0, 1280, 720));
			}
			else
			{
				old_handles.emplace_front(
					screen.Add("./AppData/Images/YouTurn.jpg", 0, 0, 1280, 720));
			}
		}
		if (turn_b == WHITE)
		{
			if (!Othello::Basic::PutAbleAll(board, -turn_b))
			{
				old_handles.emplace_front(
					screen.Add("./AppData/Images/YouTurn.jpg", 0, 0, 1280, 720));
			}
			else
			{
				old_handles.emplace_front(
					screen.Add("./AppData/Images/ZunTurn.jpg", 0, 0, 1280, 720));
			}
		}
		if (!turn_b)
		{
			old_handles.emplace_front(
				screen.Add("./AppData/Images/OthelloGame.jpg", 0, 0, 1280, 720));
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
	init = 0;
	screen.Display();
	return 0;
}

// �X�^�[�g��ʂ�\������
int DispR::Start()
{
	screen.Add("./AppData/Images/Opening.jpg", 0, 0, 1280, 720);

	{
		int x = 452, y = 508;
		float rate = 3.59;
		int high = 116;
		int width = (float)high * rate;

		screen.Add("./AppData/Images/Bottun.png", x, y, x + width, y + high);
	}

	screen.Display();

	return 0;
}

// �{�^���������ꂽ��Ԃ̃X�^�[�g��ʂ�\������
int DispR::StartPressed()
{
	screen.Reset();
	screen.Add("./AppData/Images/Opening.jpg", 0, 0, 1280, 720);

	int x = 452, y = 508;
	float rate = 3.59;
	int high = 116;
	int width = (float)high * rate;

	screen.Add("./AppData/Images/BottunPushed.png", x, y, x + width, y + high);

	screen.Display();

	return 0;
}
