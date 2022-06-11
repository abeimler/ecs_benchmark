#ifndef ECS_BENCHMARKS_FLECS_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_FLECS_MORECOMPLEXSYSTEM_H_

#include "flecs/custom_flecs.h"

#include "base/systems/MoreComplexSystem.h"

namespace ecs::benchmarks::flecs::systems {

    class MoreComplexSystem {
    public:
        using TimeDelta = float;
        using Entity = ::flecs::entity;

        static int random(int min, int max) {
            std::uniform_int_distribution<int> distr(min, max);
            return distr(m_eng);
        }

        inline static auto update = [](::flecs::iter &it, size_t /*index*/,
                                       ecs::benchmarks::base::components::PositionComponent &position,
                                       ecs::benchmarks::base::components::VelocityComponent &direction,
                                       ecs::benchmarks::base::components::DataComponent &data) {
            const TimeDelta dt = it.delta_time();

            std::vector<int> vec;
            for (int i = 0; i < data.dingy && i < 100; i++) {
                vec.push_back(i * static_cast<int>(data.thingy));
            }

            const auto sum = std::accumulate(std::begin(vec), std::end(vec), 0);
            const auto product = std::accumulate(std::begin(vec), std::end(vec), 1,
                                                 std::multiplies<>());

            data.dingy = sum + product;
            data.stringy = std::to_string(data.dingy);

            if (data.dingy % 10000 == 0) {
                if (position.x > position.y) {
                    direction.x = static_cast<float>(MoreComplexSystem::random(0, 5)) * dt;
                    direction.y = static_cast<float>(MoreComplexSystem::random(0, 10)) * dt;
                } else {
                    direction.x = static_cast<float>(MoreComplexSystem::random(0, 10)) * dt;
                    direction.y = static_cast<float>(MoreComplexSystem::random(0, 5)) * dt;
                }
            }
        };

    private:
        static std::random_device m_rd;
        static std::mt19937 m_eng;
    };

}

#endif