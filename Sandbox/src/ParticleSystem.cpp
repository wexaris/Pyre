#include "ParticleSystem.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

ParticleSystem::ParticleSystem(uint32_t maxParticles) :
    m_PoolIndex(maxParticles - 1)
{
    m_ParticlePool.resize(maxParticles);
}

void ParticleSystem::Tick(float dt) {
    for (auto& particle : m_ParticlePool) {
        if (!particle.Active)
            continue;

        if (particle.LifeRemaining <= 0.0f) {
            particle.Active = false;
            continue;
        }

        particle.LifeRemaining -= dt;
        particle.Position += particle.Velocity * dt;
        particle.Rotation += 0.01f * dt;
    }
}

void ParticleSystem::Draw(Pyre::OrthographicCamera& camera) {
    Pyre::Renderer2D::BeginScene(camera);
    for (auto& particle : m_ParticlePool) {
        if (!particle.Active)
            continue;

        // Fade away particles
        float life = particle.LifeRemaining / particle.LifeTime;
        glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
        //color.a = color.a * life;

        float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);
        glm::vec3 pos = { particle.Position, 0.5f };

        Pyre::Renderer2D::DrawRotatedQuad(pos, particle.Rotation, { size, size }, color);
    }
    Pyre::Renderer2D::EndScene();
}

void ParticleSystem::Emit(const ParticleProps& particleProps) {
    Particle& particle = m_ParticlePool[m_PoolIndex];
    particle.Active = true;
    particle.Position = particleProps.Position;
    particle.Rotation = Pyre::Random::Float(0.0, 2.0) * 2.0f * glm::pi<float>();

    // Velocity
    particle.Velocity = particleProps.Velocity;
    particle.Velocity.x += particleProps.VelocityVariation.x * (Pyre::Random::Float(0.0, 2.0) - 0.5f);
    particle.Velocity.y += particleProps.VelocityVariation.y * (Pyre::Random::Float(0.0, 2.0) - 0.5f);

    // Color
    particle.ColorBegin = particleProps.ColorBegin;
    particle.ColorEnd = particleProps.ColorEnd;

    particle.LifeTime = particleProps.LifeTime;
    particle.LifeRemaining = particleProps.LifeTime;
    particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (Pyre::Random::Float(0.0, 2.0) - 0.5f);
    particle.SizeEnd = particleProps.SizeEnd;

    --m_PoolIndex;
    m_PoolIndex %= m_ParticlePool.size();
}