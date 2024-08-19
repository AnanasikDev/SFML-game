#include "Gameobject.h"

namespace aengine {
	Gameobject::Gameobject(std::string name) {
		this->name = name;
		this->position = Vectorf(0, 0);
		//Init();
	}

	void Gameobject::Render() {
		if (renderer != nullptr)
			renderer->Render();
	}

	void Gameobject::Update() {
		if (renderer != nullptr)
			renderer->Update();
	}
}