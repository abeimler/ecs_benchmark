#ifndef ECS_BENCHMARKS_ENTITYXENTITYBENCHMARK_H_
#define ECS_BENCHMARKS_ENTITYXENTITYBENCHMARK_H_

#include <utility>

#include "entityx/entities/EntityFactory.h"
#include "entityx/EntityXApplication.h"

#include "ECSBenchmark.h"


#define STR(arg) #arg
#define XSTR(arg) STR(arg)
#define ENTITYX_VERSION XSTR(ENTITYX_MAJOR_VERSION) "." XSTR(ENTITYX_MINOR_VERSION) "." XSTR(ENTITYX_PATCH_VERSION)

namespace ecs::benchmarks::entityx {

    class EntityXEntityBenchmarkSuite final
            : public ecs::benchmarks::base::ECSBenchmark<"entityx",
                    EntityXApplication, entities::EntityFactory,
                    /*include_entity_benchmarks= */true // application is needed to get entity manager
                    > {
    public:
        EntityXEntityBenchmarkSuite() = default;

        explicit EntityXEntityBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options) : ECSBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_ENTTENTITYBENCHMARK_H_
