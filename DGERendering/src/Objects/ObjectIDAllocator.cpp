#include "DGERendering/Objects/ObjectIDAllocator.h"

std::atomic<DGERendering::Objects::ObjectID> DGERendering::Objects::ObjectIDAllocator::m_next_id{0};

DGERendering::Objects::ObjectID DGERendering::Objects::ObjectIDAllocator::alloc()
{
    std::atomic<ObjectID> new_object_ret = m_next_id.load();
    m_next_id++;
    if (m_next_id >= k_invalid_object_id)
    {
        // Console::GetInstance()->AddError("global id overflow");
    }
    return new_object_ret;
}