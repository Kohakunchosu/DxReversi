#include <DxLib.h>
#include "macros.h"
#include "variables.h"
#include "funcs.h"

// エフェクトの再生をする
int Sound::Effect::Play(int EffectType)
{
	static int init = 1;

	static int put, move;

	if (init)
	{
		put = LoadSoundMem(TEXT("./AppData/Sounds/OthelloEfect/StonePut.mp3"));

		move = LoadSoundMem(TEXT("./AppData/Sounds/OthelloEfect/Move.mp3"));

		ChangeVolumeSoundMem(200, put);

		ChangeVolumeSoundMem(170, move);
	}

	init = 0;

	switch (EffectType)
	{
	case PUT_SOUND:
		printf("%d\n", move);
		int i;
		i = PlaySoundMem(put, DX_PLAYTYPE_BACK);
		printf("%d\n", i);
		break;
	case MOVE_SOUND:
		PlaySoundMem(move, DX_PLAYTYPE_BACK);
		break;
	default:
		return -1;
		break;
	}

	return 0;
}

// ずんだもんの再生
void Sound::Zunda::Play(int PlayType)
{
	for_reaction.zun_said = PlayType;

	static int init = 1;

	int volume = 250;

	// ずんだもんがしゃべり終わるまで待つ、ちなみに待っている間は処理が止まるので注意。
	Sound::Zunda::Wait();
	Sound::Usagi::Wait();

	if (!init)
	{
		DeleteSoundMem(zun_handle);
	}

	switch (PlayType)
	{
	case ZUN_YOUKOSO:
		zun_handle = LoadSoundMem(TEXT("./AppData/Sounds/Zunda/youkoso.wav"));
		ChangeVolumeSoundMem(volume, zun_handle);
		PlaySoundMem(zun_handle, DX_PLAYTYPE_BACK);
		break;

	case ZUN_WIN:
		zun_handle = LoadSoundMem(TEXT("./AppData/Sounds/Zunda/win.wav"));
		ChangeVolumeSoundMem(volume, zun_handle);
		PlaySoundMem(zun_handle, DX_PLAYTYPE_BACK);
		break;

	case ZUN_LOSE:
		zun_handle = LoadSoundMem(TEXT("./AppData/Sounds/Zunda/lose.wav"));
		ChangeVolumeSoundMem(volume, zun_handle);
		PlaySoundMem(zun_handle, DX_PLAYTYPE_BACK);
		break;

	case ZUN_DRAW:
		zun_handle = LoadSoundMem(TEXT("./AppData/Sounds/Zunda/draw.wav"));
		ChangeVolumeSoundMem(volume, zun_handle);
		PlaySoundMem(zun_handle, DX_PLAYTYPE_BACK);
		break;

	case ZUN_CONER:
		zun_handle = LoadSoundMem(TEXT("./AppData/Sounds/Zunda/edge.wav"));
		ChangeVolumeSoundMem(volume, zun_handle);
		PlaySoundMem(zun_handle, DX_PLAYTYPE_BACK);
		break;

	case ZUN_AFTER_LOSE_0:
		zun_handle = LoadSoundMem(TEXT("./AppData/Sounds/Zunda/AfterLose0.wav"));
		ChangeVolumeSoundMem(volume, zun_handle);
		PlaySoundMem(zun_handle, DX_PLAYTYPE_BACK);
		break;

	case ZUN_AFTER_LOSE_1:
		zun_handle = LoadSoundMem(TEXT("./AppData/Sounds/Zunda/AfterLose1.wav"));
		ChangeVolumeSoundMem(volume, zun_handle);
		PlaySoundMem(zun_handle, DX_PLAYTYPE_BACK);
		break;

	case ZUN_AFTER_WIN:
		zun_handle = LoadSoundMem(TEXT("./AppData/Sounds/Zunda/AfterWin0.wav"));
		ChangeVolumeSoundMem(volume, zun_handle);
		PlaySoundMem(zun_handle, DX_PLAYTYPE_BACK);
		break;

	case ZUN_AFTER_DRAW:
		zun_handle = LoadSoundMem(TEXT("./AppData/Sounds/Zunda/AfterDraw0.wav"));
		ChangeVolumeSoundMem(volume, zun_handle);
		PlaySoundMem(zun_handle, DX_PLAYTYPE_BACK);
		break;

	case _3_START_ZUN1:
		zun_handle = LoadSoundMem(TEXT("AppData/Sounds/Voice/3_start_zun1.wav"));
		ChangeVolumeSoundMem(volume, zun_handle);
		PlaySoundMem(zun_handle, DX_PLAYTYPE_BACK);
		break;

	case _3_END_ZUN1:
		zun_handle = LoadSoundMem(TEXT("AppData/Sounds/Voice/3_end_zun1.wav"));
		ChangeVolumeSoundMem(volume, zun_handle);
		PlaySoundMem(zun_handle, DX_PLAYTYPE_BACK);
		break;

	case _3_END_ZUN2:
		zun_handle = LoadSoundMem(TEXT("AppData/Sounds/Voice/3_end_zun2.wav"));
		ChangeVolumeSoundMem(volume, zun_handle);
		PlaySoundMem(zun_handle, DX_PLAYTYPE_BACK);
		break;

	case _3_END_ZUN3:
		zun_handle = LoadSoundMem(TEXT("AppData/Sounds/Voice/3_end_zun3.wav"));
		ChangeVolumeSoundMem(volume, zun_handle);
		PlaySoundMem(zun_handle, DX_PLAYTYPE_BACK);
		break;

	case _2_START_ZUN1:
		zun_handle = LoadSoundMem(TEXT("AppData/Sounds/Voice/2_start_zun1.wav"));
		ChangeVolumeSoundMem(volume, zun_handle);
		PlaySoundMem(zun_handle, DX_PLAYTYPE_BACK);
		break;

	case _2_END_ZUN1:
		zun_handle = LoadSoundMem(TEXT("AppData/Sounds/Voice/2_end_zun1.wav"));
		ChangeVolumeSoundMem(volume, zun_handle);
		PlaySoundMem(zun_handle, DX_PLAYTYPE_BACK);
		break;

	case _2_END_ZUN2:
		zun_handle = LoadSoundMem(TEXT("AppData/Sounds/Voice/2_end_zun2.wav"));
		ChangeVolumeSoundMem(volume, zun_handle);
		PlaySoundMem(zun_handle, DX_PLAYTYPE_BACK);
		break;

	case _2_END_ZUN3:
		zun_handle = LoadSoundMem(TEXT("AppData/Sounds/Voice/2_end_zun3.wav"));
		ChangeVolumeSoundMem(volume, zun_handle);
		PlaySoundMem(zun_handle, DX_PLAYTYPE_BACK);
		break;

	default:
		break;
	}
	init = 0;
}

