#include "Gameobject.h"
#include "Renderer.h"
#include "Collider.h"
#include "Rigidbody.h"
#include <iostream>
#include "Game.h"
#include "List.h"

namespace aengine {
	Gameobject::Gameobject(std::string name) {
		this->name = name;
		this->position = Vectorf(0, 0);
	}

	void Gameobject::Render() {
		if (renderer != nullptr)
			renderer->Render();
	}

	void Gameobject::Update() {

		// if rigidbody is applied, it takes control over GO's position
		if (rigidbody != nullptr) {
			this->position = rigidbody->getPosition();
		}
		
		if (collider != nullptr) {
			collider->Update(this->position);
		}
		
		if (renderer != nullptr) {
			renderer->Update(this->position);
		}
	}

	void Gameobject::Init() {
		aengine::Game::instance->gameobjects.push_back(this);
	}

	Gameobject::~Gameobject() {
		if (renderer != nullptr) delete renderer;
		if (collider != nullptr) delete collider;
		if (rigidbody != nullptr) delete rigidbody;

		List::Remove<Gameobject*>(aengine::Game::instance->gameobjects, this);
	}

	void Gameobject::SetScale(float scale) {
		if (renderer != nullptr) renderer->SetScale(scale);
		if (collider != nullptr) collider->SetScale(scale);
	}
}