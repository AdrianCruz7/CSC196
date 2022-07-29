#pragma once
#include "Framework/Actor.h"

class Powerup : public neu::Actor
{
public:
	Powerup() = default;
	Powerup(const neu::Model& model, const neu::Transform& transform) :
		Actor{ model, transform } {}

	void Update() override;

private:
	float m_lifespan = 500;
};