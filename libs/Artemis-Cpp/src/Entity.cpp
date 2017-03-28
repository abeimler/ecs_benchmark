#include "Artemis/Entity.h"
#include <sstream>
#include "Artemis/Component.h"
#include "Artemis/World.h"
//#include "EntityManager.h"

using namespace std;

namespace artemis {
  
  Entity::Entity(World * world, int id) {
    this->world = world;
    this->entityManager = world->getEntityManager();
    this->id = id;
  }
  
  Entity::~Entity() {
    world = NULL;
    entityManager = NULL;
  }
  
  
  void Entity::addSystemBit(bitset<BITSIZE> bit) {
    systemBits |= bit;
  }
  
  void Entity::addTypeBit(bitset<BITSIZE> bit) {
    typeBits |= bit;
  }
  
  Component* Entity::getComponent(ComponentType & type) {
    return entityManager->getComponent(*this, type);
  }
  
  ImmutableBag<Component*> & Entity::getComponents() {
    return entityManager->getComponents(*this);
  }
  
  int Entity::getId() {
    return id;
  }
  
  bitset<BITSIZE> Entity::getSystemBits() {
    return systemBits;
  }
  
  bitset<BITSIZE> Entity::getTypeBits() {
    return typeBits;
  }
  
  long int Entity::getUniqueId() {
    return uniqueId;
  }
  
  bool Entity::isActive() {
    return entityManager->isActive(this->getId());
  }
  
  void Entity::refresh() {
    world->refreshEntity(*this);
  }
  
  void Entity::addComponent(Component * c){
    entityManager->addComponent(*this,c);
  }
  
  void Entity::removeComponent(ComponentType & type) {
    entityManager->removeComponent(*this, type);
  }
  
  void Entity::removeSystemBit(bitset<BITSIZE> bit) {
    systemBits &= ~bit;
  }
  
  void Entity::removeTypeBit(bitset<BITSIZE> bit) {
    typeBits &= ~bit;
  }
  
  void Entity::reset() {
    typeBits = 0;
    systemBits = 0;
  }
  
  void Entity::setGroup(string group) {
    
    world->getGroupManager()->set(group, *this);
  }
  
  void Entity::setSystemBits(bitset<BITSIZE> systemBits) {
    this->systemBits = systemBits;
  }
  
  void Entity::setTag(string tag) {
    world->getTagManager()->subscribe(tag, *this);
  }
  
  void Entity::setTypeBits(bitset<BITSIZE> typeBits) {
    this->typeBits = typeBits;
  }
  
  void Entity::setUniqueId(long int uniqueId) {
    this->uniqueId = uniqueId;
  }
  
  std::string Entity::toString() {
    std::ostringstream oss;
    oss << "Entity[" << id << "]\n";
    return  oss.str();
  }
  
  void Entity::remove() {
    world->deleteEntity(*this);
  }
};
