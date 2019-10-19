#include "particle_system_wrapper.h"

extern "C" void cudaInit(int argc, char **args);

namespace fluidity
{

auto ParticleSystemWrapper::Init(int argc, char* args[]) -> bool
{
    cudaInit(argc, args);

    m_particleSystem = new ParticleSystem(
        m_numParticles,
        m_gridSize,
        true);
    m_particleSystem->reset(ParticleSystem::CONFIG_GRID);

    return true;
}

auto ParticleSystemWrapper::Update() -> void
{
    m_particleSystem->setIterations(m_iterations);
    m_particleSystem->setDamping(m_damping);
    m_particleSystem->setGravity(m_gravity);
    m_particleSystem->setCollideSpring(m_collideSpring);
    m_particleSystem->setCollideDamping(m_collideDamping);
    m_particleSystem->setCollideShear(m_collideShear);
    m_particleSystem->setCollideAttraction(m_collideAttraction);

    m_particleSystem->update(m_timestep);
}

}