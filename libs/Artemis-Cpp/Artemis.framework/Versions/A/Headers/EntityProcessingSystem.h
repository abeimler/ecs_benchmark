#ifndef ENT_PROCESS_SYS_H
#define ENT_PROCESS_SYS_H

#include "ImmutableBag.h"
#include "EntitySystem.h"

namespace artemis {

	class Entity;
  /**
   * @brief A typical entity system.
   *
   * Use this when you need to process entities possessing the provided 
   * component types.
   */
	class EntityProcessingSystem : public EntitySystem {

		protected:
			EntityProcessingSystem() {};
			virtual void processEntity(Entity &e) = 0;
			virtual void processEntities(ImmutableBag<Entity*> & bag);
			virtual bool checkProcessing();
	};
};

#endif // $(Guard token)
