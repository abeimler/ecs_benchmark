#ifndef ENTITYXBENCHMARK_H_
#define ENTITYXBENCHMARK_H_

#include <string>
#include <vector>
#include <memory>

#include "entityx/entityx.h"

class EntityXBenchmark {
    public:

    struct PositionComponent {
        float x = 0.0f;
        float y = 0.0f;
    };

    struct DirectionComponent {
        float x = 0.0f;
        float y = 0.0f;
    };

    struct ComflabulationComponent {
        float thingy = 0.0;
        int dingy = 0;
        bool mingy = false;
        std::string stringy;
    };


    // Convenience types for our entity system.
    using Entity = entityx::Entity;
    using EntityManager = entityx::EventManager;
    using EventManager = entityx::EventManager;

    template <typename C>
    using Component = entityx::ComponentHandle<C>;

    using TimeDelta = entityx::TimeDelta;



    template<class S>
    using System = entityx::System<S>;


    class MovementSystem : public System<MovementSystem> {
        public:
        MovementSystem() = default;

        void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
            Component<PositionComponent> position;
            Component<DirectionComponent> direction;

            for (auto entity : es.entities_with_components(position, direction)) {
                position->x += direction->x * dt;
                position->y += direction->y * dt;
            }
        }
    };

    class ComflabSystem : public System<ComflabSystem> {
        public:
        ComflabSystem() = default;

        void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
            Component<ComflabulationComponent> comflab;

            for (auto entity : es.entities_with_components(comflab)) {
                comflab->thingy *= 1.000001f;
                comflab->mingy = !comflab->mingy;
                comflab->dingy++;
                //comflab.stringy = std::to_string(comflab.dingy);
            }
        }
    };

    class Application : public entityx::EntityX {
        public:
        Application() {
            this->systems.add<MovementSystem>();
            this->systems.add<ComflabSystem>();
            this->systems.configure();
        }

        void update(TimeDelta dt) {
            this->systems.update<MovementSystem>(dt);
            this->systems.update<ComflabSystem>(dt);
        }
    };

    static constexpr double fakeDeltaTime = 1.0 / 60;
};

#endif // ENTITYXBENCHMARK_H_