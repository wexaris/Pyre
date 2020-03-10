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
    Pyre::OrthographicCameraController m_CameraController;

    Pyre::Ref<Pyre::Texture2D> m_Texture;
    glm::vec4 m_SquareColor = { 0.8f, 0.3f, 0.6f, 1.0f };
};