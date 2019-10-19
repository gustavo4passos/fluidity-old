#include "utils/logger.h"
#include "renderer/fluid_renderer.h"
#include "renderer/window.h"
#include "simulation/particle_system_wrapper.h"

int main(int argc, char* args[]) 
{
    Window window = Window("OpenGL Fluid Rendering", 800, 600, 4, 5, true, false);
    fluidity::FluidRenderer renderer;
    fluidity::ParticleSystemWrapper ps;

    if(!window.Init()) 
    {
        LOG_ERROR("Unable to create window..");
        return 0;
    }
    else LOG_WARNING("Window successfully created.");

    if(!ps.Init(argc, args))
    {
        LOG_ERROR("Unable to initialize particle system.");
        return 0;
    }
    else LOG_WARNING("Particle system successfully initialized.");


    bool running = true;
    while(running) 
    {
        SDL_Event e;
        while(SDL_PollEvent(&e)) 
        {
            if(e.type == SDL_QUIT) running = false;
            if(e.type == SDL_KEYUP)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    {
                        running = false;
                    } break;
                }
            }
        }

        renderer.SetClearColor(.3f, .3f, .7f, 1.f);
        renderer.Clear();

        ps.Update();
        ps.GetParticleSystem()->dumpParticles(0, 1);

        window.Swap();
    }

    return 0;
}