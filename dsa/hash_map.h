#pragma once
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <tuple>

namespace detail {
    template <typename T>
    struct DefaultEquals {
        [[nodiscard]]
        bool operator()(const T &a, const T &b)
        {
            return a == b;
        }
    };

    template <typename T>
    struct DefaultHash {
        size_t operator()(const T &key)
        {
            return std::hash<T>{}(key);
        }
    };
}

/// Flat hash map, using linear probing to resolve collisions
template<typename K, typename T, typename Equals = detail::DefaultEquals<K>, typename Hasher = detail::DefaultHash<K>>
class hash_map {
public:
    using kvp = std::pair<const K, T>;
    class iterator {
    public:
        iterator() : ptr(), map() { }
        iterator(kvp *ptr, hash_map *map) : ptr(ptr), map(map) { }

        kvp *operator->() { return ptr; }
        const kvp *operator->() const { return ptr; }

        iterator operator++()   // ++prefix
        {
            auto lastPtr = ptr;

            // find next valid
            for (auto cur = ptr + 1, end = map->m_buckets + map->m_nBuckets; cur < end; ++cur)
            {
                if (ptrValid(cur, map))
                {
                    ptr = cur;
                    return iterator(lastPtr, map);
                }
            }

            ptr = map->m_buckets + map->m_nBuckets;
            return iterator(lastPtr, map);
        }

        iterator &operator++(int) // postfix++
        {
            // find next valid
            for (auto cur = ptr + 1, end = map->end(); cur < end; ++cur)
            {
                if (ptrValid(cur, map))
                {
                    ptr = cur;
                    return *this;
                }
            }

            ptr = map->end();
            return *this;
        }

        iterator operator--()   // --prefix
        {
            auto lastPtr = ptr;

            // find previous valid
            for (auto cur = ptr - 1, beg = map->begin(); cur >= beg; --cur)
            {
                if (ptrValid(cur, map))
                {
                    ptr = cur;
                    return iterator(lastPtr, map);
                }
            }

            ptr = map->end();
            return iterator(lastPtr, map);
        }

        iterator &operator--(int) // postfix--
        {
            // find previous valid
            for (auto cur = ptr - 1, beg = map->begin(); cur >= beg; --cur)
            {
                if (ptrValid(cur, map))
                {
                    ptr = cur;
                    return *this;
                }
            }

            ptr = map->end();
            return *this;
        }

        kvp &operator *() { return *ptr; }

        [[nodiscard]] bool operator==(const iterator &other) const
        {
            return other.ptr == ptr;
        }

        [[nodiscard]] bool operator!=(const iterator &other) const
        {
            return other.ptr != ptr;
        }

        [[nodiscard]] bool isValid() const
        {
            return ptrValid(ptr, map);
        }

        [[nodiscard]] static bool ptrValid(kvp *ptr, hash_map *map)
        {
            return ptr && ptr >= map->m_buckets && ptr < map->m_buckets + map->m_nBuckets && !ptrNull(ptr);
        }

        [[nodiscard]] static bool ptrNull(const kvp *ptr)
        {
            static const char s_testNull[sizeof(kvp)] = {0};
            return std::memcmp(ptr, s_testNull, sizeof(kvp)) == 0;
        }
    private:
        friend class hash_map;
        kvp *ptr;
        hash_map *map;
    };

    explicit hash_map(size_t buckets = 16, float loadFactor = .75f) : m_buckets(), m_nBuckets(buckets), m_alive(),
        m_loadFactor(loadFactor)
    {
        m_buckets = (kvp *)std::calloc(m_nBuckets, sizeof(kvp));
    }

    ~hash_map()
    {
        clear();
        std::free(m_buckets);
    }

    [[nodiscard]] size_t size() const { return m_alive; }
    [[nodiscard]] bool empty() const { return m_alive == 0; }
    [[nodiscard]] size_t bucket_count() const { return m_nBuckets; }

    /// Erase all kvps inside the hash_map
    void clear()
    {
        for (size_t i = 0; i < m_nBuckets; ++i)
        {
            auto it = m_buckets + i;
            if (iterator::ptrValid(it, this))
            {
                it->~kvp();
            }
        }

        std::memset(m_buckets, 0, sizeof(kvp) * m_nBuckets);
        m_alive = 0;
    }

