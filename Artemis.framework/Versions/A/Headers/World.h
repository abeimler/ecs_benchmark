#ifndef WORLD_H
#define WORLD_H


#include "ImmutableBag.h"
#include "TagManager.h"
#include "GroupManager.h"

namespace artemis {
	class Entity;
	class EntityManager;
	class SystemManager;
  
  
  /**
   * The primary instance for the framework. It contains all the managers.
   *
   * You must use this to create, delete and retrieve entities.
   *
   * It is also important to set the delta each game loop iteration, and initialize before game loop.
   */
	class World {
  public:
    World();
    ~World();
    SystemManager * getSystemManager();
    EntityManager * getEntityManager();
    TagManager *   getTagManager();
    GroupManager * getGroupManager();
    float getDelta();
    void setDelta(float delta);
    void deleteEntity(Entity& e);
    void refreshEntity(Entity& e);
    Entity& createEntity();
    Entity& getEntity(int entityId);
    void loopStart();
    
    
    
  private:
    SystemManager * systemManager;
    EntityManager * entityManager;
    TagManager * tagManager;
    GroupManager * groupManager;
    float delta;
    Bag<Entity*> refreshed;
    Bag<Entity*> deleted;
	};
};
#endif // $(Guard token)
