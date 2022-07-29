#pragma once
#include "Framework/Game.h"


namespace neu
{
	class Font;
	class Text;
}

class SpaceShooter : public neu::Game
{

public:
	SpaceShooter() = default;
	~SpaceShooter() = default;

	// Inherited via Game
	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update() override;
	virtual void Draw(neu::Renderer& renderer) override;

private:
	float m_spawnTimer = 7;
	float m_ramp = 0;
	std::unique_ptr<neu::Font> m_font;
	std::unique_ptr<neu::Text> m_titleText;
	std::unique_ptr<neu::Text> m_scoreText;

};