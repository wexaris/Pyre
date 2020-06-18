#pragma once
#include <Pyre/Pyre.hpp>
#include <glm/glm.hpp>

struct ParticleProps {
    glm::vec2 Position;
    glm::vec2 Velocity, VelocityVariation;
    glm::vec4 ColorBegin, ColorEnd;
    float SizeBegin, SizeEnd, SizeVariation;
    float LifeTime = 1.0f;
};

class ParticleSystem {
public:
    ParticleSystem(uint32_t maxParticles = 100000);

    void Tick(float ts);
    void Draw(Pyre::OrthographicCamera& camera);
    void Emit(const ParticleProps& particleProps);

private:
    struct Particle {
        glm::vec2 Position;
        glm::vec2 Velocity;
        glm::vec4 ColorBegin, ColorEnd;
        float Rotation = 0.0f;
        float SizeBegin, SizeEnd;

        float LifeTime = 1.0f;
        float LifeRemaining = 0.0f;

        bool Active = false;
    };

    std::vector<Particle> m_ParticlePool;
    uint32_t m_PoolIndex;

    unsigned int m_QuadVA = 0;
    std::unique_ptr<Pyre::Shader> m_ParticleShader;
    int m_ParticleShaderViewProj, m_ParticleShaderTransform, m_ParticleShaderColor;
};