// ずんだもん待ち
int Sound::Zunda::Wait()
{
	// ずんだもんがしゃべり終わるまで待つ
	for (;;)
	{
		PlayerInput::ProcessInput();
		ProcessMessage();
		if (CheckSoundMem(zun_handle) != 1)
		{
			break;
		}
	}

	return 0;
}

// 2プレイ目以降、ゲーム開始時にずんだもんに何かしゃべらせるためのもの
int Sound::Zunda::Start()
{
	switch (old_result_zun)
	{
	case WIN:
		Sound::Zunda::Play(ZUN_AFTER_WIN);
		break;
	case LOSE:
		Sound::Zunda::Play(Utility::RandBetween(ZUN_AFTER_LOSE_0, ZUN_AFTER_LOSE_1)); // どちらかをランダムに再生
		break;
	case DRAW:
		Sound::Zunda::Play(ZUN_AFTER_DRAW);
		break;
	default:
		break;
	}

	return 0;
}

void Sound::Usagi::Wait()
{
	for (;;)
	{
		PlayerInput::ProcessInput();
		ProcessMessage();
		if (CheckSoundMem(chu_handle) != 1)
		{
			break;
		}
	}
}

// 中国うさぎの再生
void Sound::Usagi::Play(int play_type)
{
	for_reaction.chu_said = play_type;

	int handle;

	static int init = 1;

	int volume = 250;

	Sound::Usagi::Wait();
	Sound::Zunda::Wait();

	if (init == 0)
	{
		DeleteSoundMem(chu_handle);
	}

	switch (play_type)
	{
	case _3_START_CHU1:
		chu_handle = LoadSoundMem(TEXT("AppData/Sounds/Voice/3_start_chu1.wav"));
		ChangeVolumeSoundMem(volume, chu_handle);
		PlaySoundMem(chu_handle, DX_PLAYTYPE_BACK);
		break;
	case _3_END_CHU1:
		chu_handle = LoadSoundMem(TEXT("AppData/Sounds/Voice/3_end_chu1.wav"));
		ChangeVolumeSoundMem(volume, chu_handle);
		PlaySoundMem(chu_handle, DX_PLAYTYPE_BACK);
		break;

	case _3_END_CHU2:
		chu_handle = LoadSoundMem(TEXT("AppData/Sounds/Voice/3_end_chu2.wav"));
		ChangeVolumeSoundMem(volume, chu_handle);
		PlaySoundMem(chu_handle, DX_PLAYTYPE_BACK);
		break;

	case _3_END_CHU3:
		chu_handle = LoadSoundMem(TEXT("AppData/Sounds/Voice/3_end_chu3.wav"));
		ChangeVolumeSoundMem(volume, chu_handle);
		PlaySoundMem(chu_handle, DX_PLAYTYPE_BACK);
		break;

	case _2_START_CHU1:
		chu_handle = LoadSoundMem(TEXT("AppData/Sounds/Voice/2_start_chu1.wav"));
		ChangeVolumeSoundMem(volume, chu_handle);
		PlaySoundMem(chu_handle, DX_PLAYTYPE_BACK);
		break;

	case _3_REACTION_CHU1:
		chu_handle = LoadSoundMem(TEXT("AppData/Sounds/Voice/3_reaction_chu1.wav"));
		ChangeVolumeSoundMem(volume, chu_handle);
		PlaySoundMem(chu_handle, DX_PLAYTYPE_BACK);
		break;

	default:
		break;
	}

	init = 0;
}

