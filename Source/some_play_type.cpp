#include <DxLib.h>
#include "macros.h"
#include "variables.h"
#include "funcs.h"

void SomePlayType::PlayerVsAI()
{
	int position;
	int color;
	int board[64];
	int count = 1;
	int total = 1;
	int count_for_turn = 2;
	static int init = 1;

	Init::Game1(board);

	Sound::Start::StartVoice1();

	screen.Reset();
	DispV::PrintBoard1(board, TRUE, WHITE);
	screen.Display();

	PlayerInput::WaitTimer(500);

	for (;;)
	{
		ProcessMessage();
		if (restart)
		{
			Othello::Basic::BoardCpy(board_old, board);
			StopMusic();
			return;
		}
		if (count_for_turn % 2 == 0)
		{
			// ��(AI)�̃^�[��

			position = Othello::AI::Chose::Strong(board, -1, &count, total);

			color = -1;

			if (position != -1)
			{
				// �����X�L�b�v���ꂸ�ɂ������Ƃ��ł�����
				int x = position % 8, y = position / 8;
				Sound::Effect::Play(PUT_SOUND);
				int handle = DispV::PutStone(x, y, 'b');
				screen.Display();
				screen.Remove(handle);

				// ���A�N�V�����̂��߂̏���
				for_reaction.position_old = for_reaction.position;
				for_reaction.position = position;
				for_reaction.color = BLACK;
				Sound::Reaction::Voice1();

				PlayerInput::WaitTimer(500);
			}
		}
		else
		{
			// ��(�v���C���[)�̃^�[��
			// point = Othello::AI::Chose::Rand(board, White);
			position = PlayerInput::GetChoice(board, 'w');

			if (restart)
			{
				Othello::Basic::BoardCpy(board_old, board);
				StopMusic();
				return;
			}

			color = 1;

			if (position != -1)
			{
				int x = position % 8, y = position / 8;
				Sound::Effect::Play(PUT_SOUND);
				int handle = DispV::PutStone(x, y, 'w');
				screen.Display();
				screen.Remove(handle);

				// ���A�N�V�����̂��߂̏���
				for_reaction.position_old = for_reaction.position;
				for_reaction.position = position;
				for_reaction.color = WHITE;
				Sound::Reaction::Voice1();

				PlayerInput::WaitTimer(500);
			}
		}
		if (position != -1)
		{
			// point��-1�ł͂Ȃ��Ƃ��Ɂi���Ȃ킿���܂��͔��̂ǂ��炩���X�L�b�v����邱�Ƃ��Ȃ�������j���s�����if���ł���
			// �܂���̏ꍇ�͂���if���̒��g�����s����邱�ƂƂȂ�

			total++;
			count++;

			if (count > deepest)
			{
				count = 1;
			}

			int board_old[64];

			// �����A�j���[�V�����p
			Othello::Basic::BoardCpy(board_old, board);

			Othello::Basic::ChangeBoard(board, color, position);

			// screen.Reset();

			DispV::PrintBoard1(board, FALSE, color);

			Sound::Effect::Play(MOVE_SOUND);

			// �����A�j���[�V����
			Animation::StoneDrop1(board, board_old, 1200);
		}

		if (Othello::Basic::IsEnd(board))
		{
			PlayerInput::WaitTimer(1000);

			Sound::End::EndVoice1(board);
			PlayerInput::WaitTimer(500);

			int continue_game = MessageBox(NULL, TEXT("\n�Q�[���𑱂��邩???"), TEXT("���񂾂���"), MB_YESNO);

			if (continue_game == IDNO)
			{
				DxLib_End();
				exit(0);
			}

			Othello::Basic::BoardCpy(board_old, board);

			int black, white;
			black = Othello::Basic::CountColor(board, BLACK);
			white = Othello::Basic::CountColor(board, WHITE);
			if (black > white)
			{
				old_result_zun = LOSE;
			}
			if (white == black)
			{
				old_result_zun = DRAW;
			}
			if (white > black)
			{
				old_result_zun = WIN;
			}
			play_num_count++;
			break;
		}
		count_for_turn++;
	}
	init = 0;
	StopMusic();
}

