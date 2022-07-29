#pragma once
#include "Framework/Actor.h"

class Player : public neu::Actor
{
public:
	Player() = default;
	Player(const neu::Model& model, const neu::Transform& transform) :
		Actor{ model, transform } {}

	void Update() override;
	void OnCollision(Actor* other) override;

	friend class Powerup;
	friend class SpaceShooter;

private:
	float m_health = 9.0f;
	float m_firerate = 0.0f;
	float m_cooldown = 150;

	float m_speed = 0;
	float m_maxSpeed = 1000;
};