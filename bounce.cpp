#include "test.h"
#include <fstream>
#include "settings.h"

class FistTest : public Test
{
public:
	b2Body* groundBody;
	b2Body* groundBody2;
	std::ofstream fileout;
	float   totalTime;
public:

	FistTest()
	{
		totalTime = 0;
		std::ifstream filein;
		filein.open("E:/box2d-2.4.1/data/datos.txt");
		float gravedad;
		float aire;
		float posx;
		float posy;
		float rad;
		float restituticion;
		filein >> gravedad >> aire >> posx >> posy >> rad >> restituticion;
		b2Vec2 gravity(0.0f, gravedad);
		m_world->SetGravity(gravity);
		b2BodyDef groundBodyDef;
		b2BodyDef groundBodyDef2;
		groundBodyDef.type = b2_dynamicBody;
		float forceMagnitude = aire;
		b2Vec2 opposingForce(-forceMagnitude, 0.0f);
		groundBodyDef.position.Set(posx, posy);
		groundBodyDef2.position.Set(0.0f, 0.0f);
		groundBody = m_world->CreateBody(&groundBodyDef);
		groundBody2 = m_world->CreateBody(&groundBodyDef2);
		b2PolygonShape barra;
		b2CircleShape circle;
		barra.SetAsBox(45.0f, 15.0f);
		circle.m_radius = rad;
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circle;
		fixtureDef.density = 1.0f;
		fixtureDef.restitution = restituticion;
		groundBody->CreateFixture(&fixtureDef);
		groundBody2->CreateFixture(&barra, 1.0f);
		filein.close();

		fileout.open("E:/box2d-2.4.1/data/salida.txt");
	}

	~FistTest() {
		fileout.close();
	}

	void Step(Settings& settings) override
	{
		float timeStep = settings.m_hertz > 0.0f ? 1.0f / settings.m_hertz : float(0.0f);
		totalTime = totalTime + timeStep;
		float forceMagnitude = 10.0f;
		b2Vec2 opposingForce(-forceMagnitude, 0.0f);
		groundBody->ApplyForce(opposingForce, groundBody->GetWorldCenter(), true);
		b2Vec2 position = groundBody->GetPosition();
		fileout << totalTime << " Posición en x: " << position.x << ", Posición en y: " << position.y << std::endl;
		Test::Step(settings);
	}

	static Test* Create()
	{
		return new FistTest;
	}


};

static int testIndex = RegisterTest("Forces", "sphere", FistTest::Create);
