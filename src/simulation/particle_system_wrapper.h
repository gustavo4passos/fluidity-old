#pragma once

#include <particleSystem.h>
#include "assert.h"

namespace fluidity
{

class ParticleSystemWrapper {
public: 
    explicit ParticleSystemWrapper()
    : m_particleSystem(nullptr) 
    { }
    auto Init(int argc, char* args[]) -> bool;
    auto Update() -> void;
    auto GetParticleSystem() const -> ParticleSystem*
    { 
        assert(m_particleSystem != nullptr);
        return m_particleSystem;
    }

private:
    const int   m_iterations        = 1;
    const float m_damping           = 1.f;
    const float m_gravity           = 0.003f;
    const float m_collideSpring     = 0.5f;
    const float m_collideDamping    = 0.02f;
    const float m_collideShear      = 0.1f;
    const float m_collideAttraction = 0.f;
    const float m_timestep          = 0.5f;
    
    const int m_numParticles = 16384;
    const uint3 m_gridSize   = { 64, 64, 64 };

    ParticleSystem* m_particleSystem;
};

}