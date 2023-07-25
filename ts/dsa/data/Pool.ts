class Node<T> {
    data: T | null;

    nextFree: number;
    idx: number;
    innerId: number;

    constructor() {
        this.data = null;
        this.nextFree = -1;
        this.idx = -1;
        this.innerId = -1;
    }
}

// export class Pool<T> {
//     nextFree: number;
//
//     constructor()
// }