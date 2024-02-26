#ifndef ECS_BENCHMARKS_PICO_ECS_RENDERSYSTEM_H_
#define ECS_BENCHMARKS_PICO_ECS_RENDERSYSTEM_H_

#include "base/systems/RenderSystem.h"
#include "pico_ecs/entities/EntityFactory.h"
#include <pico_ecs.h>
#include <span>

namespace ecs::benchmarks::pico_ecs::systems {

namespace details {

struct RenderSystemContext {
  ecs::benchmarks::pico_ecs::entities::details::EntityManager* registry{nullptr};
  ecs::benchmarks::base::systems::RenderSystem<ecs::benchmarks::pico_ecs::entities::details::EntityManager, ecs_dt_t>*
      system{nullptr};
};

} // namespace details

class RenderSystem final
    : public ecs::benchmarks::base::systems::RenderSystem<ecs::benchmarks::pico_ecs::entities::details::EntityManager,
                                                          ecs_dt_t> {
public:
  using BaseSystem =
      ::ecs::benchmarks::base::systems::RenderSystem<ecs::benchmarks::pico_ecs::entities::details::EntityManager,
                                                     TimeDelta>;

  RenderSystem() = delete;
  explicit RenderSystem(base::FrameBuffer& frameBuffer)
      : ecs::benchmarks::base::systems::RenderSystem<ecs::benchmarks::pico_ecs::entities::details::EntityManager,
                                                     TimeDelta>(frameBuffer) {}

  void init(EntityManager& /*registry*/) override;
  void update(EntityManager& registry, TimeDelta dt) override;

  [[nodiscard]] inline ecs_id_t id() const noexcept { return m_system; }

private:
  ecs_id_t m_system;
  details::RenderSystemContext m_context;

  static auto renderSprite(ecs_t* ecs, std::span<ecs_id_t> entities, ecs_dt_t dt, void* udata) -> ecs_ret_t;
};

} // namespace ecs::benchmarks::pico_ecs::systems

#endif