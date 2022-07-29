#pragma once
#include "../Math/Transform.h"

namespace neu
{
	class GameObject
	{
	public:
		GameObject() = default;
		GameObject(Transform& transform) : m_Transform{ transform } {}

		virtual void Update() = 0;

		
		Transform m_Transform;
	};
}