void SomePlayType::PlayerVsPlayer()
{
	int position;
	int color;
	int board[64];
	int count = 1;
	int total = 1;
	int count_for_turn = 2;
	static int init = 1;

	Init::Game2(board);

	Sound::Start::StartVoice2();

	// �����ō��ɑ΂��Ă̑I����ʂ��\�������
	screen.Reset();
	DispV::PrintBoard2(board, TRUE, WHITE);
	screen.Display();

	for (;;)
	{
		ProcessMessage();
		if (restart)
		{
			Othello::Basic::BoardCpy(board_old, board);
			StopMusic();
			return;
		}
		if (count_for_turn % 2 == 0)
		{
			// ���̃^�[��
			position = PlayerInput::GetChoice(board, 'b');

			if (restart)
			{
				Othello::Basic::BoardCpy(board_old, board);
				StopMusic();
				return;
			}

			color = -1;

			if (position != -1)
			{
				// �����X�L�b�v���ꂸ�ɂ������Ƃ��ł�����
				int x = position % 8, y = position / 8;
				Sound::Effect::Play(PUT_SOUND);
				int handle = DispV::PutStone(x, y, 'b');
				screen.Display();
				screen.Remove(handle);

				// ���A�N�V�����̂��߂̏���
				for_reaction.position_old = for_reaction.position;
				for_reaction.position = position;
				for_reaction.color = BLACK;
				Sound::Reaction::Voice2();

				PlayerInput::WaitTimer(500);
			}
		}
		else
		{
			// ���̃^�[��
			position = PlayerInput::GetChoice(board, 'w');

			if (restart)
			{
				Othello::Basic::BoardCpy(board_old, board);
				StopMusic();
				return;
			}

			color = 1;

			if (position != -1)
			{
				int x = position % 8, y = position / 8;
				Sound::Effect::Play(PUT_SOUND);
				int handle = DispV::PutStone(x, y, 'w');
				screen.Display();
				screen.Remove(handle);

				// ���A�N�V�����̂��߂̏���
				for_reaction.position_old = for_reaction.position;
				for_reaction.position = position;
				for_reaction.color = WHITE;
				Sound::Reaction::Voice2();

				PlayerInput::WaitTimer(500);
			}
		}
		if (position != -1)
		{
			// point��-1�ł͂Ȃ��Ƃ��Ɂi���Ȃ킿���܂��͔��̂ǂ��炩���X�L�b�v����邱�Ƃ��Ȃ�������j���s�����if���ł���
			// �܂���̏ꍇ�͂���if���̒��g�����s����邱�ƂƂȂ�

			total++;
			count++;

			if (count > deepest)
			{
				count = 1;
			}

			int board_old[64];

			// �����A�j���[�V�����p
			Othello::Basic::BoardCpy(board_old, board);

			Othello::Basic::ChangeBoard(board, color, position);

			// screen.Reset();

			DispV::PrintBoard2(board, FALSE, color);

			Sound::Effect::Play(MOVE_SOUND);

			// �����A�j���[�V����
			Animation::StoneDrop1(board, board_old, 1200);
		}

		if (Othello::Basic::IsEnd(board))
		{
			PlayerInput::WaitTimer(1000);

			Sound::End::EndVoice2(board);
			PlayerInput::WaitTimer(500);

			int continue_game = MessageBox(NULL, TEXT("\n�Q�[���𑱂��邩???"), TEXT("���񂾂���"), MB_YESNO);

			if (continue_game == IDNO)
			{
				DxLib_End();
				exit(0);
			}

			Othello::Basic::BoardCpy(board_old, board);
			play_num_count++;
			break;
		}
		count_for_turn++;
	}
	init = 0;
	StopMusic();
}

void SomePlayType::AIVsAI()
{
	int position;
	int color;
	int board[64];
	int count = 1;
	int total = 1;
	int count_for_turn = 2;
	static int init = 1;

	Init::Game3(board);

	Sound::Start::StartVoice3();

	screen.Reset();
	DispV::PrintBoard3(board, TRUE, WHITE);
	screen.Display();

	PlayerInput::WaitTimer(1000);

	for (;;)
	{
		ProcessMessage();
		// �v���C���[�����X�^�[�g�����I�������ꍇ�ɃQ�[�����I��
		if (restart)
		{
			Othello::Basic::BoardCpy(board_old, board);
			StopMusic();
			return;
		}
		if (count_for_turn % 2 == 0)
		{
			// ��(AI)�̃^�[��

			position = Othello::AI::Chose::Strong(board, -1, &count, total);

			color = -1;

			if (position != -1)
			{
				// �����X�L�b�v���ꂸ�ɂ������Ƃ��ł�����
				int x = position % 8, y = position / 8;
				Sound::Effect::Play(PUT_SOUND);
				int handle = DispV::PutStone(x, y, 'b');
				screen.Display();
				screen.Remove(handle);

				// ���A�N�V�����̂��߂̏���
				for_reaction.position_old = for_reaction.position;
				for_reaction.position = position;
				for_reaction.color = BLACK;
				Sound::Reaction::Voice3();

				PlayerInput::WaitTimer(500);
			}
		}
		else
		{
			// ��(�v���C���[)�̃^�[��
			position = Othello::AI::Chose::Rand(board, WHITE);

			color = 1;

			if (position != -1)
			{
				int x = position % 8, y = position / 8;
				int handle = DispV::PutStone(x, y, 'w');
				screen.Display();
				Sound::Effect::Play(PUT_SOUND);
				screen.Remove(handle);

				// ���A�N�V�����̂��߂̏���
				for_reaction.position_old = for_reaction.position;
				for_reaction.position = position;
				for_reaction.color = WHITE;
				Sound::Reaction::Voice3();

				PlayerInput::WaitTimer(500);
			}
		}
		if (position != -1)
		{
			// point��-1�ł͂Ȃ��Ƃ��Ɂi���Ȃ킿���܂��͔��̂ǂ��炩���X�L�b�v����邱�Ƃ��Ȃ�������j���s�����if���ł���
			// �܂���̏ꍇ�͂���if���̒��g�����s����邱�ƂƂȂ�

			total++;
			count++;

			if (count > deepest)
			{
				count = 1;
			}

			int board_old[64];

			// �����A�j���[�V�����p
			Othello::Basic::BoardCpy(board_old, board);

			Othello::Basic::ChangeBoard(board, color, position);

			// screen.Reset();

			DispV::PrintBoard3(board, FALSE, color);

			Sound::Effect::Play(MOVE_SOUND);

			// �����A�j���[�V����
			Animation::StoneDrop1(board, board_old, 1200);
		}

		if (Othello::Basic::IsEnd(board))
		{
			PlayerInput::WaitTimer(1000);

			Sound::End::EndVoice3(board);
			PlayerInput::WaitTimer(500);

			int continue_game = MessageBox(NULL, TEXT("\n�Q�[���𑱂��邩???"), TEXT("���񂾂���"), MB_YESNO);

			if (continue_game == IDNO)
			{
				DxLib_End();
				exit(0);
			}

			Othello::Basic::BoardCpy(board_old, board);
			play_num_count++;
			break;
		}
		count_for_turn++;
	}
	init = 0;
	StopMusic();
}
