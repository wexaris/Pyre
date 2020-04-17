#pragma once

namespace Pyre {

    class Drawable {
    public:
        virtual void Draw(float alpha) = 0;
    };

    class ImGuiDrawable {
    public:
        virtual void ImGuiDraw() = 0;
    };

}