class BTNode<T> {
	left: BTNode<T> | null;
	right: BTNode<T> | null;
	value: T;
	
	constructor(value: T) {
		this.left = null;
		this.right = null;
		this.value = value;
	}
}


/**
 * TODO: generator that yields in order
 */

export class BST<T> {
	head: BTNode<T> | null;
    comp: (a: T, b: T) => number;


    /**
     * @param comp comparison function, returns negative when `a` comes before `b`
     * 0, when equal, and positive when `b` comes before `a`.
     */
    constructor(comp: (a: T, b: T) => number = (a, b) => a > b ? -1 : a < b ? 1 : 0 ) {
        this.head = null;
        this.comp = comp;
    }

    
    /**
     * Recursive breadth-first generator, yields each node
     * @returns generator
     */
    private *bfsNodes() {
        function *traverse(node: BTNode<T> | null, done: boolean = false): Generator<BTNode<T>> {
            if (!node || done) return;

            if (node.left)
                yield node.left;
                    
            if (node.right)
                yield node.right;

            yield *traverse(node.left);
            yield *traverse(node.right);
        }

        if (!this.head) return;

        yield this.head;
        
        yield *traverse(this.head);
    }

    /**
     * Generator that yields each value in breadth-first order
     * @returns generator
     */
    public *bfsValues() {
        for (const node of this.bfsNodes())
            yield node.value;
    }
	
    /**
     * Inserts a value into the tree
     * @param value 
     * @returns this tree for chaining
     */
	emplace(value: T) {

        // no head? create it with the new value
		if (!this.head) {
			this.head = new BTNode(value);
			return this;
		}
		
        // search tree for spot to insert
		let cur = this.head;
		while (true) {
            // duplicate values not allowed
			if (this.comp(cur.value, value) === 0) {
				throw new Error("BST: illegal duplicate value: " + value);
			}
			
			
			if (this.comp(cur.value, value) < 0) {
                // value is less than current 
				if (cur.left) {
					cur = cur.left;
				} else { // found empty position to insert
					cur.left = new BTNode(value);
					return this;
				}
			} else {
                // value is more than current
				if (cur.right) {
					cur = cur.right;
				} else { // found empty position to insert
					cur.right = new BTNode(value);
					return this;
				}
			}
		}
	}


    /**
     * Checks whether tree contains a value
     * @param value - value to check
     */
	has(value: T): boolean {
		if (!this.head) return false;
		
		let cur = this.head;
		while (true) {
			if (cur.value === value) return true;
			
			if (this.comp(cur.value, value)) {
                if (cur.left)
				    cur = cur.left;
			} else {
                if (cur.right)
                    cur = cur.right;
            }

            return false;
		}
	}
}
