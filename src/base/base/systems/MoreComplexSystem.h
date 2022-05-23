#ifndef ECS_BENCHMARKS_BASE_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_BASE_MORECOMPLEXSYSTEM_H_

#include <random>
#include <vector>

#include "System.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/ComflabulationComponent.h"

namespace ecs::benchmarks::base::systems {

    template<class EntityManager, typename TimeDelta,
            class PositionComponent = ecs::benchmarks::base::components::PositionComponent,
            class DirectionComponent = ecs::benchmarks::base::components::DirectionComponent,
            class ComflabulationComponent = ecs::benchmarks::base::components::ComflabulationComponent>
    class MoreComplexSystem : public System<EntityManager, TimeDelta> {
    public:
        // virtual dtor and the rule of 6
        MoreComplexSystem() : m_eng(m_rd()) {};

        virtual ~MoreComplexSystem() = default;

        MoreComplexSystem(const MoreComplexSystem &) = delete;

        MoreComplexSystem &operator=(const MoreComplexSystem &) = delete;

        MoreComplexSystem(MoreComplexSystem &&) = default;

        MoreComplexSystem &operator=(MoreComplexSystem &&) = default;

        void
        updateComponents(PositionComponent &position, DirectionComponent &direction, ComflabulationComponent &comflab,
                         TimeDelta /*dt*/) {
            std::vector<int> vec;
            for (int i = 0; i < comflab.dingy && i < 100; i++) {
                vec.push_back(i * static_cast<int>(comflab.thingy));
            }

            const auto sum = std::accumulate(std::begin(vec), std::end(vec), 0);
            const auto product = std::accumulate(std::begin(vec), std::end(vec), 1,
                                                 std::multiplies<>());

            comflab.dingy = sum + product;
            comflab.stringy = std::to_string(comflab.dingy);

            if (comflab.dingy % 10000 == 0) {
                if (position.x > position.y) {
                    direction.x = static_cast<float>(random(0, 5));
                    direction.y = static_cast<float>(random(0, 10));
                } else {
                    direction.x = static_cast<float>(random(0, 10));
                    direction.y = static_cast<float>(random(0, 5));
                }
            }
        }

    private:
        int random(int min, int max) {
            std::uniform_int_distribution<int> distr(min, max);
            return distr(m_eng);
        }

        std::random_device m_rd;
        std::mt19937 m_eng;
    };

}

#endif