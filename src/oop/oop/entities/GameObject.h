#ifndef ECS_BENCHMARK_GAMEOBJECT_H
#define ECS_BENCHMARK_GAMEOBJECT_H

#include <cstddef>

namespace ecs::benchmarks::oop::entities {
    class EntityFactory;

    class GameObject {
    public:
        using game_object_id_t = std::size_t;

        GameObject() = default;
        GameObject(const GameObject&) = default;
        GameObject(GameObject&&) = default;
        GameObject& operator=(const GameObject&) = default;
        GameObject& operator=(GameObject&&) = default;
        virtual ~GameObject() = default;

        virtual void update(float dt) = 0;

        [[nodiscard]] inline game_object_id_t id() const noexcept { return m_id; }

    protected:
        GameObject(game_object_id_t id) : m_id(id) {}
        inline void id(game_object_id_t id) noexcept { m_id = id; }

        friend class EntityFactory;

    private:
        game_object_id_t m_id;
    };
}

#endif //ECS_BENCHMARK_GAMEOBJECT_H
