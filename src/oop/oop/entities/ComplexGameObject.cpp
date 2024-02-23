#include "ComplexGameObject.h"
#include "MovableDataObject.h"
#include "base/systems/RenderSystem.h"
#include "base/systems/SpriteSystem.h"
#include <algorithm>
#include <gsl/gsl-lite.hpp>

namespace ecs::benchmarks::oop::entities {

void ComplexGameObject::updateComplexData() {
  // NOTE: copy-paste from MoreComplexSystem
  if ((m_data.thingy % 10) == 0) {
    if (m_position.x > m_position.y) {
      m_direction.x = gsl::narrow_cast<float>(m_data.rng.range(3, 19)) - 10.0F;
      m_direction.y = gsl::narrow_cast<float>(m_data.rng.range(0, 5));
    } else {
      m_direction.x = gsl::narrow_cast<float>(m_data.rng.range(0, 5));
      m_direction.y = gsl::narrow_cast<float>(m_data.rng.range(3, 19)) - 10.0F;
    }
  }
}

void ComplexGameObject::updateSprite() {
  m_sprite.character = [&]() {
    switch (m_health.status) {
      case base::components::StatusEffect::Alive:
        switch (m_player.type) {
          case base::components::PlayerType::Hero:
            return '@';
          case base::components::PlayerType::Monster:
            return 'd';
          case base::components::PlayerType::NPC:
            return 'h';
        }
        break;
      case base::components::StatusEffect::Dead:
        return '|';
      case base::components::StatusEffect::Spawn:
        return '_';
    }
    return ' ';
  }();
}


void ComplexGameObject::updateHealth() {
  using namespace ecs::benchmarks::base::components;
  if (m_health.hp <= 0 && m_health.status != StatusEffect::Dead) {
    m_health.hp = 0;
    m_health.status = StatusEffect::Dead;
  } else if (m_health.status == StatusEffect::Dead && m_health.hp == 0) {
    m_health.hp = m_health.maxhp;
    m_health.status = StatusEffect::Spawn;
  } else if (m_health.hp >= m_health.maxhp && m_health.status != StatusEffect::Alive) {
    m_health.hp = m_health.maxhp;
    m_health.status = StatusEffect::Alive;
  } else {
    m_health.status = StatusEffect::Alive;
  }
}

void ComplexGameObject::updateDamage() {
  using namespace ecs::benchmarks::base::components;
  // Calculate damage
  const int totalDamage = m_damage.atk - m_damage.def;

  if (m_health.hp > 0 && totalDamage > 0) {
    m_health.hp = std::max(m_health.hp - totalDamage, 0);
  }
}

void ComplexGameObject::update(float dt) {
  MovableDataObject::update(dt);
  updateComplexData();
  updateHealth();
  updateDamage();
  updateSprite();
}

void ComplexGameObject::render(base::FrameBuffer& frameBuffer) {
  frameBuffer.draw(gsl::narrow_cast<int>(m_position.x), gsl::narrow_cast<int>(m_position.y), m_sprite.character);
}

} // namespace ecs::benchmarks::oop::entities