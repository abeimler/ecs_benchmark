#ifndef ANAXBENCHMARK_H_
#define ANAXBENCHMARK_H_

#include <string>
#include <vector>
#include <memory>

#include <anax/anax.hpp>
#include <anax/Component.hpp>
#include <anax/System.hpp>


class AnaxBenchmark {
    public:

    struct PositionComponent : anax::Component {
        float x = 0.0f;
        float y = 0.0f;

        
        #ifdef ANAX_VIRTUAL_DTORS_IN_COMPONENT
            PositionComponent() = default;
            virtual ~PositionComponent() = default;
            PositionComponent(const PositionComponent&) = default;
            PositionComponent& operator=(const PositionComponent&) = default;
            PositionComponent(PositionComponent&&) = default;
            PositionComponent& operator=(PositionComponent&&) = default;
        #endif // ANAX_VIRTUAL_DTORS_IN_COMPONENT
        
    };

    struct DirectionComponent : anax::Component {
        float x = 0.0f;
        float y = 0.0f;

        
        #ifdef ANAX_VIRTUAL_DTORS_IN_COMPONENT
            DirectionComponent() = default;
            virtual ~DirectionComponent() = default;
            DirectionComponent(const DirectionComponent&) = default;
            DirectionComponent& operator=(const DirectionComponent&) = default;
            DirectionComponent(DirectionComponent&&) = default;
            DirectionComponent& operator=(DirectionComponent&&) = default;
        #endif // ANAX_VIRTUAL_DTORS_IN_COMPONENT
        
    };

    struct ComflabulationComponent : anax::Component {
        float thingy = 0.0;
        int dingy = 0;
        bool mingy = false;
        std::string stringy;

        
        #ifdef ANAX_VIRTUAL_DTORS_IN_COMPONENT
            ComflabulationComponent() = default;
            virtual ~ComflabulationComponent() = default;
            ComflabulationComponent(const ComflabulationComponent&) = default;
            ComflabulationComponent& operator=(const ComflabulationComponent&) = default;
            ComflabulationComponent(ComflabulationComponent&&) = default;
            ComflabulationComponent& operator=(ComflabulationComponent&&) = default;
        #endif // ANAX_VIRTUAL_DTORS_IN_COMPONENT
        
    };


    typedef double TimeDelta;

    class MovementSystem : public anax::System<anax::Requires<PositionComponent, DirectionComponent>> {
        public:
        MovementSystem() = default;

        void update(TimeDelta dt) {
            auto entities = getEntities();
            for(auto& entity : entities) {
                auto& position = entity.getComponent<PositionComponent>();
                auto& direction = entity.getComponent<DirectionComponent>();
                
                position.x += direction.x * dt;
                position.y += direction.y * dt;
            }
        }
    };

    class ComflabSystem : public anax::System<anax::Requires<ComflabulationComponent>> {
        public:
        ComflabSystem() = default;

        void update(TimeDelta dt) {

            auto entities = getEntities();
            for(auto& entity : entities) {
                auto& comflab = entity.getComponent<ComflabulationComponent>();

                comflab.thingy *= 1.000001f;
                comflab.mingy = !comflab.mingy;
                comflab.dingy++;
                //comflab.stringy = std::to_string(comflab.dingy);
            }
        }
    };

    class Application : public anax::World {
        public:
        Application(){
            this->addSystem(this->movement_system_);
            this->addSystem(this->comflab_system_);
        }

        void update(double dt) {
            this->refresh();

            this->movement_system_.update(dt);
            this->comflab_system_.update(dt);
        }

        private:
        MovementSystem movement_system_;
        ComflabSystem comflab_system_;
    };
    
    static constexpr TimeDelta fakeDeltaTime = 1.0 / 60;
};

#endif // ANAXBENCHMARK_H_