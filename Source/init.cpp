#include <DxLib.h>
#include "variables.h"
#include "funcs.h"

// プログラムが実行されてすぐに必要な処理を行う
int Init::Program()
{
	SetWindowText(TEXT("DxReversi"));

	if (MessageBox(NULL, TEXT("フルスクリーンモードにしますか？"), TEXT(" "), MB_YESNO) == IDNO)
	{
		// ウィンドウモードにするかどうか
		ChangeWindowMode(TRUE);

		// 縦横のドット数を設定
		SetGraphMode(1280, 720, 32);

		// ウィンドウの大きさを変更できるかどうか
		SetWindowSizeChangeEnableFlag(TRUE);

		// デフォルトのウィンドウサイズの設定
		SetWindowSizeExtendRate(1.3);

		DxLib_Init();

		// マウスを表示するかどうか
		SetMouseDispFlag(TRUE);
	}
	else
	{
		DxLib_Init();

		// ウィンドウモードにするかどうか
		ChangeWindowMode(FALSE);

		// 縦横のドット数を設定
		SetGraphMode(1280, 720, 32);

		// マウスを表示するかどうか
		SetMouseDispFlag(TRUE);
	}

	// 描画先の設定
	SetDrawScreen(DX_SCREEN_BACK);

	SetAlwaysRunFlag(TRUE);

	DispR::Start();

	PlayerInput::WaitTimer(500);

	for (;;)
	{
		// マウスでスタートボタンが押されるまで行われる処理
		PlayerInput::WaitKey();
		if (GetMouseInput() == MOUSE_INPUT_LEFT)
		{
			int x, y; // マウスの位置を取得
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

// ゲーム開始時の初期処理をする
int Init::Game1(int board[])
{
	// ゲームの初期処理をする

	static int init = 1;

	screen.Reset();

	StopMusic();
	PlayMusic(TEXT("./AppData/Sounds/OthelloBGM/0.mp3"), DX_PLAYTYPE_LOOP);
	SetVolumeMusic(130);

	if (play_num_count == 0)
	{
		// 初期状態の生成
		Othello::Basic::InitBoard(board);
		DispV::PrintBoard1(board, TRUE, 0);
		screen.Display();
	}
	else
	{
		if (init == 1)
		{
			// 初期状態の生成
			Othello::Basic::InitBoard(board);
			DispV::PrintBoard1(board, TRUE, 0);
			Animation::StoneDrop2(board_old, 1600);
		}
		else
		{
			// 初期状態の生成
			Othello::Basic::InitBoard(board);
			DispV::PrintBoard1(board, TRUE, 0);
			Animation::StoneDrop2(board_old, 1600);

			PlayerInput::WaitTimer(500);
		}
	}

	init = 0;

	return 0;
}

// ゲーム開始時の初期処理をする
int Init::Game2(int board[])
{
	// ゲームの初期処理をする

	static int init = 1;

	screen.Reset();

	StopMusic();
	PlayMusic(TEXT("./AppData/Sounds/OthelloBGM/1.mp3"), DX_PLAYTYPE_LOOP);
	SetVolumeMusic(130);

	if (play_num_count != 0)
	{
		// 初期状態の生成
		Othello::Basic::InitBoard(board);
		DispV::PrintBoard2(board, TRUE, 0);
		Animation::StoneDrop2(board_old, 1600);
	}
	else
	{
		// 初期状態の生成
		Othello::Basic::InitBoard(board);
		DispV::PrintBoard2(board, TRUE, 0);
		screen.Display();
	}
	init = 0;

	return 0;
}

int Init::Game3(int board[])
{
	// ゲームの初期処理をする

	static int init = 1;

	screen.Reset();

	StopMusic();
	PlayMusic(TEXT("./AppData/Sounds/OthelloBGM/2.mp3"), DX_PLAYTYPE_LOOP);
	SetVolumeMusic(130);

	if (play_num_count == 0)
	{
		// 初期状態の生成
		Othello::Basic::InitBoard(board);
		DispV::PrintBoard3(board, TRUE, 0);
		screen.Display();

		// 何かしらのセリフなど
		/*thre will be written the code*/
	}
	else
	{
		if (init == 1)
		{
			// 初期状態の生成
			Othello::Basic::InitBoard(board);

			// 物理アニメーションとともにゲームスタート画面に遷移
			DispV::PrintBoard3(board, TRUE, 0);
			Animation::StoneDrop2(board_old, 1600);

			/// 何かしらのセリフなど
			/*thre will be written the code*/
		}
		else
		{
			// 初期状態の生成
			Othello::Basic::InitBoard(board);

			// 物理アニメーションとともにゲームスタート画面に遷移
			DispV::PrintBoard3(board, TRUE, 0);
			Animation::StoneDrop2(board_old, 1600);

			PlayerInput::WaitTimer(500);

			// 何かしらのセリフなど
			/*thre will be written the code*/
		}
	}

	Sound::Zunda::Wait();

	init = 0;

	return 0;
}