void Sound::End::EndVoice1(int board[])
{
	// ずんだもんにゲーム終了時にゲームの結果をしゃべらせる

	int bc = Othello::Basic::CountColor(board, -1);
	int wc = Othello::Basic::CountColor(board, 1);
	Sound::Zunda::Wait();
	if (bc > wc)
	{
		Sound::Zunda::Play(ZUN_LOSE);
	}
	if (bc < wc)
	{
		Sound::Zunda::Play(ZUN_WIN);
	}
	if (bc == wc)
	{
		Sound::Zunda::Play(ZUN_DRAW);
	}
	Sound::Zunda::Wait();
}

void Sound::End::EndVoice2(int board[])
{
	int bc = Othello::Basic::CountColor(board, -1);
	int wc = Othello::Basic::CountColor(board, 1);
	Sound::Zunda::Wait();
	if (bc > wc)
	{
		Sound::Zunda::Play(_2_END_ZUN1);
	}
	if (bc < wc)
	{
		Sound::Zunda::Play(_2_END_ZUN2);
	}
	if (bc == wc)
	{
		Sound::Zunda::Play(_2_END_ZUN3);
	}
	Sound::Zunda::Wait();
}

void Sound::End::EndVoice3(int board[])
{
	int bc = Othello::Basic::CountColor(board, -1);
	int wc = Othello::Basic::CountColor(board, 1);
	Sound::Zunda::Wait();
	if (bc > wc)
	{
		Sound::Zunda::Play(_3_END_ZUN1);
		Sound::Usagi::Play(_3_END_CHU1);
	}
	if (bc < wc)
	{
		Sound::Zunda::Play(_3_END_ZUN3);
		Sound::Usagi::Play(_3_END_CHU3);
	}
	if (bc == wc)
	{
		Sound::Usagi::Play(_3_END_CHU2);
		Sound::Zunda::Play(_3_END_ZUN2);
	}
	Sound::Zunda::Wait();
	Sound::Usagi::Wait();
}

void Sound::Start::StartVoice1()
{
	static int init = 1;
	if (init == 0)
	{
		switch (old_result_zun)
		{
		case WIN:
			Sound::Zunda::Play(ZUN_AFTER_WIN);
			break;
		case LOSE:
			Sound::Zunda::Play(Utility::RandBetween(ZUN_AFTER_LOSE_0, ZUN_AFTER_LOSE_1)); // どちらかをランダムに再生
			break;
		case DRAW:
			Sound::Zunda::Play(ZUN_AFTER_DRAW);
			break;
		default:
			break;
		}
	}
	if (init == 1)
	{
		// ずんだもん煽り
		PlayerInput::WaitTimer(500);
		if (CheckMusic())
		{
			Sound::Zunda::Play(ZUN_YOUKOSO);
		}
	}

	printf("sound wait 1\n");
	Sound::Zunda::Wait();
	printf("sound wait 2\n");

	init = 0;
}

void Sound::Start::StartVoice2()
{
	Sound::Zunda::Play(_2_START_ZUN1);
	Sound::Zunda::Wait();
	Sound::Usagi::Play(_2_START_CHU1);
	Sound::Usagi::Wait();
}

void Sound::Start::StartVoice3()
{
	Sound::Zunda::Play(_3_START_ZUN1);
	Sound::Zunda::Wait();
	Sound::Usagi::Play(_3_START_CHU1);
	Sound::Usagi::Wait();
}

// ai vs player
void Sound::Reaction::Voice1()
{
	if (for_reaction.color == BLACK)
	{
		if (for_reaction.position == 0 || for_reaction.position == 7 ||
			for_reaction.position == 56 || for_reaction.position == 63)
		{
			Sound::Zunda::Play(ZUN_CONER);
		}
	}

	if (for_reaction.color == WHITE)
	{
	}
}

// player vs player
void Sound::Reaction::Voice2()
{
	if (for_reaction.color == BLACK)
	{
	}

	if (for_reaction.color == WHITE)
	{
	}
}

// ai vs ai
void Sound::Reaction::Voice3()
{
	const int ZUN = 1;
	const int CHU = 2;
	static int player = 0;
	if (for_reaction.color == BLACK)
	{
		if (for_reaction.position == 0 || for_reaction.position == 7 ||
			for_reaction.position == 56 || for_reaction.position == 63)
		{
			Sound::Zunda::Play(ZUN_CONER);
			player = ZUN;
		}
	}

	if (for_reaction.color == WHITE)
	{
		if (for_reaction.zun_said == ZUN_CONER && player == ZUN)
		{
			Sound::Usagi::Play(_3_REACTION_CHU1);
			player = CHU;
		}
	}
}
