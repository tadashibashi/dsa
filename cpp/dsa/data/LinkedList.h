#pragma once

namespace dsa {
    template <typename T>
    class LinkedList {
    public:
        LinkedList();
        ~LinkedList();

        /**
         * Append a value to the end of the list
         * @param value
         * @return
         */
        LinkedList &append(T value);

        [[nodiscard]]
        size_t size() const;

        const T &operator[] (int idx) const;
    private:
        struct Node {
            explicit Node(T value): value { value }, next { nullptr } {}
            T value;
            Node *next;
        };

        Node *m_head;
    };
}

#include "LinkedList.inl"
