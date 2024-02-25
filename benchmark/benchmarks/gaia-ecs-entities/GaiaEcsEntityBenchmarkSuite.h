#ifndef ECS_BENCHMARKS_GAIA_ECS_ENTITYBENCHMARK_H_
#define ECS_BENCHMARKS_GAIA_ECS_ENTITYBENCHMARK_H_

#include "EntityBenchmark.h"
#include "gaia-ecs/entities/EntityFactory.h"
#include <utility>

#define STR(arg) #arg
#define XSTR(arg) STR(arg)
#define GAIA_VERSION XSTR(GAIA_VERSION_MAJOR) "." XSTR(GAIA_VERSION_MINOR) "." XSTR(GAIA_VERSION_PATCH)

namespace ecs::benchmarks::gaia_ecs {

class GaiaEcsEntityBenchmarkSuite final
    : public ecs::benchmarks::base::EntityBenchmark<"gaia-ecs", entities::EntityFactory> {
public:
  GaiaEcsEntityBenchmarkSuite() = default;

  explicit GaiaEcsEntityBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : EntityBenchmark(std::move(options)) {}
};

} // namespace ecs::benchmarks::gaia_ecs

#endif // ECS_BENCHMARKS_GAIA_ECS_ENTITYBENCHMARK_H_
