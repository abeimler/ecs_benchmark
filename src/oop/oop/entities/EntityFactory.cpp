#include "EntityFactory.h"
#include "MovableObject.h"
#include "MovableDataObject.h"
#include "ComplexMovableDataObject.h"
#include <algorithm>

namespace ecs::benchmarks::oop::entities {

    EntityFactory::Entity EntityFactory::create(EntityManager &registry) {
        auto& ret = (add_more_complex_system)? registry.emplace_back(std::make_unique<ComplexMovableDataObject>()) : registry.emplace_back(std::make_unique<MovableDataObject>());
        ret->id(registry.size());
        return ret.get();
    }

    void EntityFactory::createBulk(EntityManager &registry, std::vector<Entity> &out) {
        registry.reserve(registry.size() + out.size());
        for (size_t i = 0; i < out.size(); i++) {
            auto& ret = (add_more_complex_system)? registry.emplace_back(std::make_unique<ComplexMovableDataObject>()) : registry.emplace_back(std::make_unique<MovableDataObject>());
            ret->id(registry.size());
        }
    }

    EntityFactory::Entity EntityFactory::createMinimal(EntityManager &registry) {
        auto& ret = registry.emplace_back(std::make_unique<MovableObject>());
        ret->id(registry.size());
        return ret.get();
    }

    void EntityFactory::createMinimalBulk(EntityManager &registry, std::vector<Entity> &out) {
        registry.reserve(registry.size() + out.size());
        for (size_t i = 0; i < out.size(); i++) {
            auto& ret = registry.emplace_back(std::make_unique<MovableObject>());
            ret->id(registry.size());
        }
    }

    void EntityFactory::destroy(EntityManager &registry, Entity entity) {
        if (entity != nullptr && entity->id() != 0) {
            registry.erase( std::next( registry.begin(), entity->id()-1 ) );
        }
    }

    void EntityFactory::destroyBulk(EntityManager &registry, std::vector<Entity> &in) {
        std::remove_if(registry.begin(), registry.end(), [&](const auto &ptr) {
            return std::any_of(in.begin(), in.end(), [&](const auto &it) {
                return it == ptr.get();
            });
        });
    }

    void EntityFactory::clear(EntityManager &registry) {
        registry.clear();
    }

}