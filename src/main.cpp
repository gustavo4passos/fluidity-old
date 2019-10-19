#include "utils/logger.h"
#include "renderer/shader.h"
#include "renderer/window.h"
#include "simulation/particleSystem.h"

extern "C" void cudaInit(int argc, char **args);

void update_particle_system(ParticleSystem* p)
{
    p->setIterations(1);
    p->setDamping(1.f);
    p->setGravity(0.0003f);
    p->setCollideSpring(.5f);
    p->setCollideDamping(0.02f);
    p->setCollideShear(0.1f);
    p->setCollideAttraction(0.0f);
    p->update(0.5f);
}

int main(int argc, char* args[]) 
{
    Window window = Window("OpenGL Fluid Rendering", 800, 600, 4, 5, true, false);
    if(!window.Init()) 
    {
        LOG_ERROR("Unable to create window..");
        return 0;
    }
    else LOG_WARNING("Window successfully created.");

    cudaInit(argc, args);
    ParticleSystem* particleSystem = new ParticleSystem(16000, {200, 200, 200}, true);
    particleSystem->reset(ParticleSystem::CONFIG_GRID);

    bool running = true;
    while(running) 
    {
        SDL_Event e;
        while(SDL_PollEvent(&e)) 
        {
            if(e.type == SDL_QUIT || (e.type == SDL_KEYUP && e.key.keysym.sym  == SDLK_ESCAPE))
            {
                running = false;
            }
        }

        update_particle_system(particleSystem);
        particleSystem->dumpParticles(0, 1);
        glClearColor(.4f, .4f, .4f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        window.Swap();
    }
    return 0;
}