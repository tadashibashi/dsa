class Node<T> {
    data: T;
    next: Node<T> | null;
    constructor(item: T){
        this.data = item;
        this.next = null;
    }
}

export class LinkedList<T> {
    head: Node<T> | null;
    constructor(){
        // a Linked List starts with a "head" property intialized as null
        this.head = null;
    }

    get length(): number {
        if (!this.head) return 0;

        let len = 0;
        let cur: Node<T> | null = this.head;
        while (cur) {
            cur = cur.next;
            ++len;
        }

        return len;
    }

    reverse() {
        if (!this.head) return;

        let last = null;
        let cur: Node<T> | null = this.head;

        while (cur) {
            const temp: Node<T> | null = cur.next;
            cur.next = last;
            last = cur;
            cur = temp;
        }

        this.head = last;
    }

    // get the initial iterator to the first node
    *begin() {
        let cur = this.head;
        while (cur) {
            yield cur;
            cur = cur.next;
        }
    }

    get(idx: number): T {
        if (!this.head) throw RangeError("out of range");

        let cur = this.head;
        while (idx > 0 && cur?.next) {
            cur = cur.next;
            --idx;
        }

        if (idx !== 0) throw RangeError("out of range");

        return cur.data;
    }

    /**
     * Creates a new node with the given data and adds it to back of the list.
     * @param data
     */
    append(data: T) {
        if (!this.head)
            this.head = new Node<T>(data);
        else {
            // go to last node
            let cur = this.head;
            while (cur.next)
                cur = cur.next;
            cur.next = new Node<T>(data);
        }
    }

    /**
     * Creates a new node with the given data and adds it to the front of the list.
     * @param data
     */
    prepend(data: T){
        const newNode = new Node<T>(data);
        if (this.head)
            newNode.next = this.head;
        this.head = newNode;
    }

    /**
     * Removes the last node from the list and returns it
     */
    pop(){
        if (!this.head) return null;

        let last = null;
        let cur: Node<T> | null = this.head;
        while (cur.next) {
            last = cur;
            cur = cur.next;
        }

        if (!last)
            this.head = null;
        else
            last.next = null;

        return cur.data;
    }

    /**
     * Remove (shift off) the first node and return its value.
     */
    shift(){
        if (!this.head) return null;
        const cur = this.head;
        this.head = this.head.next;

        return cur.data;
    }
    insertAt(idx: number, data: T) {
        let last = null;
        let cur = this.head;

        while (idx > 0 && cur?.next) {
            last = cur;
            cur = cur.next;
            --idx;
        }

        if (idx !== 0)
            throw RangeError(idx + " is out of range!");

        if (!last)
            this.head = new Node(data);
        else {
            last.next = new Node(data);
            last.next.next = cur;
        }
    }

    removeAt(idx: number) {
        if (!this.head) throw RangeError("out of range");

        let last = null;
        let cur = this.head;
        while (cur.next && idx > 0) {
            last = cur;
            cur = cur.next;
            --idx;
        }

        if (idx > 0)
            throw RangeError("out of range");

        if (!last) {
            this.head = null;
        } else {
            last.next = cur.next;
        }
    }

    /**
     * Searches for a value in the list
     * @param data
     * @return index of the value of the list, -1 if not found
     */
    search(data: T) {
        let idx = 0;
        let cur = this.head;
        while (cur) {
            if (cur.data === data) return idx;
            cur = cur.next;
            ++idx;
        }

        return -1;
    }


    sort(compareFn?: (a: T, b: T) => number) {
        if (!this.head) return;

        const arr = this.toArray();
        arr.sort(compareFn);

        let idx = 0;
        let cur: Node<T> | null = this.head;
        while (cur) {
            cur.data = arr[idx++];
            cur = cur.next;
        }
    }

    toArray() {
        const res = [];
        let cur = this.head;
        while(cur) {
            res.push(cur.data);
            cur = cur.next;
        }

        return res;
    }

    *[Symbol.iterator]() {
        let cur = this.head;
        while(cur) {
            yield cur.data;
            cur = cur.next;
        }
    }
}

export function sumList(list: LinkedList<number>) {
    let sum = 0;
    for (let n of list)
        sum += n;

    return sum;
}
