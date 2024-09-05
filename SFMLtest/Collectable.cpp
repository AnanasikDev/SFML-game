#include "Collectable.h"
#include "Gameobject.h"
#include "Renderer.h"
#include "Game.h"
#include "Collider.h"
#include "Rigidbody.h"
#include <iostream>

namespace agame {
	Collectable::Collectable(std::string name) {
		this->name = name;
	}

	void Collectable::Init() {
		Gameobject::Init();
		this->renderer = new aengine::ShapeRenderer(this, aengine::Game::instance->getWindow());

		aengine::ShapeRenderer* sp = static_cast<aengine::ShapeRenderer*>(this->renderer);

		sf::CircleShape* circle = new sf::CircleShape();

		sp->shape = circle;

		SetPosition(0, 0);
		circle->setFillColor(sf::Color(250, 220, 20));
		circle->setRadius(15);
		sp->SetOrigin(aengine::Vectorf(15, 15));

		aengine::CircleCollider* collider 
			= new aengine::CircleCollider(this);
		collider->radius = 15;

		this->collider = collider;

		this->rigidbody = new aengine::Rigidbody(this);
		//this->rigidbody->
	}

	void Collectable::Render() {
		Gameobject::Render();
	}

	void Collectable::Update() {
		Gameobject::Update();
		position += aengine::Vectorf(0, 1.f);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (this->collider->IsPointInside(aengine::Game::instance->worldPos)) {
				collected++;
				this->SetPosition(aengine::Vectorf(std::rand() % 500 + 50, 0));
			}
		}
	}

	unsigned int Collectable::collected = 0;
}
