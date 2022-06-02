#ifndef ECS_BENCHMARKS_ENTITASPP_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_ENTITASPP_MORECOMPLEXSYSTEM_H_

#include <EntitasPP/ComponentTypeId.hpp>
#include <EntitasPP/Matcher.hpp>
#include <EntitasPP/ISystem.hpp>
#include <EntitasPP/Pool.hpp>

#include "base/systems/MoreComplexSystem.h"
#include "EntitasPP/components/PositionComponent.h"
#include "EntitasPP/components/DirectionComponent.h"
#include "EntitasPP/components/DataComponent.h"

namespace ecs::benchmarks::EntitasPP::systems {

    class MoreComplexSystem final
            : public ::EntitasPP::IExecuteSystem, public ::EntitasPP::ISetPoolSystem, public base::systems::MoreComplexSystem<::EntitasPP::Pool, float> {
    public:
        void SetPool(::EntitasPP::Pool* pool) override {
            #define EntitasPP_COMPONENT_GET_TYPE_ID(COMPONENT_CLASS) ::EntitasPP::ComponentTypeId::Get<COMPONENT_CLASS>()
            #define EntitasPP_Matcher_AllOf(...) (::EntitasPP::Matcher::AllOf(std::vector<::EntitasPP::ComponentId>({ FOR_EACH(EntitasPP_COMPONENT_GET_TYPE_ID, __VA_ARGS__) })))
            m_group = pool->GetGroup(EntitasPP_Matcher_AllOf(EntitasPP::components::PositionComponent, EntitasPP::components::DirectionComponent, EntitasPP::components::DataComponent));
            #undef EntitasPP_COMPONENT_GET_TYPE_ID
            #undef EntitasPP_Matcher_AllOf
        }


        void Execute() override;

        void update(EntityManager &entities, TimeDelta dt) override;

    private:
        std::weak_ptr<::EntitasPP::Group> m_group;
    };

}

#endif