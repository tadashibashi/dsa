#pragma once
#include "LinkedList.h"

#include <stdexcept>
#include <utility>

namespace dsa {
    template<typename T>
    LinkedList<T>::LinkedList(): m_head(nullptr) { }

    template<typename T>
    LinkedList<T>::~LinkedList()
    {
        // clean up each node
        for (auto n = m_head; n != nullptr; )
        {
            const auto temp = n;
            n = n->next;
            delete temp;
        }
    }

    template <typename T>
    LinkedList<T> &LinkedList<T>::append(T value)
    {
        if (!m_head) {
            m_head = new Node(std::move(value));
        } else {
            Node *cur = m_head;

            while (cur->next)
                cur = cur->next;
            cur->next = new Node(std::move(value));
        }

        return *this;
    }

    template<typename T>
    LinkedList<T> &LinkedList<T>::insert(int pos, T value)
    {
        // beginning of list
        if (pos == 0)
        {
            if (!m_head)
                m_head = new Node(std::move(value));
            else
            {
                auto newNode = new Node(std::move(value));
                newNode->next = m_head;
                m_head = newNode;
            }
        }
        else
        {   // mid or end of list
            auto newNode = new Node(std::move(value));
            auto prevNode = nodeAt(pos - 1);
            newNode->next = prevNode->next;
            prevNode->next = newNode;
        }

        return *this;
    }


    template<typename T>
    LinkedList<T> &LinkedList<T>::reverse()
    {
        Node *prev = nullptr;
        auto cur = m_head;
        while (cur) {
            auto temp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = temp;
        }

        m_head = prev;
        return *this;
    }


    template<typename T>
    size_t LinkedList<T>::size() const
    {
        if (!m_head) return 0;

        size_t count = 0;
        Node *cur = m_head;
        while (cur) {
            cur = cur->next;
            ++count;
        }

        return count;
    }

    template<typename T>
    bool LinkedList<T>::empty() const
    {
        return !m_head;
    }

    template<typename T>
    const T &LinkedList<T>::operator[](int idx) const
    {
        return nodeAt(idx)->value;;
    }

    template<typename T>
    const typename LinkedList<T>::Node *LinkedList<T>::nodeAt(int idx) const
    {
        if (idx < 0 || !m_head)
            throw std::out_of_range("[LinkedList] idx is out of range");

        auto cur = m_head;
        while (idx)
        {
            if (!cur)
                throw std::out_of_range("[LinkedList] idx is out of range");
            cur = cur->next;
            --idx;
        }

        return cur;
    }

    template<typename T>
    typename LinkedList<T>::Node *LinkedList<T>::nodeAt(int idx)
    {
        return const_cast<LinkedList<T>::Node *>(const_cast<const LinkedList<T> *>(this)->nodeAt(idx));
    }

    template<typename T>
    const typename LinkedList<T>::Node *LinkedList<T>::lastNode() const
    {
        if (!m_head) return nullptr;
        auto cur = m_head;
        while (cur->next)
            cur = cur->next;
        return cur;
    }

    template<typename T>
    typename LinkedList<T>::Node *LinkedList<T>::lastNode()
    {
        return const_cast<LinkedList<T>::Node *>(const_cast<const LinkedList<T> *>(this)->lastNode());
    }
}
