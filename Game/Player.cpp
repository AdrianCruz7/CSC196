#include "Player.h"
#include "Bullet.h"
#include "Source/Engine.h"
#include "Powerup.h"

void Player::Update()
{
	//rotation
	if (neu::g_inputSystem.GetKeyState(neu::key_left) == neu::InputSystem::State::Held)
	{
		m_Transform.rotation -= math::Pi * neu::g_time.deltaTime;
	}

	if (neu::g_inputSystem.GetKeyState(neu::key_right) == neu::InputSystem::State::Held)
	{
		m_Transform.rotation += math::Pi * neu::g_time.deltaTime;
	}

	//set thrust speed 
	m_speed = 0;
	if (neu::g_inputSystem.GetKeyState(neu::key_up) == neu::InputSystem::State::Held)
	{
		m_speed = m_maxSpeed;
	}
	
	//move in direction
	neu::Vector2 direction{ 1, 0 };
	direction = neu::Vector2::Rotate(direction, m_Transform.rotation);
	neu::Vector2 force = direction * m_speed * neu::g_time.deltaTime;
	
	//apply force to velocity
	m_velocity += force;

	//apply drag
	m_damping = 5;
	m_velocity *= 1.0f / (1.0f + m_damping * neu::g_time.deltaTime);

	//move
	m_Transform.position += m_velocity * neu::g_time.deltaTime;
	
	//fire bullet
	if (neu::g_inputSystem.GetKeyState(neu::key_space) == neu::InputSystem::State::Held)
	{
		//fire
		if (m_firerate >= m_cooldown)
		{
			m_firerate = 0;
			neu::g_audioSystem.PlayAudio("laser");
			neu::Transform transform = m_Transform;
			std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(neu::Model("Bullet.txt"), transform, 10);
			bullet->SetTag("player");
			m_scene->Add(std::move(bullet));
		} 
		else if (m_firerate < m_cooldown)
		{
			m_firerate += 10;
		}

	}

	if (m_Transform.position.x > neu::g_renderer.GetWidth()) m_Transform.position.x = 0;
	if (m_Transform.position.x < 0) m_Transform.position.x = neu::g_renderer.GetWidth();

	if (m_Transform.position.y > neu::g_renderer.GetWidth()) m_Transform.position.y = 0;
	if (m_Transform.position.y < 0) m_Transform.position.y = neu::g_renderer.GetWidth();
}

void Player::OnCollision(Actor* other)
{
	if (dynamic_cast<Bullet*>(other) && other->GetTag() == "enemy")
	{
		m_health -= dynamic_cast<Bullet*>(other)->GetDamage();
		
		if (m_health <= 0) m_destroy = true;
	}

	if (dynamic_cast<Powerup*>(other))
	{
		m_cooldown -= 10;
		other->m_destroy = true;
	}
}