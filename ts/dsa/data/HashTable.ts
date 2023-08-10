// hash a unique value from a key, store it in a bucket with that key

function hashString(s: string, bucketCount: number): number {
    let hash = 0;
    for (let i = 0; i < s.length; ++i)
        hash += (s.charCodeAt(i) + 27 * i) % Number.MAX_VALUE;

    return hash % bucketCount;
}

function hashNumber(n: number, bucketCount: number): number {
    return n % bucketCount;
}



type Hashable = string | number;
type KVP<K, V> = {key: K, value: V };
type HashBucket<K, V> = Array<KVP<K, V>>;

class HashTable<K extends Hashable, V> {

    private buckets: Array<HashBucket<K, V>>;

    constructor() {
        this.buckets = new Array(33);
        for (let i = 0; i < 33; ++i)
            this.buckets[i] = [];
    }

    size(): number {
        let s = 0;
        for (let i = 0; i < this.buckets.length; ++i)
            s += this.buckets[i].length;

        return s;
    }

    get(key: K): V | undefined {
        const bucket = this.getBucket(key);
        let pair = bucket.find(obj => obj.key === key);
        if (!pair) return undefined;

        return pair.value;
    }

    set(key: K, value: V) {
        const bucket = this.getBucket(key);
        let pair = bucket.find(obj => obj.key === key);
        if (pair)  // overwrite existing key's value
            pair.value = value;
        else       // add new kvp
            bucket.push({key, value});
    }

    private getBucket(key: K): HashBucket<K, V> {
        return this.buckets[this.getBucketIndex(key)];
    }

    private getBucketIndex(key: K): number {
        switch (typeof key) {
            case "string":
                return hashString(key, this.buckets.length);
            case "number":
                return hashNumber(key, this.buckets.length);
            default:
                throw new Error("invalid key type");
        }
    }


}

const map = new HashTable<string, number>();

map.set("acorn", 10);
console.assert(map.size() === 1);
map.set("acorn", 1234);
console.assert(map.size() === 1);

map.set("pizza", 444);
console.assert(map.size() === 2);
map.set("pink", 123);
console.assert(map.size() === 3);


console.assert(map.get("acorn") === 10);
console.assert(map.get("acorn") === 1234);
console.assert(map.get("pink") === 123);
console.log(hashString("pink", 33));
console.log(hashString("green", 33));
console.log(hashString("orange", 33));