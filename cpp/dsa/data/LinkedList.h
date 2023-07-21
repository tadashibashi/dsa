#pragma once
#include <utility>

namespace dsa {
    template <typename T>
    class LinkedList {
        struct Node {
            explicit Node(T value): value { value }, next { nullptr } {}
            T value;
            Node *next;
        };

        Node *m_head;
    public:
        LinkedList(): m_head(nullptr) {

        }

        LinkedList &append(T value) {
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

        [[nodiscard]]
        size_t size() const {
            if (!m_head) return 0;

            size_t count = 0;
            Node *cur = m_head;
            while (cur) {
                cur = cur->next;
                ++count;
            }

            return count;
        }

        ~LinkedList() {
            // clean up each node
            for (auto n = m_head; n != nullptr; ) {
                const auto temp = n;
                n = n->next;
                delete temp;
            }
        }

        const T &operator[] (int idx) const {
            if (idx < 0 || !m_head)
                throw std::out_of_range("[LinkedList] idx is out of range");

            auto cur = m_head;
            while (idx) {
                if (!cur)
                    throw std::out_of_range("[LinkedList] idx is out of range");
                cur = cur->next;
                --idx;
            }

            return cur->value;
        }
    };
}

