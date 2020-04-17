#include <Pyre.hpp>

class TestLayer2D : public Pyre::Layer {
public:
    TestLayer2D();

    void OnAttach() override;
    void OnDetach() override;

    void Tick(float dt) override;
    void Draw(float alpha) override;
    void ImGuiDraw() override;
    void OnEvent(Pyre::Event& e) override;

private:
    Pyre::OrthographicCameraController m_CameraController;

    Pyre::Ref<Pyre::Texture2D> m_Texture;
    glm::vec4 m_SquareColor = { 0.8f, 0.3f, 0.6f, 1.0f };
};