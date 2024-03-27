

#define NOMINMAX

#define HEALTHBAR_OFFSET 70
#define SCRWIDTH (1280 + (HEALTHBAR_OFFSET * 2))
#define SCRHEIGHT 720

#include <Windows.h>
// C++ headers
#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include <deque>
#include <queue>
#include <future>
#include <mutex>
#include <thread>
#include <filesystem>


#include <cinttypes>
#include <cmath>
#include <cstdio>
#include <cstdlib>

// Header for AVX, and every technology before it.
// If your CPU does not support this, include the appropriate header instead.
// See: https://stackoverflow.com/a/11228864/2844473
#include <immintrin.h>

// clang-format off

// "Leak" common namespaces to all compilation units. This is not standard
// C++ practice but a mere simplification for this small project.
//using namespace std;

#include "surface.h"


// clang-format on
