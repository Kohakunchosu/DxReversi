#include <list>
#include <Box2D/Box2D.h>
#include <DxLib.h>
#include <time.h>
#include "funcs.h"
#include "variables.h"
#include "macros.h"

void Animation::StoneDrop1(int board_new[], int board_old[], int time)
{
	std::list<int> change_point;

	int drop_color;

	for (int i = 0; i < 64; i++)
	{
		if (board_new[i] != board_old[i] && board_old[i] != 0)
		{
			change_point.emplace_front(i);
			drop_color = board_old[i];
		}
	}

	int body_num = change_point.size();

	// Define the gravity vector.
	b2Vec2 gravity(0.0, -9.8 * scale_change);

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(gravity);

	//-------------------------------------------------------------------------------------------

	b2Body* groundBody = Physics::CreateStaticBox(50.0f * scale_change, 10.0f * scale_change,
		0.0f * scale_change, -10.01f * scale_change, &world);

	//-------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------

	b2Body** body;
	body = new b2Body * [body_num];

	float x_coner = 343.0 * (1.0 / DPM) * (1.0 / scale_change),
		y_coner = (720.0 - 63.0) * (1.0 / DPM) * (1.0 / scale_change);

	float interval = 85.0 * (1.0 / DPM) * (1.0 / scale_change);

	{
		int x, y;
		int ct = -1;
		for (int i : change_point)
		{
			ct++;
			x = i % 8;
			y = i / 8;
			body[ct] = Physics::CreateCircle(
				1.7 * (1.0 / 100.0) * scale_change,
				(x_coner + interval * x + Utility::RandBetweenF(-0.1 * (1.0 / 100.0), 0.1 * (1.0 / 100.0))) * scale_change,
				(y_coner - interval * y + Utility::RandBetweenF(-0.1 * (1.0 / 100.0), 0.1 * (1.0 / 100.0))) * scale_change,
				&world);
		}
	}
	//-------------------------------------------------------------------------------------------

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 10;
	int32 positionIterations = 6;

	int init = 1;

	int* handles;
	handles = new int[body_num];

	// This is our little game loop.
	for (int32 i = 0; i < 60.0 * ((float)time / 1000.0); i++)
	{
		double time = (double)clock();

		// 指定時間の７割以上に達したら地面を無効
		if (60.0 * 0.9 < i)
		{
			groundBody->SetActive(FALSE);
		}

		ProcessMessage();
		PlayerInput::ProcessInput();

		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world.Step(timeStep, velocityIterations, positionIterations);

		// Now print the position and angle of the body.
		b2Vec2 position;

		if (init)
		{
			if (drop_color == BLACK)
			{
				for (int j = 0; j < body_num; j++)
				{
					position = body[j]->GetPosition();
					handles[j] = screen.AddWithC("AppData/Images/black.png", 145, 145, Physics::ExX(position.x), Physics::ExY(position.y), 0.0);
				}
			}
			else
			{
				for (int j = 0; j < body_num; j++)
				{
					position = body[j]->GetPosition();
					handles[j] = screen.AddWithC("AppData/Images/white.png", 145, 145, Physics::ExX(position.x), Physics::ExY(position.y), 0.0);
					// printfDx(TEXT("handle1 %d\n"), handles[j]);
				}
			}
		}
		else
		{
			for (int j = 0; j < body_num; j++)
			{
				position = body[j]->GetPosition();
				screen.Move(handles[j], Physics::ExX(position.x), Physics::ExY(position.y), 0.0);
				// screen.AddCircle(20, Physics::ExX(position.x), Physics::ExY(position.y), GetColor(100, 100, 100));
				// printfDx(TEXT("handle %d\n"), handles[j]);
			}
		}

		init = 0;

		screen.Display();

		for (;;)
		{
			ProcessMessage();
			if ((double)clock() - time > 1000.0 * (1.0 / 60.0))
				break;
		}
	}
	// printfDx(TEXT("graph num1 %d\n"), screen.GetGraphNum());
	for (int i = 0; i < body_num; i++)
	{
		screen.Remove(handles[i]);
	}
	// printfDx(TEXT("graph num2 %d\n"), screen.GetGraphNum());
}

void Animation::StoneDrop2(int board_old[], int time)
{
	// Define the gravity vector.
	b2Vec2 gravity(0.0, -9.8 * scale_change);

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(gravity);

	//-------------------------------------------------------------------------------------------

	b2Body* groundBody = Physics::CreateStaticBox(50.0f * scale_change, 10.0f * scale_change,
		0.0f * scale_change, -10.01f * scale_change, &world);

	//-------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------

	b2Body* body[64];

	float x_coner = 343.0 * (1.0 / DPM) * (1.0 / scale_change),
		y_coner = (720.0 - 63.0) * (1.0 / DPM) * (1.0 / scale_change);

	float interval = 85.0 * (1.0 / DPM) * (1.0 / scale_change);

	int handles[64];

	int ct = -1;
	for (int i = 0; i < 64; i++)
	{
		if (board_old[i] == 0)
			continue;

		int x = i % 8, y = i / 8;

		ct++;

		body[ct] = Physics::CreateCircle(
			1.7 * (1.0 / 100.0) * scale_change,
			(x_coner + interval * x + Utility::RandBetweenF(-0.1 * (1.0 / 100.0), 0.1 * (1.0 / 100.0))) * scale_change,
			(y_coner - interval * y + Utility::RandBetweenF(-0.1 * (1.0 / 100.0), 0.1 * (1.0 / 100.0))) * scale_change,
			&world);

		if (board_old[i] == WHITE)
		{
			handles[ct] = screen.AddWithC("AppData/Images/white.png", 145, 145, 0, 0, 0.0);
		}
		else
		{
			handles[ct] = screen.AddWithC("AppData/Images/black.png", 145, 145, 0, 0, 0.0);
		}
	}

	// デバッグ用
	int body_num = ct + 1;
	printf("body %d\n", body_num);

	//-------------------------------------------------------------------------------------------

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 10;
	int32 positionIterations = 6;

	int init = 1;

	// This is our little game loop.
	for (int32 i = 0; i < 60.0 * ((float)time / 1000.0); i++)
	{
		double time = (double)clock();

		// 一定時間たったら地面を無効
		if (60.0 * 1.2 < i)
		{
			groundBody->SetActive(FALSE);
		}

		ProcessMessage();

		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world.Step(timeStep, velocityIterations, positionIterations);

		// Now print the position and angle of the body.
		b2Vec2 position;

		for (int j = 0; j < body_num; j++)
		{
			position = body[j]->GetPosition();
			screen.Move(handles[j], Physics::ExX(position.x), Physics::ExY(position.y), 0.0);
		}

		screen.Display();

		if (init)
		{
			PlayerInput::WaitTimer(100);
		}

		for (;;)
		{
			ProcessMessage();
			if ((double)clock() - time > 1000.0 * (1.0 / 60.0))
				break;
		}
		init = 0;
	}

	// printfDx(TEXT("graph num1 %d\n"), screen.GetGraphNum());
	for (int i = 0; i < body_num; i++)
	{
		screen.Remove(handles[i]);
	}
	// printfDx(TEXT("graph num2 %d\n"), screen.GetGraphNum());
}
