#include <iostream>
#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include "Renderer/Model.h"
#include <vector>

using namespace std;

class Star
{
public:
	Star(const kiko::Vector2& pos, const kiko::Vector2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update(int width, int height)
	{
		m_pos += m_vel;
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
	}

	void Draw(kiko::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kiko::vec2 m_pos;
	kiko::vec2 m_vel;
};


int main(int argc, char* argv[])
{
	kiko::seedRandom((unsigned int)time(nullptr));

	kiko::Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("CSC196", 800, 600);

	std::vector<kiko::vec2> points{ { -50, 0 }, { 50, 25 }, { 0, -25 }, { -50, 0 } };
	kiko::Model model(points);

	kiko::vec2 v{5, 5};
	v.Normalize();

	vector<Star> stars;
	for (int i = 0; i < 5000; i++)
	{
		kiko::Vector2 pos(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()));
		kiko::Vector2 vel(kiko::randomf(1, 4), 0.0f);

		stars.push_back(Star(pos, vel));
	}

while (true)
{
	renderer.SetColor(0, 0, 0, 0);
	renderer.BeginFrame();
	// Draw
	kiko::Vector2 vel(1.0f, 0.3f);

	//for (auto& star : stars)
	//{
	//	star.Update(renderer.GetWidth(), renderer.GetHeight());

	//	if (star.m_pos.x >= renderer.GetWidth()) star.m_pos.x = 0;
	//	if (star.m_pos.y >= renderer.GetHeight()) star.m_pos.y = 0;

	renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
	//	renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
	//}
	
	model.Draw(renderer, {400, 300}, 2.0f);


	renderer.EndFrame();
}
}