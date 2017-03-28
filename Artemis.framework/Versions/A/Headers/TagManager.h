#ifndef TAG_MANAGER_H
#define TAG_MANAGER_H


#include <map>
#include <string>

namespace artemis {
  
	//class World;
	class Entity;
  
  /**
   * If you need to tag any entity, use this. A typical usage would be to tag
   * entities such as "PLAYER", "BOSS" or something that is very unique.
   */
	class TagManager {
  private:
    //World * world;
    std::map<std::string, Entity*> tagByEntity;
  public:
    //TagManager(World &world);
    TagManager();
    void subscribe(const std::string tag, Entity &e);
    void unSubscribe(const std::string tag);
    bool isSubscribed(const std::string tag);
    Entity & getEntity(const std::string tag);
    void remove(Entity &e);
	};
};
#endif // $(Guard token)
