#include "Actor.h"

namespace neu
{
	void neu::Actor::Draw(Renderer& renderer)
	{
		m_model.Draw(renderer, m_Transform.position, m_Transform.rotation, m_Transform.scale);
	}



}
