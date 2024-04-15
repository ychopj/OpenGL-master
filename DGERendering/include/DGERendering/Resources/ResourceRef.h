#pragma once
#include <vector>
#include <algorithm>

using namespace std;

namespace DGERendering::Resources
{
    template<class T>
    class EditorResource
    {
    public:
        vector<T> m_references;

        void AddRef(T p_refTarget) { m_references.push_back(p_refTarget); }
        void RemoveRef(T p_removeTarget)
        {
            auto new_end = std::remove(m_references.begin(), m_references.end(), p_removeTarget);
            m_references.erase(new_end, m_references.end());
        }
    };

} // namespace DGERendering::Resources