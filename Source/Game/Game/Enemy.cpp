#include "Enemy.h"
#include "Player.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Weapon.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		kiko::Vector2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.Angle() + kiko::HalfPi;
		
	}

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap((float)m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap((float)m_transform.position.y, (float)kiko::g_renderer.GetHeight());

	if (m_fireRate != -1.0f)
	{
		m_fireTime -= dt;
		if (m_fireTime <= 0)
		{
			m_fireTime = m_fireRate;
			kiko::Transform transform{ m_transform.position, m_transform.rotation, 1};
			std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, m_transform, m_model);
			weapon->m_tag = "EnemyBullet";
			m_scene->Add(std::move(weapon));
		}
	}
}

void Enemy::OnCollision(Actor* other)
{

	if (other->m_tag == "Player")
	{
		m_health -= 10;
		if (m_health <= 0) m_destroyed = true;
		
	}
}
