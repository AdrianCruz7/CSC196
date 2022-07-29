#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "Powerup.h"
#include "Source/Engine.h"
#include "Framework/Scene.h"

void Enemy::Initialize()
{
	m_fireTime = neu::randomf( 0, 6 );
	m_speed = neu::randomf(20, 150);
}

void Enemy::Update()
{
	//fire weapon
	m_fireTime -= neu::g_time.deltaTime;
	if (m_fireTime < 0)
	{
		m_fireTime = neu::randomf(2, 6);
		neu::Transform transform = m_Transform;
		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(neu::Model("Bullet.txt"), transform, 2);
		bullet->SetTag("enemy");
		m_scene->Add(std::move(bullet));
	}

	//set rotation towards player
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		neu::Vector2 direction = player->m_Transform.position - m_Transform.position;
		m_Transform.rotation = direction.GetAngle();
	}

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

void Enemy::OnCollision(Actor* other)
{
	if (dynamic_cast<Bullet*>(other) && other->GetTag() == "player")
	{
		m_health -= dynamic_cast<Bullet*>(other)->GetDamage();

		if (m_health <= 0)
		{
			neu::Transform transform = m_Transform;
			transform.position.x = neu::randomf(200);
			transform.position.y = neu::randomf(100);
			transform.rotation = neu::randomf(math::TwoPi);
			std::unique_ptr<Powerup> powerUp = std::make_unique<Powerup>(neu::Model("Powerup.txt"), transform);
			m_scene->Add(std::move(powerUp));

			neu::g_audioSystem.PlayAudio("explosion");
			m_scene->GetGame()->AddPoints(100);
			m_destroy = true;	
		}
	}
}
 