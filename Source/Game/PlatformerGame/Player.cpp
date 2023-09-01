#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include"Renderer/ModelManager.h"
#include "Audio/AudioSystem.h"
#include "Core/Math/MathUtils.h"
#include "Framework/Components/PhysicsComponent.h"


#include "Framework/Framework.h"

namespace kiko 
{
	CLASS_DEFINITION(Player);

		bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<kiko::PhysicsComponent>();
		m_SpriteRenderComponent = GetComponent<kiko::SpriteAnimRenderComponent>();
	
		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);

		bool onGround = (groundCount > 0);
		vec2 velocity = m_physicsComponent->m_velocity;

		//ovement
		float dir = 0;
		if (kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;
		//transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

		if (dir)
		{
			velocity.x += speed * dir * ((onGround) ? 1 : 0.2f) * dt;
			velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
			m_physicsComponent->SetVelocity(velocity);

			//m_physicsComponent->ApplyForce(forward * speed * dir * ((onGround) ? 1 : 0.2f));
		}

		if (onGround && kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_InputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
			kiko::vec2 up = kiko::vec2{ 0,-1 };
			m_physicsComponent->SetVelocity(velocity + (up * jump));
		}

		m_physicsComponent->SetGravityScale((velocity.y > 0) ? 3 : 2);


		// animation
		//check if movin'
		if (std::fabs(velocity.x) > 0.2f)
		{
			if (dir != 0) m_SpriteRenderComponent->flipH = (dir < 0);
			m_SpriteRenderComponent->SetSequence("run");
		}
		else
		{
			m_SpriteRenderComponent->SetSequence("idle");
		}

	}
	void Player::OnCollissionEnter(Actor* other)
	{
		if (other->tag == "Ground") groundCount++;
		
	}

	void Player::OnCollissionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--;

	}

	void Player::Read(const json_t& value) {
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, maxSpeed);
		READ_DATA(value, jump);
	}
}