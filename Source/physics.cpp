#include <Box2D/Box2D.h>
#include "variables.h"
#include "funcs.h"

b2Body* Physics::CreateStaticBox(float xl, float yl, float xp, float yp, b2World* world)
{
	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(xp, yp);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(xl, yl);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	return groundBody;
}

b2Body* Physics::CreateCircle(float r, float x, float y, b2World* world)
{
	// b2body型以外は全て物体の設定情報を生成し、それを保持するためのオブジェクト。

	// Define the dynamic body. We set its position and call the body factory.
	// b2BodyDef型は物体の初期位置、タイプなどを設定するためのもの。
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);

	// b2Body型は物体そのもの。
	b2Body* body = world->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	// フィクスチャーの設定に使われるb2FixtureDef型オブジェクトに渡すためのもので、物体の形の情報が入る。

	b2CircleShape dynamicCircle;
	dynamicCircle.m_radius = r;

	// Define the dynamic body fixture.
	// 物体のフィクスチャーを設定するためのもの。
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicCircle;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1000.0f;

	// Override the default friction.
	fixtureDef.friction = 0.15f;

	fixtureDef.restitution = 0.4f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	return body;
}

int Physics::ExX(float x)
{
	return x * DPM;
}

int Physics::ExY(float y)
{
	return (int)(720.0 - y * DPM);
}