#pragma once

#include "system.h"

namespace Systems {

class MovementSystem : public System {
    public:
        MovementSystem(SystemManager &manager);
        virtual ~MovementSystem() = default;

        virtual void update(EntityManager &es, double dt);

        void move(Entity entity, float x, float y);

        void stop(Entity entity, float x, float y);

        void processMove(Entity entity, const RoseCommon::CliMouseCmd &packet);
};

}
