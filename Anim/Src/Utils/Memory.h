#pragma once
#include <memory>

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