    /// Erase a kvp by key
    /// @returns number of elements deleted (1 or 0)
    int erase(const K &key)
    {
        return erase(find(key));
    }

    /// Erase a kvp by iterator
    int erase(const iterator &it)
    {
        if (it.map == this && it.isValid())
        {
            it.ptr->~kvp();
            std::memset(it.ptr, 0, sizeof(kvp));
            --m_alive;
            return 1;
        }

        return 0;
    }

    /// Add a key value pair to the hash_map. Replaces the object at the key if it already exists.
    /// @returns an iterator to the object that was created
    template <typename ...TArgs>
    iterator emplace(const K &key, TArgs &&...args)
    {
        if ((float)(m_alive + 1) / m_nBuckets > m_loadFactor)
        {
            rehash(m_nBuckets * 2 + 1);
        }

        auto kvp = findVacantBucket(key, m_buckets, m_nBuckets);
        if (iterator::ptrNull(kvp))
        {
            new (kvp) std::pair<const K, T>( // use piecewise construction to avoid multiple copies
                std::piecewise_construct,
                std::forward_as_tuple(key),
                std::forward_as_tuple(std::forward<TArgs>(args)...)
                );
            ++m_alive;
        }
        else // duplicate key, overwrite it
        {
            kvp->second.~T();
            new (&kvp->second) T(std::forward<TArgs>(args)...);
        }

        return {kvp, this};
    }

    /// Returns iterator, or `end()` if entry was not found for key
    iterator find(const K&key)
    {
        auto index = hashKey(key, m_nBuckets);
        for (size_t i = 0; i < m_nBuckets; ++i)
        {
            auto curIndex = (i + index) % m_nBuckets;
            if (keysEqual(m_buckets[curIndex].first, key))
            {
                return {m_buckets + curIndex, this};
            }
        }

        return end(); // could not be found
    }

    bool rehash(size_t nBuckets)
    {
        if (nBuckets <= m_nBuckets)
            return false;
        auto buckets = (kvp *)std::calloc(nBuckets, sizeof(kvp));

        for (size_t i = 0; i < m_nBuckets; ++i)
        {
            auto curBucket = m_buckets + i;
            if (!iterator::ptrNull(curBucket))
            {
                if (auto newBucket = findVacantBucket(curBucket->first, buckets, nBuckets)) // Failing this would be an internal logic problem
                    new (newBucket) std::pair<const K, T>(curBucket->first, std::move(curBucket->second));
                else
                    printf("Critical error: failed to find valid hash while rehashing\n");
            }
        }

        // Done, commit results
        std::free(m_buckets);
        m_buckets = buckets;
        m_nBuckets = nBuckets;
        return true;
    }

    /// Find the first valid iterator or end() if none available.
    [[nodiscard]] iterator begin()
    {
        for (auto cur = m_buckets, end = m_buckets + m_nBuckets; cur < end; ++cur)
        {
            if (iterator::ptrValid(cur, this)) // found a valid ptr
            {
                return {cur, this};
            }
        }

        return end(); // none found
    }
    [[nodiscard]] iterator end() { return {m_buckets + m_nBuckets, this}; }

private: // Helpers
    [[nodiscard]] static size_t hashKey(const K &key, size_t nBuckets) { return Hasher{}(key) % nBuckets; }
    [[nodiscard]] static bool keysEqual(const K &a, const K &b) { return Equals{}(a, b); }

    [[nodiscard]] kvp *findVacantBucket(const K &key, kvp *buckets, size_t nBuckets)
    {
        auto index = hashKey(key, nBuckets);
        for (size_t i = 0; i < nBuckets; ++i) // use linear probing to find next open slot
        {
            auto &curBucket = buckets[(i + index) % nBuckets];
            if (iterator::ptrNull(&curBucket) || keysEqual(curBucket.first, key))
            {
                return &curBucket;
            }
        }

        // TODO: should throw here? internal logic error.
        return nullptr;
    }

private: // Members
    kvp *m_buckets;
    size_t m_nBuckets;
    size_t m_alive;
    float m_loadFactor;
};
