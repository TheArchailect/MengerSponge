#pragma once
// engine includes
#include <fstream>
#include <sstream>
#include <sdl/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <glad/khrplatform.h>
// std includes
#include <string>
#include <future>
#include <iostream>
#include <map>
#include <vector>
// enum / state definitions
enum OVERLAY_STATE {
    S_FULL_HUD,
    S_FPS_ONLY,
};