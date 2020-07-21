#pragma once
#include <memory>
/* wrappers for stuff like smart pointers because I'm tired of writing them out all the time :') */
namespace Anim
{
template <typename T>
using SPtr = std::shared_ptr<T>;
template <typename T>
using UPtr = std::unique_ptr<T>;
template<typename T>
using WPtr = std::weak_ptr<T>;

using uint32 = uint32_t;
using uint64 = uint64_t;
}