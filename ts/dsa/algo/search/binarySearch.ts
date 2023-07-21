/**
 * Binary search implementation.
 *
 * Finds the index of a value in a sorted array.
 * If there are duplicate variables, there is no guarantee as to which index it will find.
 *
 * @param arr - array to search
 * @param predicate
 * A comparison function that describes the ordering of the provided array.
 * Should return positive when `a` comes after `b`, and negative when
 * `a` comes before `b`, and 0 when `a` is equal to `b`.
 * By default, it describes an array of numbers or strings in ascending order.
 * @param value - value to search for
 *
 * @returns the index of the value if found, if not, the value of the negative index of where it should be inserted - 1.
 */
function binarySearch<T>(arr: ArrayLike<T>, value: T,
                         predicate=(a: T, b: T) => a < b ? -1 : a > b ? 1 : 0): number {
    let left=0, right=arr.length-1;
    while(right - left > 1) {
        const mid = Math.floor((right + left) / 2);
        
        const predResult = predicate(arr[mid], value);
        if (predResult > 0) {
            right = mid - 1;
        } else if (predResult < 0) {
            left = mid + 1;
        } else {
            return mid;
        }
    }

    const predLeftResult = predicate(arr[left], value)
    if (predLeftResult === 0) return left;
    if (predicate(arr[right], value) === 0) return right;

    return (predLeftResult < 0 ? -right : -left) - 1;
}

console.assert(binarySearch([1,2,3,4,5],2) === 1);
console.assert(binarySearch([1,2,3,4,5],3) === 2);
console.assert(binarySearch([1,2,3,4,5],5) === 4);
console.assert(binarySearch([1,2,3,4,5],6) === -5);
console.assert(binarySearch([
  5, 6, 10, 13, 14, 18, 30, 34, 35, 37, 
  40, 44, 64, 79, 84, 86, 95, 96, 98, 99
], 100) === -20);
