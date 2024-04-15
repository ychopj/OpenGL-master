#pragma once

#include <atomic>
namespace DGERendering::Objects
{
    using ObjectID = std::size_t;

    constexpr ObjectID k_invalid_object_id = SIZE_MAX;

    class ObjectIDAllocator
    {
    public:
        static ObjectID alloc();

    private:
        static std::atomic<ObjectID> m_next_id;
    };
} // namespace DGERendering::Objects
