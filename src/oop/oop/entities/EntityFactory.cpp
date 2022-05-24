#include "EntityFactory.h"
#include <algorithm>

namespace ecs::benchmarks::oop::entities {

    EntityFactory::EntityMDO EntityFactory::create(EntityManagerMDO &registry) {
        return &registry.emplace_back();
    }

    void EntityFactory::createBulk(EntityManagerMDO &registry, std::vector<EntityMDO> &out) {
        registry.reserve(registry.size() + out.size());
        for (size_t i = 0; i < out.size(); i++) {
            out[i] = &registry.emplace_back();
        }
    }

    EntityFactory::EntityMO EntityFactory::createMinimal(EntityManagerMO &registry) {
        return &registry.emplace_back();
    }

    void EntityFactory::createMinimalBulk(EntityManagerMO &registry, std::vector<EntityMO> &out) {
        registry.reserve(registry.size() + out.size());
        for (size_t i = 0; i < out.size(); i++) {
            out[i] = &registry.emplace_back();
        }
    }

    void EntityFactory::destory(EntityManagerMO &registry, EntityMO entity) {
        std::remove_if(registry.begin(), registry.end(), [&](const auto &e) {
            return &e == entity;
        });
    }

    void EntityFactory::destory(EntityManagerMDO &registry, EntityMDO entity) {
        std::remove_if(registry.begin(), registry.end(), [&](const auto &e) {
            return &e == entity;
        });
    }

    void EntityFactory::destoryBulk(EntityManagerMO &registry, std::vector<EntityMO> &in) {
        std::remove_if(registry.begin(), registry.end(), [&](const auto &e) {
            return std::any_of(in.begin(), in.end(), [&](const auto &it) {
                return it == &e;
            });
        });
    }

    void EntityFactory::destoryBulk(EntityManagerMDO &registry, std::vector<EntityMDO> &in) {
        std::remove_if(registry.begin(), registry.end(), [&](const auto &e) {
            return std::any_of(in.begin(), in.end(), [&](const auto &it) {
                return it == &e;
            });
        });
    }

    void EntityFactory::clear(EntityManagerMO &registry) {
        registry.clear();
    }

    void EntityFactory::clear(EntityManagerMDO &registry) {
        registry.clear();
    }
}
