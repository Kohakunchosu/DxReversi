#include <DxLib.h>
#include "variables.h"
#include "funcs.h"

// �v���O���������s����Ă����ɕK�v�ȏ������s��
int Init::Program()
{
	SetWindowText(TEXT("DxReversi"));

	if (MessageBox(NULL, TEXT("�t���X�N���[�����[�h�ɂ��܂����H"), TEXT(" "), MB_YESNO) == IDNO)
	{
		// �E�B���h�E���[�h�ɂ��邩�ǂ���
		ChangeWindowMode(TRUE);

		// �c���̃h�b�g����ݒ�
		SetGraphMode(1280, 720, 32);

		// �E�B���h�E�̑傫����ύX�ł��邩�ǂ���
		SetWindowSizeChangeEnableFlag(TRUE);

		// �f�t�H���g�̃E�B���h�E�T�C�Y�̐ݒ�
		SetWindowSizeExtendRate(1.3);

		DxLib_Init();

		// �}�E�X��\�����邩�ǂ���
		SetMouseDispFlag(TRUE);
	}
	else
	{
		DxLib_Init();

		// �E�B���h�E���[�h�ɂ��邩�ǂ���
		ChangeWindowMode(FALSE);

		// �c���̃h�b�g����ݒ�
		SetGraphMode(1280, 720, 32);

		// �}�E�X��\�����邩�ǂ���
		SetMouseDispFlag(TRUE);
	}

	// �`���̐ݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	SetAlwaysRunFlag(TRUE);

	DispR::Start();

	PlayerInput::WaitTimer(500);

	for (;;)
	{
		// �}�E�X�ŃX�^�[�g�{�^�����������܂ōs���鏈��
		PlayerInput::WaitKey();
		if (GetMouseInput() == MOUSE_INPUT_LEFT)
		{
			int x, y; // �}�E�X�̈ʒu���擾
			GetMousePoint(&x, &y);
			if (452 < x && x < 868 && 508 < y && y < 624)
			{
				DispR::StartPressed();
				PlayerInput::WaitTimer(500);
				break;
			}
		}
	}

	return 0;
}

// �Q�[���J�n���̏�������������
int Init::Game1(int board[])
{
	// �Q�[���̏�������������

	static int init = 1;

	screen.Reset();

	StopMusic();
	PlayMusic(TEXT("./AppData/Sounds/OthelloBGM/0.mp3"), DX_PLAYTYPE_LOOP);
	SetVolumeMusic(130);

	if (play_num_count == 0)
	{
		// ������Ԃ̐���
		Othello::Basic::InitBoard(board);
		DispV::PrintBoard1(board, TRUE, 0);
		screen.Display();
	}
	else
	{
		if (init == 1)
		{
			// ������Ԃ̐���
			Othello::Basic::InitBoard(board);
			DispV::PrintBoard1(board, TRUE, 0);
			Animation::StoneDrop2(board_old, 1600);
		}
		else
		{
			// ������Ԃ̐���
			Othello::Basic::InitBoard(board);
			DispV::PrintBoard1(board, TRUE, 0);
			Animation::StoneDrop2(board_old, 1600);

			PlayerInput::WaitTimer(500);
		}
	}

	init = 0;

	return 0;
}

// �Q�[���J�n���̏�������������
int Init::Game2(int board[])
{
	// �Q�[���̏�������������

	static int init = 1;

	screen.Reset();

	StopMusic();
	PlayMusic(TEXT("./AppData/Sounds/OthelloBGM/1.mp3"), DX_PLAYTYPE_LOOP);
	SetVolumeMusic(130);

	if (play_num_count != 0)
	{
		// ������Ԃ̐���
		Othello::Basic::InitBoard(board);
		DispV::PrintBoard2(board, TRUE, 0);
		Animation::StoneDrop2(board_old, 1600);
	}
	else
	{
		// ������Ԃ̐���
		Othello::Basic::InitBoard(board);
		DispV::PrintBoard2(board, TRUE, 0);
		screen.Display();
	}
	init = 0;

	return 0;
}

int Init::Game3(int board[])
{
	// �Q�[���̏�������������

	static int init = 1;

	screen.Reset();

	StopMusic();
	PlayMusic(TEXT("./AppData/Sounds/OthelloBGM/2.mp3"), DX_PLAYTYPE_LOOP);
	SetVolumeMusic(130);

	if (play_num_count == 0)
	{
		// ������Ԃ̐���
		Othello::Basic::InitBoard(board);
		DispV::PrintBoard3(board, TRUE, 0);
		screen.Display();

		// ��������̃Z���t�Ȃ�
		/*thre will be written the code*/
	}
	else
	{
		if (init == 1)
		{
			// ������Ԃ̐���
			Othello::Basic::InitBoard(board);

			// �����A�j���[�V�����ƂƂ��ɃQ�[���X�^�[�g��ʂɑJ��
			DispV::PrintBoard3(board, TRUE, 0);
			Animation::StoneDrop2(board_old, 1600);

			/// ��������̃Z���t�Ȃ�
			/*thre will be written the code*/
		}
		else
		{
			// ������Ԃ̐���
			Othello::Basic::InitBoard(board);

			// �����A�j���[�V�����ƂƂ��ɃQ�[���X�^�[�g��ʂɑJ��
			DispV::PrintBoard3(board, TRUE, 0);
			Animation::StoneDrop2(board_old, 1600);

			PlayerInput::WaitTimer(500);

			// ��������̃Z���t�Ȃ�
			/*thre will be written the code*/
		}
	}

	Sound::Zunda::Wait();

	init = 0;

	return 0;
}