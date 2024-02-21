#include "SoAMoreComplexSystem.h"

namespace ecs::benchmarks::gaia_ecs::systems {

std::random_device SoAMoreComplexSystem::m_rd;
std::mt19937 SoAMoreComplexSystem::m_eng(SoAMoreComplexSystem::m_rd());

} // namespace ecs::benchmarks::gaia_ecs::systems