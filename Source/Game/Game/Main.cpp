#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"

#include <iostream>
#include <vector>
#include <thread>
#include <memory>

using namespace std;

class Star
{
public:
	Star(const kiko::Vector2& pos, const kiko::Vector2& vel) :
		m_pos{ pos },
		m_vel{ vel } {}

	void Update(int width, int height)
	{
		m_pos += m_vel * kiko::g_time.GetDeltaTime();
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

	{
	//std::unique_ptr<int> up = std::make_unique<int>(10);
	}

	kiko::g_memoryTracker.DisplayInfo();

	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	// engine initialization
	//kiko::Renderer renderer;
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);
	kiko::g_inputSystem.Initialize();
	kiko::g_audioSystem.Initialize();
	kiko::g_audioSystem.AddAudio("Laser_Shoot", "Laser_Shoot.wav");

	kiko::Model model;
	model.Load("Star.txt");
	kiko::vec2 position{ 400, 300 };

	float speed = 100;
	constexpr float turnrate = kiko::DegreesToRadians(180);

	kiko::Scene scene;
	unique_ptr<Player> player = std::make_unique<Player>(200.0f, kiko::Pi, kiko::Transform{ { 400, 300 }, 0, 6 }, model);
	scene.Add(std::move(player));


	for (int i = 0; i < 10; i++)
	{
		unique_ptr<Enemy> enemy = std::make_unique<Enemy>(300.0f, kiko::Pi, kiko::Transform{ {kiko::randomf(kiko::g_renderer.GetWidth()), kiko::randomf(kiko::g_renderer.GetHeight())}, kiko::randomf(kiko::TwoPi), 3}, model);
		scene.Add(std::move(enemy));
	}

	vector<Star> stars;
	for (int i = 0; i < 5000; i++)
	{
		kiko::Vector2 pos(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight()));
		kiko::Vector2 vel(kiko::randomf(100, 200), 0.0f);

		stars.push_back(Star(pos, vel));
	}
	

	

	kiko::Transform transform{ { 400, 300 }, 0, 3};

	// Main Game Loop
	bool quit = false;
	while (!quit)
	{
		// Update engine
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		//cout << "Current Mouse Position: " << kiko::g_inputSystem.GetMousePosition().x << " " << kiko::g_inputSystem.GetMousePosition().y << endl;
		//if (inputSystem.GetMouseButtonDown(0)) { cout << "Left Mouse Pressed" << endl; }
		//if (inputSystem.GetMouseButtonDown(1)) { cout << "Middle Mouse Pressed" << endl; }
		//if (inputSystem.GetMouseButtonDown(2)) { cout << "Right Mouse Pressed" << endl; }

		//position += direction * speed * kiko::g_time.GetDeltaTime();;

		// Update game
		scene.Update(kiko::g_time.GetDeltaTime());

		// Update Audio
		kiko::g_audioSystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			kiko::g_audioSystem.PlayOneShot("Laser_Shoot");
		}

		// Draw game
		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();

		for (auto& star : stars)
		{
			star.Update(kiko::g_renderer.GetWidth(), kiko::g_renderer.GetHeight());

			if (star.m_pos.x >= kiko::g_renderer.GetWidth()) star.m_pos.x = 0;
			if (star.m_pos.y >= kiko::g_renderer.GetHeight()) star.m_pos.y = 0;

			kiko::g_renderer.SetColor(255, 255, 255, 255);
			kiko::g_renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}
	
		kiko::g_renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);

		scene.Draw(kiko::g_renderer);

		kiko::g_renderer.EndFrame();

	}

	scene.RemoveAll();
	kiko::g_memoryTracker.DisplayInfo();

	return 0;
}