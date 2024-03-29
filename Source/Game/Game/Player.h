#pragma once
#include "Framework/Actor.h"


namespace kiko {
	class Player : public kiko::Actor
	{
	public:

		CLASS_DECLARATION(Player)

			Player() = default;
		Player(float speed, float turnRate, const kiko::Transform& transform) :
			Actor{ transform },
			speed{ speed },
			turnRate{ turnRate }
		{}

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollissionEnter(Actor* other) override;



	private:
		float speed = 0;
		float turnRate = 0;
		int m_health = 100;
		float jump = 0;
		int groundCount = 0;

		class PhysicsComponent* m_physicsComponent = nullptr;
		class SpriteAnimComponent* m_SpriteRenderComponent = nullptr;
	};
}