#ifndef ECS_BENCHMARKS_PICO_ECS_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_PICO_ECS_ENTITYFACTORY_H_

#include <pico_ecs.h>
#include <memory>
#include <bit>

#include "base/entities/EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::pico_ecs::entities {

    namespace details {
    struct EcsDeleter {
      void operator()(ecs_t* p_ecs) { ecs_free(p_ecs); }
    };

    class EntityManager {
    public:
      static inline constexpr int MIN_ENTITIES = 1 * 1024;

      EntityManager() : ecs(ecs_new(MIN_ENTITIES, nullptr)) { register_components(); }

      EntityManager(const EntityManager&) = delete;
      EntityManager(EntityManager&&) = default;
      EntityManager& operator=(const EntityManager&) = delete;
      EntityManager& operator=(EntityManager&&) = default;
      ~EntityManager() = default;

      std::unique_ptr<ecs_t, details::EcsDeleter> ecs;

      ecs_id_t PositionComponent;
      ecs_id_t VelocityComponent;
      ecs_id_t DataComponent;

    private:
      void register_components() {
        PositionComponent = ecs_register_component(ecs.get(), sizeof(ecs::benchmarks::base::components::PositionComponent));
        VelocityComponent = ecs_register_component(ecs.get(), sizeof(ecs::benchmarks::base::components::VelocityComponent));
        DataComponent = ecs_register_component(ecs.get(), sizeof(ecs::benchmarks::base::components::DataComponent));
      }
    };
    }

    class EntityFactory {
    public:
        using EntityManager = details::EntityManager;
        using Entity = ecs_id_t;

        auto create(EntityManager &registry) {
            const ecs_id_t id = ecs_create(registry.ecs.get());
            ecs_add(registry.ecs.get(), id, registry.PositionComponent);
            ecs_add(registry.ecs.get(), id, registry.VelocityComponent);
            ecs_add(registry.ecs.get(), id, registry.DataComponent);
            return id;
        }

        auto createMinimal(EntityManager &registry) {
            const ecs_id_t id = ecs_create(registry.ecs.get());
            ecs_add(registry.ecs.get(), id, registry.PositionComponent);
            ecs_add(registry.ecs.get(), id, registry.VelocityComponent);
            return id;
        }

        auto createEmpty(EntityManager &registry) {
            return ecs_create(registry.ecs.get());
        }

        auto createSingle(EntityManager &registry) {
            const ecs_id_t id = ecs_create(registry.ecs.get());
            ecs_add(registry.ecs.get(), id, registry.PositionComponent);
            return id;
        }

        void destroy(EntityManager &registry, Entity entity_id) {
            ecs_destroy(registry.ecs.get(), entity_id);
        }

        void clear(EntityManager &registry) {
            ecs_reset(registry.ecs.get());
        }


        [[nodiscard]] static inline const ecs::benchmarks::base::components::PositionComponent &
        getComponentOneConst(EntityManager &registry, Entity entity_id) {
            return *reinterpret_cast<ecs::benchmarks::base::components::PositionComponent*>(ecs_get(registry.ecs.get(), entity_id, registry.PositionComponent));
        }

        [[nodiscard]] static inline const ecs::benchmarks::base::components::VelocityComponent &
        getComponentTwoConst(EntityManager &registry, Entity entity_id) {
            return *reinterpret_cast<ecs::benchmarks::base::components::VelocityComponent*>(ecs_get(registry.ecs.get(), entity_id, registry.VelocityComponent));
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::PositionComponent &
        getComponentOne(EntityManager &registry, Entity entity_id) {
            return *reinterpret_cast<ecs::benchmarks::base::components::PositionComponent*>(ecs_get(registry.ecs.get(), entity_id, registry.PositionComponent));
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::VelocityComponent &
        getComponentTwo(EntityManager &registry, Entity entity_id) {
            return *reinterpret_cast<ecs::benchmarks::base::components::VelocityComponent*>(ecs_get(registry.ecs.get(), entity_id, registry.VelocityComponent));
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::DataComponent *
        getOptionalComponentThree(EntityManager &registry, Entity entity_id) {
            return reinterpret_cast<ecs::benchmarks::base::components::DataComponent*>(ecs_get(registry.ecs.get(), entity_id, registry.DataComponent));
        }


        static inline void removeComponentOne(EntityManager &registry, Entity entity_id) {
            ecs_remove(registry.ecs.get(), entity_id, registry.PositionComponent);
        }

        static inline void removeComponentTwo(EntityManager &registry, Entity entity_id) {
            ecs_remove(registry.ecs.get(), entity_id, registry.VelocityComponent);
        }

        static inline void removeComponentThree(EntityManager &registry, Entity entity_id) {
            ecs_remove(registry.ecs.get(), entity_id, registry.DataComponent);
        }

        static inline auto &addComponentOne(EntityManager &registry, Entity entity_id) {
            return *reinterpret_cast<ecs::benchmarks::base::components::PositionComponent*>(ecs_add(registry.ecs.get(), entity_id, registry.PositionComponent));
        }
    };

}

#endif