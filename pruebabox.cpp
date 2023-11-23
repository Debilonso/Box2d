#include "test.h"

class FistTest : public Test
{
public:

	FistTest()
	{
		b2Vec2 gravity(0.0f, -9.81f);	
		m_world->SetGravity(gravity);
		b2BodyDef groundBodyDef;
		b2BodyDef groundBodyDef2;
		groundBodyDef.type = b2_dynamicBody;
		groundBodyDef.position.Set(0.0f, 40.0f);
		groundBodyDef2.position.Set(0.0f, 0.0f);
		b2Body* groundBody = m_world->CreateBody(&groundBodyDef);
		b2Body* groundBody2 = m_world->CreateBody(&groundBodyDef2);
		b2PolygonShape barra;
		b2CircleShape circle;
		barra.SetAsBox(10.0f,1.0f);
		circle.m_radius = 2.5f;
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circle;
		fixtureDef.density = 1.0f;
		fixtureDef.restitution = 0.9f;
		groundBody->CreateFixture(&fixtureDef);
		groundBody2->CreateFixture(&barra, 1.0f);
	

		
	}

	static Test* Create()
	{
		return new FistTest;
	}
};

static int testIndex = RegisterTest("Forces", "sphere", FistTest::Create);
