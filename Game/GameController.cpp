#include "Core/Engine.h"
#include "Blob.h"
#include "Player.h"
#include "Bomb.h"
#include "GameController.h"

using namespace aengine;

namespace agame {
	float GameController::secondsLeft = 30.f;
	TextRenderer* GameController::textRenderer = nullptr;

	Player* GameController::player = nullptr;

	std::vector<Blob*> GameController::blobs;
	std::vector<Gameobject*> GameController::walls;
	std::vector<Bomb*> GameController::hookpoints;

	std::array<float, 3> GameController::levelThresholds { 0, 9, 20 }; // TODO: increase levels intervals
	int GameController::level = 0;

	Action<> GameController::onLevelUpEvent;

	void GameController::init() {
		onLevelUpEvent.Subscribe([]() {

			std::cout << "Level up! current level is " << level << std::endl;

			if (level == 1) beginLevel1();
			else if (level == 2) beginLevel2();
			else if (level == 3) beginLevel3();

			});

		beginLevel0();
	}

	float GameController::getSecondsLeft() {
		return GameController::secondsLeft;
	}

	void GameController::setSecondsLeft(float val) {
		
		secondsLeft = val;
		if (textRenderer != nullptr) textRenderer->text.setString(std::to_string(secondsLeft));
	}

	void GameController::addSecondsLeft(float delta) {
		setSecondsLeft(secondsLeft + delta);
	}

	void GameController::markBlobHit(Gameobject* obj) {
		obj->setPosition(player->getPosition() + Vectorf(
			Random::getFloat(-200, 200),
			Random::getFloat(-200, 200)
		));
	}

	float GameController::getDifficultyAt(float t) {
		return powf(t, 0.9f);
	}

	float GameController::getCurrentDifficulty() {
		return getDifficultyAt(Time::getTime());
	}

	int GameController::getCurrentLevel() {
		return level;
	}

	void GameController::beginLevel0() {
		for (int i = 0; i < 7; i++) {
			Blob* blob = Gameobject::instantiate<Blob>("blob" + std::to_string(i));
			blobs.push_back(blob);
			blob->tag = "blob";
		}
	}

	void GameController::beginLevel1() {
		// walls
		for (int i = 0; i < 10; i++) {
			auto pos = player->getPosition() + 
				Vectorf(
					pixelate(Random::getFloat(-800, 800), 60),
					pixelate(Random::getFloat(-800, 800), 60));
			Gameobject* wall = Gameobject::instantiate("wall" + std::to_string(i));
			wall->tag = "wall";
			RectCollider* col = wall->setCollider(std::make_unique<RectCollider>(wall, Vectorf(60, 60)));
			col->stickiness = 8;
			SpriteRenderer* rend = wall->setRenderer(std::make_unique<SpriteRenderer>(wall, "resources/wall.png"));
			rend->setRelativeOrigin(Vectorf::half);
			rend->sprite->setScale(Vectorf(3, 3).getsf());
			
			wall->setPosition(pos);
			rend->setRelativeOrigin(Vectorf::half);
		}
	}

	void GameController::beginLevel2() {
		// hook points

		for (int i = 0; i < 10; i++) {
			Gameobject* hookpoint = Gameobject::instantiate("hook_" + std::to_string(i));
			ShapeRenderer* rend = hookpoint->setRenderer(std::make_unique<ShapeRenderer>(hookpoint, std::make_unique<sf::CircleShape>(10)));
			rend->getShapeAs<sf::CircleShape>()->setFillColor(sf::Color::Blue);
			rend->setRelativeOrigin(Vectorf::half);
		}
	}

	void GameController::beginLevel3() {
		// bombs
	}


	void GameController::update() {
		addSecondsLeft(-Time::getDeltaTime());

		float difficulty = getCurrentDifficulty();

		if (level != maxLevel && difficulty > levelThresholds[level + 1]) {
			level++;
			onLevelUpEvent.Invoke();
		}
	}
}
