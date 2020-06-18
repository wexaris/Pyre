#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>

#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Pyre/Core/Base.hpp"
#include "Pyre/Core/Log.hpp"
#include "Pyre/Debug/Instrumentor.hpp"

#ifdef PYRE_PLATFORM_WINDOWS
    #include <Windows.h>
#endif