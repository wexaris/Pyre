#include "pyrepch.hpp"
#include "Pyre/Core/Layer.hpp"

namespace Pyre {

    Layer::Layer(const std::string& name) :
        m_Name(name), m_Enabled(true)
    { 
    }

}