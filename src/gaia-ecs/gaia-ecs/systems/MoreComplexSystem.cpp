#include "MoreComplexSystem.h"

namespace ecs::benchmarks::gaia_ecs::systems {

std::random_device MoreComplexSystem::m_rd;
std::mt19937 MoreComplexSystem::m_eng(MoreComplexSystem::m_rd());

} // namespace ecs::benchmarks::gaia_ecs::systems