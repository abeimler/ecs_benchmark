#ifndef ECS_BENCHMARKS_OOP_COMPLEXMOVABLEWITHDATAOBJECT_H_
#define ECS_BENCHMARKS_OOP_COMPLEXMOVABLEWITHDATAOBJECT_H_

#include "GameObject.h"
#include "MovableDataObject.h"
#include "base/FrameBuffer.h"
#include "base/components/HeroMonsterComponents.h"
#include "base/components/SpriteComponent.h"

namespace ecs::benchmarks::oop::entities {

class ComplexGameObject : public MovableDataObject, public RenderableObject {
public:
  ComplexGameObject() = default;
  ComplexGameObject(const ComplexGameObject&) = default;
  ComplexGameObject(ComplexGameObject&&) = default;
  ComplexGameObject& operator=(const ComplexGameObject&) = default;
  ComplexGameObject& operator=(ComplexGameObject&&) = default;
  ~ComplexGameObject() override = default;

  void update(float dt) override;
  void render(base::FrameBuffer& frameBuffer) override;

private:
  void updateComplexData();
  void updateHealth();
  void updateDamage();
  void updateSprite();

protected:
  ecs::benchmarks::base::components::PlayerComponent m_player;
  ecs::benchmarks::base::components::HealthComponent m_health;
  ecs::benchmarks::base::components::DamageComponent m_damage;
  ecs::benchmarks::base::components::SpriteComponent m_sprite;
};

} // namespace ecs::benchmarks::oop::entities

#endif