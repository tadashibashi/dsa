import unittest

class Node:
    def __init__(self, val: any, next=None):
        self.val = val
        self.next = next


class CircularList:
    def __init__(self):
        self.head = None

    def __eq__(self, other):
        """Compare one CircularList to another"""
        # head of either list is zero edge-case
        if not self.head:
            return not other.head
        elif not other.head:
            return not self.head

        p = self.head
        q = other.head

        while True:
            if p.val != q.val:
                return False

            p = p.next
            q = q.next
            if p.next is self.head or q.next is other.head:
                break

        # make sure both lists are at the end
        return p.next is self.head and q.next is other.head

    def __ne__(self, other):
        """Check unequality with another CircularList"""
        return not self.__eq__(other)

    def append(self, data):
        """Append new data to the end of the list"""
        if not self.head:
            self.head = Node(data)
            self.head.next = self.head # circular link
            return

        new_node = Node(data, self.head)
        last = self.head
        while last.next != self.head:
            last = last.next

        last.next = new_node

    def __repr__(self):
        """Render repl string representation"""
        cur = self.head
        if not cur:
            return "CircularList: []"

        outstr = "CircularList: ["
        while True:
            outstr += str(cur.val)

            if cur.next is not self.head:
                outstr += ", "
                cur = cur.next
            else:
                break

        outstr += "]"
        return outstr

    def __str__(self):
        return self.__repr__()

    def prepend(self, val):
        if not self.head:
            self.head = Node(val)
            self.head.next = self.head
            return

        last = self.head
        while last.next is not self.head:
            last = last.next

        new_node = Node(val, self.head)
        last.next = new_node # circular link
        self.head = new_node # shift in the new head

    def remove(self, val):
        if not self.head:
            return

        # find the node with val
        cur = self.head
        prev = None

        while True:
            if cur.val == val:
                break
            if cur.next == self.head:
                return # could not find node with key

            prev = cur
            cur = cur.next

        # determine if it's head or body/tail and act accordingly
        if cur is self.head: # head
            # get tail
            tail = self.head

            while tail.next is not self.head:
                tail = tail.next

            # replace head
            tail.next = self.head.next
            self.head = self.head.next

        else: # body or tail
            prev.next = cur.next

    def __len__(self):
        cur = self.head
        if not cur:
            return 0

        count = 1
        while cur.next != self.head:
            cur = cur.next
            count += 1

        return count

    def split_list(self):
        """Splits the list in half and returns the other half as
        another CircularList object."""

        new_list = CircularList()
        length = len(self)
        if length < 2:
            return new_list

        half_way = length // 2
        tail1 = None
        head2 = self.head
        for i in range(half_way):
            tail1 = head2
            head2 = head2.next

        tail1.next = self.head
        new_list.head = head2

        cur = head2
        while cur.next is not self.head:
            cur = cur.next

        cur.next = head2

        return new_list



class TestCircularList(unittest.TestCase):
    def test_eq_empty(self):
        l1 = CircularList()
        l2 = CircularList()

        self.assertEqual(l1, l2)
        self.assertEqual(l1 != l2, False)

    def test_eq(self):
        l1 = CircularList()
        l2 = CircularList()
        l1.append(1)
        l1.append(2)
        l1.append(2)
        l2.append(1)
        l2.append(2)
        l2.append(2)

        self.assertEqual(l1, l2)
        self.assertEqual(l1 != l2, False)

    def test_repr(self):
        l = CircularList()
        self.assertEqual(repr(l), "CircularList: []")

        l.append(1)
        l.append(2)
        l.append(3)
        self.assertEqual(repr(l), "CircularList: [1, 2, 3]")

    def test_prepend(self):
        l = CircularList()
        l.prepend(1)
        l.prepend(2)
        l.prepend(3)

        self.assertEqual(repr(l), "CircularList: [3, 2, 1]")

    def test_remove_mid(self):
        l = CircularList()
        l.append(1)
        l.append(2)
        l.append(3)
        l.append(4)
        l.remove(3)

        self.assertEqual(repr(l), "CircularList: [1, 2, 4]")

    def test_remove_tail(self):
        l = CircularList()
        l.append(1)
        l.append(2)
        l.append(3)
        l.append(4)
        l.remove(4)

        self.assertEqual(repr(l), "CircularList: [1, 2, 3]")

    def test_remove_head(self):
        l = CircularList()
        l.append(1)
        l.append(2)
        l.append(3)
        l.append(4)
        l.remove(1)

        self.assertEqual(repr(l), "CircularList: [2, 3, 4]")

    def test_len_empty(self):
        l = CircularList()
        self.assertEqual(len(l), 0)

    def test_len_add_delete(self):
        l = CircularList()
        l.append(0)
        l.append(1)
        self.assertEqual(len(l), 2)

        l.remove(0)
        self.assertEqual(len(l), 1)

    def test_split_list_even(self):
        l = CircularList()
        l.append(0)
        l.append(1)
        l.append(2)
        l.append(3)

        l2 = l.split_list()

        self.assertEqual(repr(l), "CircularList: [0, 1]")
        self.assertEqual(repr(l2), "CircularList: [2, 3]")


if __name__ == "__main__":
    unittest.main(verbosity=2)