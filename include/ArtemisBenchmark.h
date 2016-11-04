#ifndef ARTEMISBENCHMARK_H_
#define ARTEMISBENCHMARK_H_

#include <string>
#include <vector>
#include <memory>

#include <Artemis/Artemis.h>


class ArtemisBenchmark {
    public:

    struct PositionComponent : artemis::Component {
        float x = 0.0f;
        float y = 0.0f;
        
    };

    struct DirectionComponent : artemis::Component {
        float x = 0.0f;
        float y = 0.0f;
        
    };

    struct ComflabulationComponent : artemis::Component {
        float thingy = 0.0;
        int dingy = 0;
        bool mingy = false;
        std::string stringy;
        
    };

    using System = artemis::EntityProcessingSystem;
    using Entity = artemis::Entity;
    using EntityManager = artemis::EntityManager;

    typedef double TimeDelta;

    class MovementSystem : public artemis::EntityProcessingSystem {
        private:
        artemis::ComponentMapper<PositionComponent> positionMapper_;
        artemis::ComponentMapper<DirectionComponent> directionMapper_;
        
        public:
        virtual ~MovementSystem() = default;
        MovementSystem(const MovementSystem&) = default;
        MovementSystem& operator=(const MovementSystem&) = default;
        MovementSystem(MovementSystem&&) = default;
        MovementSystem& operator=(MovementSystem&&) = default;

        MovementSystem() {
            addComponentType<PositionComponent>();
            addComponentType<DirectionComponent>();
        };

        virtual void initialize() {
            positionMapper_.init(*world);
            directionMapper_.init(*world);
        };

        virtual void processEntity(artemis::Entity &e) {
            auto dt = world->getDelta();

            auto position = positionMapper_.get(e);
            auto direction = directionMapper_.get(e);

            position->x += direction->x * dt;
            position->y += direction->y * dt;
        };
    };

    class ComflabSystem : public artemis::EntityProcessingSystem {
        private:
        artemis::ComponentMapper<ComflabulationComponent> comflabulationMapper_;
        
        public:
        virtual ~ComflabSystem() = default;
        ComflabSystem(const ComflabSystem&) = default;
        ComflabSystem& operator=(const ComflabSystem&) = default;
        ComflabSystem(ComflabSystem&&) = default;
        ComflabSystem& operator=(ComflabSystem&&) = default;

        ComflabSystem() {
            addComponentType<ComflabulationComponent>();
        };

        virtual void initialize() {
            comflabulationMapper_.init(*world);
        };

        virtual void processEntity(artemis::Entity &e) {
            auto dt = world->getDelta();

            auto comflab = comflabulationMapper_.get(e);

            comflab->thingy *= 1.000001f;
            comflab->mingy = !comflab->mingy;
            comflab->dingy++;
            //comflab.stringy = std::to_string(comflab.dingy);
        }
    };

    class Application : public artemis::World {
        public:
        Application(){
            auto systemmanager = this->getSystemManager();

            this->movement_system_ = (MovementSystem*) systemmanager->setSystem(new MovementSystem());
            this->comflab_system_ = (ComflabSystem*) systemmanager->setSystem(new ComflabSystem());

            systemmanager->initializeAll();
        }

        void update(TimeDelta dt) {
            this->loopStart();
            this->setDelta(dt);

            this->movement_system_->process();
            this->comflab_system_->process();
        }

        private:
        MovementSystem* movement_system_;
        ComflabSystem* comflab_system_;
    };
    
    static constexpr TimeDelta fakeDeltaTime = 1.0 / 60;
};

#endif // ARTEMISBENCHMARK_H_