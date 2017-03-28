#include "Artemis/TagManager.h"
#include "Artemis/Entity.h"

namespace artemis {
  
	TagManager::TagManager() {
		//this->world = &world;
	}
  
	Entity& TagManager::getEntity(const std::string tag) {
		return *tagByEntity[tag];
	}
  
	bool TagManager::isSubscribed(const std::string tag) {
		return (tagByEntity[tag] != NULL);
	}
  
	void TagManager::remove(Entity &e) {
		// TODO find cleaner way to remove by value
		std::map<std::string, Entity*>::iterator it;
		for (it = tagByEntity.begin(); it != tagByEntity.end(); ++it) {
      if(it->second == &e){
				tagByEntity.erase(it->first);
				return;
			}
    }

	}
  
	void TagManager::unSubscribe(const std::string tag) {
		//tagByEntity[tag] = NULL;
		tagByEntity.erase(tag);
	}
	
	void TagManager::subscribe(std::string tag, Entity &e){
		remove(e);
		tagByEntity[tag] = &e;
	}
  
}
