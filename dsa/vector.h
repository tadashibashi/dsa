#pragma once
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <utility>

template <typename T>
class vector {
public:
    using iterator = T *;
    using const_iterator = const T *;

    explicit vector(size_t reservedSpace = 16) : m_begin(), m_end(), m_max()
    {
        if (reservedSpace == 0)
            reservedSpace = 1;

        m_begin = (T *)std::malloc(sizeof(T) * reservedSpace);
        m_end = m_begin;
        m_max = m_begin + reservedSpace;
    }

    ~vector()
    {
        clear();
        std::free(m_begin);
    }

    [[nodiscard]]
    size_t size() const { return m_end - m_begin; }

    [[nodiscard]]
    bool empty() const { return m_end == m_begin; }

    [[nodiscard]]
    size_t capacity() const { return m_max - m_begin; }

    // Erase one element by iterator
    void erase(iterator it)
    {
        // check that iterator is in range
        if (it < m_begin || it >= m_end)
            return;

        it->~T();

        // shift memory over
        auto next = it + 1;
        if (next < m_end)
            std::memcpy(it, next, sizeof(T) * (m_end - next));
        --m_end;
    }

    /// Erase elements from start (inclusive) up until end (exclusive)
    void erase(iterator start, iterator end)
    {
        if (start < m_begin || start >= m_end || end <= start)
            return;
        if (end > m_end)
            end = m_end;

        const auto count = end - start;

        for (auto it = start; it < end; ++it)
            it->~T();

        // move memory between end and m_end to start
        if (end < m_end)
        {
            std::memcpy(start, end, sizeof(T) * (m_end - end));
        }

        m_end -= count;
    }

    /// Constructs an object in-place at the back of the container
    template <typename ...TArgs>
    iterator emplace_back(TArgs &&...args)
    {
        if (const auto cap = capacity(); size() + 1 > cap)
            this->realloc(cap * 2 + 1);

        return (iterator)new (m_end++) T(std::forward<TArgs>(args)...);
    }

    /// Makes a copy of the object and pushes it to the back of the container
    iterator push_back(T &obj)
    {
        return emplace_back(obj);
    }

    void clear()
    {
        for (auto ptr = m_begin, ptrEnd = m_end; ptr < ptrEnd; ++ptr)
            ptr->~T();
        m_end = m_begin;
    }

    T &operator[](size_t index) { return m_begin[index]; }
    const T &operator[](size_t index) const { return m_begin[index]; }

    T &at(size_t index)
    {
        if (index >= size())
            throw std::range_error("vector::at: index exceeds valid size");
        return m_begin[index];
    }
    const T &at(size_t index) const
    {
        if (index >= size())
            throw std::range_error("vector::at: index exceeds valid size");
        return m_begin[index];
    }

    void shrink(size_t newSize)
    {
        if (const auto curSize = size(); newSize < curSize)
            newSize = curSize;
        if (capacity() <= newSize)
            return;

        this->realloc(newSize);
    }

    void reserve(size_t elemCount)
    {
        // todo: expand to a larger size than requested?

        realloc(elemCount);
    }

    iterator begin() { return m_begin; }
    iterator end() { return m_end; }
    const_iterator begin() const { return m_begin; }
    const_iterator end() const { return m_end; }

private:
    void realloc(size_t newSize)
    {
        const auto oldSize = size();
        if (newSize <= oldSize) return;
        auto newMem = (T *)std::malloc(sizeof(T) * newSize);
        try
        {
            std::memcpy(newMem, m_begin, sizeof(T) * size());
        }
        catch(...)
        {
            std::free(newMem);
            throw;
        }

        std::free(m_begin);
        m_begin = newMem;
        m_end = newMem + oldSize;
        m_max = newMem + newSize;
    }

    T *m_begin, *m_end, *m_max;
};