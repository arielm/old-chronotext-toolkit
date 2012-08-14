#include "Emitter.h"
#include "TextureHelper.h"
#include "Constants.h"
#include "Utils.h"

using namespace std;
using namespace ci;

namespace chronotext
{
    Emitter::Emitter(MasterClock *masterClock, const EmitterParams &params, uint32_t seed)
    :
    random(Rand(seed)),
    clock(Clock(masterClock)),
    params(params),
    controller(NULL),
    controllerIsOwned(false),
    data(NULL),
    dataIsOwned(false),
    position(Vec2f::zero()),
    ended(false),
    spawnEnded(false),
    accum(0),
    total(0)
    {
        clock.setTime(0);
        clock.start();
    }
    
    Emitter::~Emitter()
    {
        if (controller && controllerIsOwned)
        {
            delete controller;
        }
        
        if (data && dataIsOwned)
        {
            delete data;
        }
        
        DLOG("Emitter DELETED");
    }
    
    void Emitter::setController(EmitterController *controller, bool controllerIsOwned)
    {
        this->controller = controller;
        this->controllerIsOwned = controllerIsOwned;
    }
    
    void Emitter::setData(EmitterData *data, bool dataIsOwned)
    {
        this->data = data;
        this->dataIsOwned = dataIsOwned;
    }
    
    EmitterData* Emitter::getData()
    {
        return data;
    }
    
    bool Emitter::hasEnded()
    {
        return ended;
    }

    void Emitter::update(float dt)
    {
        double now = clock.getTime();
        
        if (controller)
        {
            controller->emitterWillUpdate(this, dt, now);
        }
        
        if (!ended)
        {
            if (now > params.duration)
            {
                ended = true;
                particles.clear();
                
                if (controller)
                {
                    controller->emitterHasEnded(this);
                }
            }
            else
            {
                float spawnRate = params.spawnRate;
                
                if (params.spawnDuration != std::numeric_limits<double>::max())
                {
                    double t = now / params.spawnDuration;
                    
                    if (t > 1)
                    {
                        spawnEnded = true;
                    }
                    else
                    {
                        spawnRate *= params.spawnFunction(t);
                    }
                }
                
                if (!spawnEnded)
                {
                    accum += random.nextFloat(spawnRate * dt * 2);
                    
                    if (accum >= 1)
                    {
                        int quantity = math<float>::floor(accum);
                        accum -= quantity;
                        total += quantity;
                        
                        for (int i = 0; i < quantity; i++)
                        {
                            addParticle(now);
                        }
                    }
                }
                
                for (list<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
                {
                    double elapsed = now - it->creationTime;
                    double t = elapsed / it->lifetime;
                    
                    if (t > 1)
                    {
                        it->remove = true;
                    }
                    else
                    {
                        it->scale = it->scale0 * it->scaleFunction(t);
                        it->alpha = it->alpha0 * it->alphaFunction(t);
                        
                        it->angle = math<float>::fmod(it->angle0 + it->angularVelocity * elapsed, 360);
                    }
                }
                
                particles.remove_if(Particle::shouldBeRemoved);
                
                // ---
                
                accumulateForces();
                integrate(dt);
                satisfyConstraints();
            }
        }
    }
    
    void Emitter::draw(const Vec2f &scale)
    {
        for (list<Particle>::const_iterator it = particles.begin(); it != particles.end(); ++it)
        {
            glPushMatrix();
            gl::translate(position + it->position);
            glRotatef(it->angle, 0, 0, 1);
            glScalef(it->scale * scale.x, it->scale * scale.y, 1);

            glColor4f(1, 1, 1, it->alpha);
            it->sprite->drawFromCenter();
            glPopMatrix();
        }
    }
    
    void Emitter::addSprite(Sprite *sprite)
    {
        sprites.push_back(sprite);
    }
    
    void Emitter::addParticle(double now)
    {
        Sprite *sprite = sprites[random.nextInt(sprites.size())];
        
        float direction = random.nextFloat(params.direction0, params.direction1);
        float speed = random.nextFloat(params.speed0, params.speed1);
        Vec2f velocity = Vec2f(math<float>::cos(direction * D2R) * speed, math<float>::sin(direction * D2R) * speed);
        
        float lifetime = random.nextFloat(params.lifetime0, params.lifetime1);
        float angle = random.nextFloat(params.angle0, params.angle1);
        float angularVelocity = random.nextFloat(params.angularVelocity0, params.angularVelocity1);
        float scale = random.nextFloat(params.scale0, params.scale1);
        float alpha = random.nextFloat(params.alpha0, params.alpha1);
        
        // ---
        
        float mass;
        
        if (params.massRelativeToScale)
        {
            mass = scale * params.massFactor;
        }
        else
        {
            mass = random.nextFloat(params.mass0, params.mass1);
        }
        
        // ---
        
        particles.push_back(Particle(sprite, Vec2f::zero(), velocity, now, lifetime, mass, angle, angularVelocity, scale, params.scaleFunction, alpha, params.alphaFunction));
    }
    
#pragma mark ---------------------------------------- VERLET ----------------------------------------
    
    void Emitter::accumulateForces()
    {
        for (list<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
        {
            it->acceleration = it->mass * params.gravity;
        }
    }
    
    void Emitter::integrate(float dt)
    {
        for (list<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
        {
            float f1 = 1 - params.friction;
            float f2 = 2 - params.friction;
            float dt2 = dt * dt;
            
            const Vec2f tmp = it->position;
            it->position = f2 * it->position - f1 * it->previousPosition + it->acceleration * dt2;
            it->previousPosition = tmp;
        }
    }
    
    void Emitter::satisfyConstraints()
    {}
}
