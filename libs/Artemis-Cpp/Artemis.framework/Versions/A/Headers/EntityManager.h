#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H


#include "ImmutableBag.h"
#include "Component.h"
#include "ComponentTypeManager.h"


namespace artemis {
  
  class Entity;
  class World;
  class EntityManager {
    
  public:
    EntityManager(World& world);
    ~EntityManager();
    Entity & create();
    void remove(Entity &e);
    void removeComponentsOfEntity(Entity & e);
    bool isActive(int entityId);
    void addComponent(Entity &e, Component * c);
    void refresh(Entity &e);
    
    void removeAllEntities();
    
    void removeComponent(Entity & e, ComponentType & type);
    
    template<typename c>
    void removeComponent(Entity & e) {
      removeComponent(e,ComponentTypeManager::getTypeFor<c>());
    }
    
    Component * getComponent(Entity & e, ComponentType & type);
    
    template<typename c>
    Component * getComponent(Entity & e) {
      ComponentType type = ComponentTypeManager::getTypeFor<c>();
      return getComponent(e,type);
    }
    
    Entity& getEntity(int entityId);
    int getEntityCount();
    long getTotalCreated();
    long getTotalRemoved();
    
    Bag<Component*>& getComponents(Entity & e);
    
    
  private:
    World * world;
    Bag<Entity*> activeEntities;
    Bag<Entity*> removedAndAvailable;
    int nextAvailableId;
    int count;
    long uniqueEntityId;
    long totalCreated;
    long totalRemoved;
    
    Bag<Bag<Component*>*> componentsByType;
    Bag<Component*> entityComponents;
    
  };
};
#endif // $(Guard token)
