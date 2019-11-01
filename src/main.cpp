#include "utils/logger.h"
#include "renderer/fluid_renderer.h"
#include "renderer/fluid_surfaces.h"
#include "renderer/window.h"
#include "simulation/particle_system_wrapper.h"

int main(int argc, char* args[]) 
{
    const unsigned int WINDOW_WIDTH = 1366;
    const unsigned int WINDOW_HEIGHT = 768;
    Window window = Window("Fluidity", WINDOW_WIDTH, WINDOW_HEIGHT, 4, 5, true, false);
    fluidity::ParticleSystemWrapper ps;
    fluidity::FluidRenderer* renderer;
    fluidity::FluidSurfaces fs(WINDOW_WIDTH, WINDOW_HEIGHT);

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

    renderer = new fluidity::FluidRenderer(966.f / 544.f, 6.f);

    if(!fs.Init()){
        LOG_ERROR("Unable to initialized fluid surfaces.");
        return 0;
    }

    bool running = true;
    bool paused = false;
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

                    case SDLK_m:
                    {
                        ps.AddSphere();
                    } break;

                    case SDLK_g:
                    {
						ps.GetParticleSystem()->reset(ParticleSystem::CONFIG_GRID);
                    } break;

					case SDLK_r:
					{
						ps.GetParticleSystem()->reset(ParticleSystem::CONFIG_RANDOM);
					} break;

                    case SDLK_SPACE:
                    {
                        paused = !paused;
                        paused? ps.Pause() : ps.Resume();
                    } break;
                    default: break;
                }
            }
        }

        renderer->SetClearColor(.3f, .3f, .5f, 1.f);
        renderer->Clear();

        ps.Update();
        renderer->SetNumberOfParticles(ps.GetParticleSystem()->getNumParticles());
        renderer->SetVAO(ps.GetParticleSystem()->getCurrentPosVao());
        renderer->Render();

        window.Swap();
    }

    return 0;
}
