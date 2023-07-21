#pragma once

namespace dsa {
    template <typename T>
    class LinkedList {
        struct Node;
    public:
        LinkedList();
        ~LinkedList();

        /**
         * time: O(N)
         * Append a value to the end of the list
         * @param value
         * @return
         */
        LinkedList<T> &append(T value);

        /**
         *
         */
        LinkedList<T> &insert(int pos, T value);

        LinkedList<T> &reverse();

        /**
         * time: O(N)
         * @return the length of the list in contained items
         */
        [[nodiscard]]
        size_t size() const;

        /**
         * time: O(1)
         * @return whether list is empty or contains items
         */
        [[nodiscard]]
        bool empty() const;

        [[nodiscard]]
        const T &operator[] (int idx) const;

    private:
        [[nodiscard]]
        const Node *nodeAt(int idx) const;
        [[nodiscard]]
        Node *nodeAt(int idx);
        [[nodiscard]]
        const Node *lastNode() const;
        [[nodiscard]]
        Node *lastNode();
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
