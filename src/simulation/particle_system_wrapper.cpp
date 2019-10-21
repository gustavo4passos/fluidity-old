#include "particle_system_wrapper.h"
#include <random>

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

auto ParticleSystemWrapper::AddSphere() -> void
{
    int ballr = 1;
    float pr = m_particleSystem->getParticleRadius();
    float tr = pr + (pr * 2.f) * ballr;
    float pos[4], vel[4];
    pos[0] = -2.f + tr + (rand() / (float)RAND_MAX) * (2.f - tr * 2.f);
    pos[1] = 2.f - tr;
    pos[2] = -1.f + tr + (rand() / (float)RAND_MAX) * (2.f - tr * 2.f);
    pos[3] = 0.f;

    vel[0] = vel[1] = vel[2] = vel[3] = 0.f;

    m_particleSystem->addSphere(0, pos, vel, 10, pr * 2.f);
}

auto ParticleSystemWrapper::Update() -> void
{
    if(!m_paused)
    {
        m_particleSystem->setIterations(m_iterations);
        m_particleSystem->setDamping(m_damping);
        m_particleSystem->setGravity(-m_gravity);
        m_particleSystem->setCollideSpring(m_collideSpring);
        m_particleSystem->setCollideDamping(m_collideDamping);
        m_particleSystem->setCollideShear(m_collideShear);
        m_particleSystem->setCollideAttraction(m_collideAttraction);

        m_particleSystem->update(m_timestep);
    }
}

}