#include "Artemis/DelayedEntityProcessingSystem.h"

namespace artemis {
  
	void DelayedEntityProcessingSystem::processEntities(ImmutableBag<Entity*>& bag, float accumulatedDelta) {
		for(int i=0; i< bag.getCount(); i++)
			processEntity(*bag.get(i), accumulatedDelta);
	}
}
