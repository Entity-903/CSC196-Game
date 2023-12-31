#pragma once
#include "Framework/Actor.h"
#include "SpaceGame.h"
#include <Framework/Game.h>

class Enemy : public kiko::Actor
{
public:
	Enemy(float speed, float turnRate, const kiko::Transform& transform, std::shared_ptr<kiko::Model> model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_fireTime = 2.0f;
		m_fireRate = m_fireTime;
	}
	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_fireTime = 0;
	float m_fireRate = 0;

	// int testDifficulty = kiko::Game::GetScore();
	int m_enemyDifficulty = 1; // (testDifficulty != (int)nullptr && (testDifficulty % 1000) != 0) ? testDifficulty % 1000 : 1; // % 1000;
	float m_health = 20.0f * m_enemyDifficulty;

};