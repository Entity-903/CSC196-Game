#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

void Player::Update(float dt)
{
	float rotate = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * kiko::TwoPi * kiko::g_time.GetDeltaTime();

	float thrust = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 5;

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * 0.25 * thrust * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap((float)m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap((float)m_transform.position.y, (float)kiko::g_renderer.GetHeight());

}