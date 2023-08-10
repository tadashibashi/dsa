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


export class BST<T> {
	head: BTNode<T> | null;
    comp: (a: T, b: T) => number;


	constructor(comp: (a: T, b: T) => number = (a, b) => a > b ? -1 : a < b ? 1 : 0 ) {
		this.head = null;
        this.comp = comp;
	}

    
    private *bfsIterator() {
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


    forEachBFS(callback: (value: T) => unknown) {
        for (const node of this.bfsIterator()) {
            if (callback(node.value) === -1)
                break;
        }
    }
	

	emplace(value: T) {
		if (!this.head) {
			this.head = new BTNode(value);
			return this;
		}
		
		let cur = this.head;
		while (true) {
			if (this.comp(cur.value, value) === 0) {
				// don't do anything if duplicate
				
				return this;
			}
			
			
			if (this.comp(cur.value, value) < 0) {
				if (cur.left) {
					cur = cur.left;
					continue;
				} else {
					cur.left = new BTNode(value);
					return this;
				}
			} else {
				if (cur.right) {
					cur = cur.right;
					continue;
				} else {
					cur.right = new BTNode(value);
					return this;
				}
			}
		}
	}

    
	has(value: T) {
		if (!this.head) return false;
		
		let cur = this.head;
		while (true) {
			if (cur.value === value) return true;
			
			if (this.comp(cur.value, value) < 0 && cur.left) {
				cur = cur.left;
				continue;
			}
			
			if (this.comp(cur.value, value) > 0 && cur.right) {
				cur = cur.right;
				continue;
			}
			
			return false;
		}
	}
}
