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
			// 黒(AI)のターン

			position = Othello::AI::Chose::Strong(board, -1, &count, total);

			color = -1;

			if (position != -1)
			{
				// 黒がスキップされずにおくことができたら
				int x = position % 8, y = position / 8;
				Sound::Effect::Play(PUT_SOUND);
				int handle = DispV::PutStone(x, y, 'b');
				screen.Display();
				screen.Remove(handle);

				// リアクションのための処理
				for_reaction.position_old = for_reaction.position;
				for_reaction.position = position;
				for_reaction.color = BLACK;
				Sound::Reaction::Voice1();

				PlayerInput::WaitTimer(500);
			}
		}
		else
		{
			// 白(プレイヤー)のターン
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

				// リアクションのための処理
				for_reaction.position_old = for_reaction.position;
				for_reaction.position = position;
				for_reaction.color = WHITE;
				Sound::Reaction::Voice1();

				PlayerInput::WaitTimer(500);
			}
		}
		if (position != -1)
		{
			// pointが-1ではないときに（すなわち黒または白のどちらかがスキップされることがなかったら）実行されるif文である
			// つまり大抵の場合はこのif文の中身が実行されることとなる

			total++;
			count++;

			if (count > deepest)
			{
				count = 1;
			}

			int board_old[64];

			// 物理アニメーション用
			Othello::Basic::BoardCpy(board_old, board);

			Othello::Basic::ChangeBoard(board, color, position);

			// screen.Reset();

			DispV::PrintBoard1(board, FALSE, color);

			Sound::Effect::Play(MOVE_SOUND);

			// 物理アニメーション
			Animation::StoneDrop1(board, board_old, 1200);
		}

		if (Othello::Basic::IsEnd(board))
		{
			PlayerInput::WaitTimer(1000);

			Sound::End::EndVoice1(board);
			PlayerInput::WaitTimer(500);

			int continue_game = MessageBox(NULL, TEXT("\nゲームを続けるか???"), TEXT("ずんだもん"), MB_YESNO);

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

	// ここで黒に対しての選択画面が表示される
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
			// 黒のターン
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
				// 黒がスキップされずにおくことができたら
				int x = position % 8, y = position / 8;
				Sound::Effect::Play(PUT_SOUND);
				int handle = DispV::PutStone(x, y, 'b');
				screen.Display();
				screen.Remove(handle);

				// リアクションのための処理
				for_reaction.position_old = for_reaction.position;
				for_reaction.position = position;
				for_reaction.color = BLACK;
				Sound::Reaction::Voice2();

				PlayerInput::WaitTimer(500);
			}
		}
		else
		{
			// 白のターン
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

				// リアクションのための処理
				for_reaction.position_old = for_reaction.position;
				for_reaction.position = position;
				for_reaction.color = WHITE;
				Sound::Reaction::Voice2();

				PlayerInput::WaitTimer(500);
			}
		}
		if (position != -1)
		{
			// pointが-1ではないときに（すなわち黒または白のどちらかがスキップされることがなかったら）実行されるif文である
			// つまり大抵の場合はこのif文の中身が実行されることとなる

			total++;
			count++;

			if (count > deepest)
			{
				count = 1;
			}

			int board_old[64];

			// 物理アニメーション用
			Othello::Basic::BoardCpy(board_old, board);

			Othello::Basic::ChangeBoard(board, color, position);

			// screen.Reset();

			DispV::PrintBoard2(board, FALSE, color);

			Sound::Effect::Play(MOVE_SOUND);

			// 物理アニメーション
			Animation::StoneDrop1(board, board_old, 1200);
		}

		if (Othello::Basic::IsEnd(board))
		{
			PlayerInput::WaitTimer(1000);

			Sound::End::EndVoice2(board);
			PlayerInput::WaitTimer(500);

			int continue_game = MessageBox(NULL, TEXT("\nゲームを続けるか???"), TEXT("ずんだもん"), MB_YESNO);

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
		// プレイヤーがリスタートするを選択した場合にゲームを終了
		if (restart)
		{
			Othello::Basic::BoardCpy(board_old, board);
			StopMusic();
			return;
		}
		if (count_for_turn % 2 == 0)
		{
			// 黒(AI)のターン

			position = Othello::AI::Chose::Strong(board, -1, &count, total);

			color = -1;

			if (position != -1)
			{
				// 黒がスキップされずにおくことができたら
				int x = position % 8, y = position / 8;
				Sound::Effect::Play(PUT_SOUND);
				int handle = DispV::PutStone(x, y, 'b');
				screen.Display();
				screen.Remove(handle);

				// リアクションのための処理
				for_reaction.position_old = for_reaction.position;
				for_reaction.position = position;
				for_reaction.color = BLACK;
				Sound::Reaction::Voice3();

				PlayerInput::WaitTimer(500);
			}
		}
		else
		{
			// 白(プレイヤー)のターン
			position = Othello::AI::Chose::Rand(board, WHITE);

			color = 1;

			if (position != -1)
			{
				int x = position % 8, y = position / 8;
				int handle = DispV::PutStone(x, y, 'w');
				screen.Display();
				Sound::Effect::Play(PUT_SOUND);
				screen.Remove(handle);

				// リアクションのための処理
				for_reaction.position_old = for_reaction.position;
				for_reaction.position = position;
				for_reaction.color = WHITE;
				Sound::Reaction::Voice3();

				PlayerInput::WaitTimer(500);
			}
		}
		if (position != -1)
		{
			// pointが-1ではないときに（すなわち黒または白のどちらかがスキップされることがなかったら）実行されるif文である
			// つまり大抵の場合はこのif文の中身が実行されることとなる

			total++;
			count++;

			if (count > deepest)
			{
				count = 1;
			}

			int board_old[64];

			// 物理アニメーション用
			Othello::Basic::BoardCpy(board_old, board);

			Othello::Basic::ChangeBoard(board, color, position);

			// screen.Reset();

			DispV::PrintBoard3(board, FALSE, color);

			Sound::Effect::Play(MOVE_SOUND);

			// 物理アニメーション
			Animation::StoneDrop1(board, board_old, 1200);
		}

		if (Othello::Basic::IsEnd(board))
		{
			PlayerInput::WaitTimer(1000);

			Sound::End::EndVoice3(board);
			PlayerInput::WaitTimer(500);

			int continue_game = MessageBox(NULL, TEXT("\nゲームを続けるか???"), TEXT("ずんだもん"), MB_YESNO);

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
