#pragma once

#include <particleSystem.h>
#include <assert.h>
#include "../utils/export_directives.h"

namespace fluidity
{

class EXPORT ParticleSystemWrapper {
public: 
    explicit ParticleSystemWrapper()
    : m_particleSystem(nullptr),
      m_paused(false) 
    { }
    auto Init(int argc, char* args[]) -> bool;
    auto AddSphere() -> void;
    auto Update() -> void;
    auto Pause()  -> void { m_paused = true;  }
    auto Resume() -> void { m_paused = false; }

    auto GetParticleSystem() const -> ParticleSystem*
    { 
        assert(m_particleSystem != nullptr);
        return m_particleSystem;
    }

private:
    const int   m_iterations        = 1;
    const float m_damping           = 1.f;
    const float m_gravity           = 0.003f;
    const float m_collideSpring     = 0.3f;
    const float m_collideDamping    = 0.02f;
    const float m_collideShear      = 0.1f;
    const float m_collideAttraction = 0.f;
    const float m_timestep          = 0.3f;
    
    const int m_numParticles = 96384;
    // const int m_numParticles = 16384;
    const uint3 m_gridSize   = { 64, 64, 64 };

    ParticleSystem* m_particleSystem;
    bool m_paused;
};

}
