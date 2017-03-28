#ifndef ENTITY_H
#define ENTITY_H

#include <bitset>
#include <string>
#include <cstddef>
#include <typeinfo>
#include "BitSize.h"
#include "ImmutableBag.h"
#include "EntityManager.h"
#include "ComponentTypeManager.h"

namespace artemis {
  
	class Component;
	class ComponentType;
	class World;
	//class EntityManager;
  
	/**
   * The entity class. Cannot be instantiated outside the framework, you must
   * create new entities using World.
   */
  class Entity {
    
  private:
    int id;
    long int uniqueId;
    std::bitset<BITSIZE> typeBits;
    std::bitset<BITSIZE> systemBits;
    World * world;
    EntityManager * entityManager;
    
    // No copy constructor
    Entity(const Entity&);
    // No assign operator
    Entity& operator=(const Entity&);
    
  protected:
    
  public:
    Entity(World * world, int id);
    ~Entity();
    int getId();
    void setUniqueId(long int uniqueId);
    long int getUniqueId();
    
    std::bitset<BITSIZE> getTypeBits();
    void addTypeBit(std::bitset<BITSIZE> bit);
    void removeTypeBit(std::bitset<BITSIZE> bit);
    std::bitset<BITSIZE> getSystemBits();
    void addSystemBit(std::bitset<BITSIZE> bit);
    void removeSystemBit(std::bitset<BITSIZE> bit);
    void setSystemBits(std::bitset<BITSIZE> systemBits);
    void setTypeBits(std::bitset<BITSIZE> typeBits);
    void reset();
    
    std::string toString();
    
    void addComponent(Component * c);
    
    //Might change to non template
    template<typename c>
    void removeComponent() {
      entityManager->removeComponent(*this,ComponentTypeManager::getTypeFor<c>());
    }
    
    void removeComponent(ComponentType & type);
    
    
    Component * getComponent(ComponentType & type);
    
    template<typename c>
    Component * getComponent() {
      return (c*)entityManager->getComponent(*this,ComponentTypeManager::getTypeFor<c>());
    }
    
    ImmutableBag<Component*> & getComponents();
    
    bool isActive();
    void refresh();
    void remove();
    void setGroup(std::string group);
    void setTag(std::string tag);
    
    
  };
};
#endif // $(Guard token)
