#include "SpaceShooter.h"
#include "Player.h"
#include "Enemy.h"
#include "Source\Engine.h"
#include <memory>



void SpaceShooter::Initialize()
{

	m_scene = std::make_unique<neu::Scene>(this); 

	//create assets
	neu::g_audioSystem.AddAudio("laser", "laser.wav");
	neu::g_audioSystem.AddAudio("explosion", "explosion.wav");
	neu::g_audioSystem.AddAudio("music", "music.wav");

	neu::g_audioSystem.PlayAudio("music");

	m_font = std::make_unique<neu::Font>("fonts/arcadeclassic.ttf", 24);
	//m_titleText = std::make_unique<neu::Text>(m_font.get());
	//m_titleText->Create(neu::g_renderer, "Asteroidz", { 0,255,255,255 });
	m_scoreText = std::make_unique<neu::Text>(m_font.get());
	m_scoreText->Create(neu::g_renderer, "000000", { 255,255,255,255 });

	//** CREATE ACTOR **
	//transform
	neu::Transform transform;
	transform.position = neu::Vector2{ 400,300 };
	transform.rotation = 0;
	transform.scale = 3;

	std::unique_ptr<Player> player = std::make_unique<Player>(neu::Model("Player.txt"), transform);
	m_scene->Add(std::move(player));

	//model
	for (int i = 0; i < 1; i++)
	{
		transform.position.x = neu::randomf(200);
		transform.position.y = neu::randomf(100);
		transform.rotation = neu::randomf(math::TwoPi);
		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(neu::Model("Enemy.txt"), transform, 1);
		m_scene->Add(std::move(enemy));
	}
}

void SpaceShooter::Shutdown()
{
}

void SpaceShooter::Update()
{
	//spawn enemies
	m_spawnTimer -= neu::g_time.deltaTime;
	if (m_spawnTimer <= 0)
	{
		m_ramp += 0.5;
		m_spawnTimer = 7 - m_ramp;

		neu::Transform transform;

		transform.position.x = neu::randomf(200);
		transform.position.y = neu::randomf(100);
		transform.rotation = neu::randomf(math::TwoPi);
		transform.scale = 3;
		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(neu::Model("Enemy.txt"), transform, 1);
		m_scene->Add(std::move(enemy));

		if (m_ramp >= 5.5)
		{
			m_ramp = 5;
		}
	}

	//update game objects
	m_scene->Update();

	//update score text
	m_scoreText->Create(neu::g_renderer, std::to_string(m_score), { 255,255,255,255 });
	
}

void SpaceShooter::Draw(neu::Renderer& renderer)
{

	//render game objects
	m_scene->Draw(renderer);

	//m_titleText->Draw(renderer, { 400,300 });
	m_scoreText->Draw(renderer, { 40,30 });
}
