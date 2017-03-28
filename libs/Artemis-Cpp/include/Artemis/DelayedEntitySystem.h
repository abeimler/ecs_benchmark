#ifndef DELAYED_ENTITY_SYSTEM_H
#define DELAYED_ENTITY_SYSTEM_H

#include "EntitySystem.h"

namespace artemis {
	class DelayedEntitySystem : public EntitySystem {
		private:
			float delay;
			float acc;
			bool running;
			bool autoRepeat;
		protected:
			virtual void processEntities(ImmutableBag<Entity*> & bag);
			virtual void processEntities(ImmutableBag<Entity*> & bag, float accumulatedDelta) = 0;
			virtual bool checkProcessing();
	public:
			DelayedEntitySystem();
			void start(float delay);
    void runNow();
			void stop();
			void setAutoRepeat(bool repeat);
			float getInitialTimeDelay();
			float getRemainingTime();
			bool isRunning();

	};
};

#endif // $(Guard token)
