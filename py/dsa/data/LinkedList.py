# Implementation of a singly linked list

class Node:
    def __init__(self, val):
        self.val = val
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None

    def __len__(self):
        if self.head is None:
            return 0
        count = 1
        current = self.head
        while current.next is not None:
            count += 1
            current = current.next
        return count

    def __repr__(self):
        if self.head is None:
            return "SinglyLinkedList: []"

        ret = "SinglyLinkedList: [ "
        current = self.head
        while current is not None:
            ret += str(current.val)
            if current.next is not None:
                ret += ", "
            current = current.next

        ret += " ]"
        return ret

    def __str__(self):
        return self.__repr__()

    def __get_node(self, index):
        if index < 0:
            raise IndexError()
        if self.head is None:
            return None

        current = self.head
        while index > 0:
            index -= 1
            if current.next is None:
                raise IndexError()
            current = current.next
        return current

    def __getitem__(self, index):
        node = self.__get_node(index)
        return node.val

    def is_empty(self):
        return self.head is None

    def append(self, val):
        new_node = Node(val)
        if self.head is None:
            self.head = new_node
        else:
            current = self.head
            while current.next is not None:
                current = current.next
            current.next = new_node

    def prepend(self, val):
        new_node = Node(val)

        new_node.next = self.head
        self.head = new_node

    def __insert_after_node(self, prev_node, data):
        new_node = Node(data)

        if not prev_node:
            self.head = new_node
        else:
            new_node.next = prev_node.next
            prev_node.next = new_node

    def insert(self, index, data):
        if index == 0:
            self.prepend(data)
        else:
            prev_node = self.__get_node(index-1)
            self.__insert_after_node(prev_node, data)

    def delete_at(self, index):
        if self.head is None:
            return
        if index == 0:
            self.head = self.head.next
        else:
            prev_node = self.__get_node(index-1)
            target = prev_node.next
            if target is not None:
                prev_node.next = target.next

    def delete(self, val):
        cur_node = self.head

        # check if head is to be deleted
        if cur_node and cur_node.val == val:
            cur_node.next = self.head
            cur_node = None
            return

        # check rest of list
        prev = None
        while cur_node and cur_node.val != val:
            prev = cur_node
            cur_node = cur_node.next

        if cur_node:
            prev.next = cur_node.next
            cur_node = None
            return

    def swap(self, val1, val2):
        # avoid unecessary calls if possible
        if val1 == val2:
            return

        # find the node and previous node for each value
        prev_1 = None
        curr_1 = self.head
        while curr_1 and curr_1.val != val1:
            prev_1 = curr_1
            curr_1 = curr_1.next

        prev_2 = None
        curr_2 = self.head
        while curr_2 and curr_2.val != val2:
            prev_2 = curr_2
            curr_2 = curr_2.next

        # if one of the values was not found, cannot swap, return
        if not curr_1 or not curr_2:
            return

        # swap the nodes
        if prev_1:
            prev_1.next = curr_2
        else:
            self.head = curr_2

        if prev_2:
            prev_2.next = curr_1
        else:
            self.head = curr_1

        # swap the nodes' next values
        curr_1.next, curr_2.next = curr_2.next, curr_1.next

    def reverse(self):
        if not self.head:
            return

        prev = None
        curr = self.head

        while curr:
            temp = curr.next
            curr.next = prev
            prev = curr
            curr = temp
        self.head = prev


# ===== TODO: Move to tests folder =====
a_list = LinkedList()

print("a_list is empty:", a_list.is_empty())
print("a_list len:", len(a_list))

print("appending 1")
a_list.append(1)

print("length correct:", not a_list.is_empty() and len(a_list) == 1)

print("indexes correctly:", a_list[0] == 1)
print(a_list)

print("prepending 10")
a_list.prepend(10)

print("length correct:", len(a_list) == 2)
print("10 inserted correctly:", a_list[0] == 10 and a_list[1] == 1)
print(a_list)

print("inserting 100 at start")
a_list.insert(0, 100)
print("length correct:", len(a_list) == 3)
print("100 inserted correctly:", a_list[0] == 100 and a_list[1] == 10 and a_list[2] == 1)
print(a_list)

print("inserting 1000 at index 1")
a_list.insert(1, 1000)
print("length correct:", len(a_list) == 4)
print("1000 inserted correctly:", a_list[0] == 100 and a_list[1] == 1000 and a_list[2] == 10 and a_list[3] == 1)
print(a_list)

print("delete_at index 1")
a_list.delete_at(1)

print("length correct:", len(a_list) == 3)
print("deleted 1000:", a_list[0] == 100 and a_list[1] == 10 and a_list[2] == 1)
print(a_list)

print("delete the number 10")
a_list.delete(10)
print("length correct: ", len(a_list) == 2)
print("deleted 10:", a_list[1] == 1)
print(a_list)

print("swap 100 and 1")
a_list.swap(100, 1)
print("length correct:", len(a_list) == 2)
print("swapped:", a_list[0] == 1 and a_list[1] == 100)
print(a_list)

b_list = LinkedList()
b_list.append(1)
b_list.append(2)
b_list.append(3)
print("Reversing linkedlist")
b_list.reverse()

print("reversed:", b_list[0] == 3 and b_list[1] == 2 and b_list[2] == 1)
print(b_list)
