#include "Engine.h"

namespace aengine {

	Camera::Camera(const std::string& name) {
		this->name = name;
		cornerPosition = Vectorf();
		scene = context();
		size = Vectorf::otherFromsf<unsigned int, float>(window()->getWindow()->getSize());

		SceneManager::onSceneChanged.Subscribe([this](Scene* newScene) { this->scene = newScene; }); // no need for unsubscription because it will be deleted at the end
		scene->addCamera(this);
	}

	void Camera::translate(Vectorf delta) {
		cornerPosition += delta;
		for (int i = 0; i < scene->gameobjects.size(); i++) {
			
			// if attached to camera leave it where it is
			if (scene->gameobjects[i]->isAttachedToCamera) {
				scene->gameobjects[i]->screenPosition = scene->gameobjects[i]->getPosition();
			}

			else
			{
				scene->gameobjects[i]->screenPosition = scene->gameobjects[i]->getPosition() - cornerPosition;// (position - Vectorf(size.x / 2., size.y / 2.));
			}
		}
	}

	Vectorf Camera::worldToScreen(Vectorf worldpos) const {
		return worldpos - cornerPosition;
	}

	Vectorf Camera::screenToWorld(Vectorf screenpos) const {
		return cornerPosition + screenpos;
	}

	void Camera::setPosition(Vectorf newPos) {
		translate(newPos - cornerPosition);
	}
	
	Vectorf Camera::getPosition() const {
		return cornerPosition;
	}

	std::string Camera::getName() const {
		return name;
	}
}
