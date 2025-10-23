#pragma once
#include <cstdint>
#include <bitset>
#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>

using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 10000;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;