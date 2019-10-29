#ifndef ENTITYXBENCHMARK_H_
#define ENTITYXBENCHMARK_H_

#include <string>
#include <vector>
#include <memory>
#include <random>
#include <numeric>
#include <functional>

#include <entityx/entityx.h>

class EntityXBenchmark {
    public:

    struct PositionComponent {
        double x = 0.0f;
        double y = 0.0f;
    };

    struct DirectionComponent {
        double x = 0.0f;
        double y = 0.0f;
    };

    struct ComflabulationComponent {
        double thingy = 0.0;
        int dingy = 0;
        bool mingy = false;
        std::string stringy;
    };


    // Convenience types for our entity system.
    using Entity = entityx::Entity;
    using EntityManager = entityx::EntityManager;
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

    #ifdef USE_MORECOMPLEX_SYSTEM
    class MoreComplexSystem : public System<MoreComplexSystem> {
        private:
        static int random(int min, int max){
            // Seed with a real random value, if available
            static std::random_device r;
        
            // Choose a random mean between min and max
            static std::default_random_engine e1(r());

            std::uniform_int_distribution<int> uniform_dist(min, max);

            return uniform_dist(e1);
        }

        public:
        MoreComplexSystem() = default;

        void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
            Component<PositionComponent> position;
            Component<DirectionComponent> direction;
            Component<ComflabulationComponent> comflab;

            for (auto entity : es.entities_with_components(comflab, direction, comflab)) {
                if(comflab) {
                    std::vector<double> vec;
                    for(size_t i = 0;i < comflab->dingy && i < 100;i++){
                        vec.push_back(i * comflab->thingy);
                    }

                    int sum = std::accumulate(std::begin(vec), std::end(vec), 0.0);
                    int product = std::accumulate(std::begin(vec), std::end(vec), 1, std::multiplies<double>());

                    comflab->stringy = std::to_string(comflab->dingy);

                    if(position && direction && comflab->dingy % 10000 == 0) {
                        if(position->x > position->y) {
                            direction->x = random(0, 5);
                            direction->y = random(0, 10);
                        } else {
                            direction->x = random(0, 10);
                            direction->y = random(0, 5);
                        }
                    }
                }
            }
        }
    };
    #endif

    class Application : public entityx::EntityX {
        public:
        Application() {
            this->systems.add<MovementSystem>();
            this->systems.add<ComflabSystem>();
            #ifdef USE_MORECOMPLEX_SYSTEM
            this->systems.add<MoreComplexSystem>();
            #endif

            this->systems.configure();
        }

        void update(TimeDelta dt) {
            this->systems.update<MovementSystem>(dt);
            this->systems.update<ComflabSystem>(dt);
            #ifdef USE_MORECOMPLEX_SYSTEM
            this->systems.update<MoreComplexSystem>(dt);
            #endif
        }
    };

    static constexpr double fakeDeltaTime = 1.0 / 60;
};

#endif // ENTITYXBENCHMARK_H_