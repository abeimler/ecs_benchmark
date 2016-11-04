#ifndef D_E_PROCESSING_SYSTEM_H
#define D_E_PROCESSING_SYSTEM_H

#include "DelayedEntitySystem.h"

namespace artemis{
  /**
   * @brief Systems execute at varying intervals.
   *
   * An example system would be an ExpirationSystem, that deletes entities after a certain
   * lifetime. Instead of running a system that decrements a timeLeft value for each
   * entity, you can simply use this system to execute in a future at a time of the shortest
   * lived entity, and then reset the system to run at a time in a future at a time of the
   * shortest lived entity, etc.
   *
   * Another example system would be an AnimationSystem. You know when you have to animate
   * a certain entity, e.g. in 300 milliseconds. So you can set the system to run in 300 ms.
   * to perform the animation.
   *
   * This will save CPU cycles in some scenarios.
   */
	class DelayedEntityProcessingSystem : public DelayedEntitySystem
	{
  protected:
		virtual void processEntities(ImmutableBag<Entity*>& bag, float accumulatedDelta);
		virtual void processEntity(Entity& e, float accumulatedDelta) = 0;
	};
};

#endif // $(Guard token)
