#include <Pyre.hpp>

class TextLayer2D : public Pyre::Layer {
public:
    TextLayer2D();

    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate(float ts) override;
    void OnImGuiRender() override;
    void OnEvent(Pyre::Event& e) override;

private:
    Pyre::Ref<Pyre::VertexArray> m_SquareVA;
    Pyre::Ref<Pyre::Shader> m_Shader;

    Pyre::OrthographicCameraController m_CameraController;

    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};