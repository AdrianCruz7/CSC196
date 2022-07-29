#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Source/Engine.h"


void Bullet::Update()
{
	m_lifespan -= neu::g_time.deltaTime;
	if (m_lifespan <= 0) { m_destroy = true; };

	//calculate velocity
	neu::Vector2 direction{ 1, 0 };
	direction = neu::Vector2::Rotate(direction, m_Transform.rotation);
	neu::Vector2 velocity = direction * m_speed * neu::g_time.deltaTime;

	//move
	m_Transform.position += velocity;

	if (m_Transform.position.x > neu::g_renderer.GetWidth()) m_Transform.position.x = 0;
	if (m_Transform.position.x < 0) m_Transform.position.x = neu::g_renderer.GetWidth();
	if (m_Transform.position.y > neu::g_renderer.GetWidth()) m_Transform.position.y = 0;
	if (m_Transform.position.y < 0) m_Transform.position.y = neu::g_renderer.GetWidth();
}

void Bullet::OnCollision(Actor* other)
{
	if (dynamic_cast<Player*>(other) && m_tag != "player")
	{
		m_destroy = true;
	}
	
	if (dynamic_cast<Enemy*>(other) && m_tag != "enemy")
	{
		m_destroy = true;
	}
}

