#include <DxLib.h>
#include "macros.h"
#include "variables.h"
#include "funcs.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Init::Program();

	for (;;)
	{
		int play_type = PlayerInput::ChosePlayType();

		restart = 0;

		if (play_type == PLAYER_VS_PLAYER)
		{
			SomePlayType::PlayerVsPlayer();
			continue;
		}

		if (play_type == AI_VS_PLAYER)
		{
			SomePlayType::PlayerVsAI();
			continue;
		}

		if (play_type == AI_VS_AI)
		{
			SomePlayType::AIVsAI();
			continue;
		}
	}

	return 0;
}
