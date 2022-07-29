#pragma once
#include "GameObject.h"
//#include "Scene.h"
#include "../Renderer/Model.h"

namespace neu
{
	class Scene;
	class Actor : public GameObject
	{
	public:
		Actor() = default;
		Actor(Model model, Transform transform) : 
			GameObject { transform },
			m_model{ model } {}
		
		virtual void Update() override {}
		virtual void Draw(Renderer& renderer);

		virtual void OnCollision(Actor* other) {}
		float GetRadius() { return m_model.GetRadius() * m_Transform.scale; }
		
		void SetTag(std::string tag) { m_tag = tag; }
		std::string GetTag() { return m_tag; }

		friend class scene;
		
	public:
		bool m_destroy = false;
		Scene* m_scene = nullptr;

	protected:
		std::string m_tag;

		Vector2 m_velocity;
		float m_damping = 1;

		Model m_model;
	};
}