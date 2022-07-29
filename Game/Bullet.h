#pragma once
#include "Framework/Actor.h"

class Bullet : public neu::Actor
{
public:
	Bullet() = default;
	Bullet(const neu::Model& model, const neu::Transform& transform, float damage = 1) :
		Actor{ model, transform }, 
		m_damage{ damage }  {}

	void Update() override;
	void OnCollision(Actor* other) override;

	float GetDamage() { return m_damage; }

private:
	float m_damage = 0;
	float m_speed = 300;
	float m_lifespan = 10;	
};