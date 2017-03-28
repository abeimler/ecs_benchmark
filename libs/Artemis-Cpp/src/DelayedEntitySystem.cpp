#include "Artemis/DelayedEntitySystem.h"
#include "Artemis/World.h"

namespace artemis {

	DelayedEntitySystem::DelayedEntitySystem() {
		acc = 0;
		delay = 0;
		running = false;
		autoRepeat = false;
	}

	bool DelayedEntitySystem::checkProcessing() {
		if(running) {
			acc += world->getDelta();

			if(acc >= delay) {
				return true;
			}
		}

		return false;
	}

	float DelayedEntitySystem::getInitialTimeDelay() {
		return delay;
	}

	float DelayedEntitySystem::getRemainingTime() {
		if(running) {
			return delay - acc;
		}

		return 0;
	}

	bool DelayedEntitySystem::isRunning() {
		return running;
	}

	void DelayedEntitySystem::setAutoRepeat(bool repeat) {
		autoRepeat = repeat;
	}

	void DelayedEntitySystem::processEntities(ImmutableBag<Entity*>& bag) {
		processEntities(bag, acc);

		if(autoRepeat) {
			start(delay);
		} else {
			stop();
		}
	}

	void DelayedEntitySystem::start(float delay) {
		this->delay = delay;
		acc = 0.0f;
		running = true;
	}

	void DelayedEntitySystem::stop() {
		acc = 0;
		running = false;
	}
  void DelayedEntitySystem::runNow()
  {
    acc = delay;
  }

};
