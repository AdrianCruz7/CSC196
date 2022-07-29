#pragma once
#include "Framework/Actor.h"

class Enemy : public neu::Actor
{
public:
	Enemy() = default;
	Enemy(const neu::Model& model, const neu::Transform& transform, float health = 1) :
		Actor{ model, transform },
		m_health{ health }
	{
		Initialize();
	}

	void Initialize();

	void Update() override;
	void OnCollision(Actor* other) override;

private:
	float m_health = 1;

	float m_speed = 50;
	float m_fireTime = 0;
};