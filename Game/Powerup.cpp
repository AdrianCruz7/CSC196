#include "Powerup.h"
#include "Player.h"
#include "Source/Engine.h"

void Powerup::Update()
{
	m_lifespan -= neu::g_time.deltaTime;
	if (m_lifespan <= 0) { m_destroy = true; };
}