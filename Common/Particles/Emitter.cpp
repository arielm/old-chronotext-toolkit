#include "Emitter.h"
#include "TextureHelper.h"
#include "Constants.h"
#include "Utils.h"

using namespace std;
using namespace ci;

namespace chronotext
{
    Emitter::Emitter(MasterClock *masterClock, TextureAtlas *atlas, const EmitterParams &params, uint32_t seed)
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
    spawnEnabled(true),
    accum(0),
    total(0)
    {
        clock.setTime(0);
        clock.start();
        
        for (vector<string>::const_iterator it = params.spritePaths.begin(); it != params.spritePaths.end(); ++it)
        {
            sprites.push_back(atlas->getSprite(*it));
        }
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
                if (spawnEnabled && !spawnEnded)
                {
                    if (params.spawnDuration == std::numeric_limits<double>::min())
                    {
                        int quantity = params.spawnRate;
                        total = quantity;
                        
                        for (int i = 0; i < quantity; i++)
                        {
                            spawnParticle(now);
                        }
                        
                        spawnEnded = true;
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
                                spawnRate *= params.spawnCurve(t);
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
                                    spawnParticle(now);
                                }
                            }
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
                        it->scale = it->scale0 * it->scaleCurve(t);
                        it->alpha = it->alpha0 * it->alphaCurve(t);
                        
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
            gl::translate(it->position);
            
            if (params.positionLocked)
            {
                gl::translate(position);
            }
            
            glRotatef(it->angle, 0, 0, 1);
            glScalef(it->scale * scale.x, it->scale * scale.y, 1);

            glColor4f(1, 1, 1, it->alpha);
            it->sprite->drawFromCenter();
            glPopMatrix();
        }
    }
    
    void Emitter::setSpawnEnabled(bool b)
    {
        spawnEnabled = b;
    }
    
    void Emitter::spawnParticle(double now)
    {
        Sprite *sprite = sprites[random.nextInt(sprites.size())];

        // ---
        
        Vec2f particlePosition;
        float radius = random.nextFloat(params.radius.first, params.radius.second);
        
        if (radius > 0)
        {
            float direction = random.nextFloat(0, 360);
            particlePosition = Vec2f(math<float>::cos(direction * D2R) * radius, math<float>::sin(direction * D2R) * radius);
        }
        else
        {
            particlePosition = Vec2f::zero();
        }
        
        if (!params.positionLocked)
        {
            particlePosition += position;
        }
        
        // ---

        Vec2f particleVelocity;
        float speed = random.nextFloat(params.speed.first, params.speed.second);
            
        if (speed > 0)
        {
            float direction = random.nextFloat(params.direction.first, params.direction.second);
            particleVelocity = Vec2f(math<float>::cos(direction * D2R) * speed, math<float>::sin(direction * D2R) * speed);
        }
        else
        {
            particleVelocity = Vec2f::zero();
        }
        
        // ---
        
        float lifetime = random.nextFloat(params.lifetime.first, params.lifetime.second);
        float angle = random.nextFloat(params.angle.first, params.angle.second);
        float angularVelocity = random.nextFloat(params.angularVelocity.first, params.angularVelocity.second);
        float scale = random.nextFloat(params.scale.first, params.scale.second);
        float alpha = random.nextFloat(params.alpha.first, params.alpha.second);
        
        // ---
        
        float mass;
        
        if (params.massRelativeToScale)
        {
            mass = scale * params.massFactor;
        }
        else
        {
            mass = random.nextFloat(params.mass.first, params.mass.second);
        }
        
        // ---
        
        particles.push_back(Particle(sprite, particlePosition, particleVelocity, now, lifetime, mass, angle, angularVelocity, scale, params.scaleCurve, alpha, params.scaleCurve));
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
        float f1 = 1 - params.friction;
        float f2 = 2 - params.friction;
        float dt2 = dt * dt;

        for (list<Particle>::iterator it = particles.begin(); it != particles.end(); ++it)
        {
            const Vec2f tmp = it->position;
            it->position = f2 * it->position - f1 * it->previousPosition + it->acceleration * dt2;
            it->previousPosition = tmp;
        }
    }
    
    void Emitter::satisfyConstraints()
    {}
}
