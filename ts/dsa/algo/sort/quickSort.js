/**
 * Quick sort implementation
 * 
 * @template T
 * @param {Array<T>} arr array to sort
 * @param {(a: T, b: T) => number} predicate 
 * comparison function that returns negative when `a` should come before `b`, 
 * and positve when `a` should come after `b`.
 * This needs to be set if comparing anything besides a string or number.
 * @param {number} begin - beginning of index to sort
 * @param {number} end - one beyond the last index to sort
 * @returns {Array<T>} a reference to the passed array
 * 
 * @throws {RangeError} if accessing an array element beyond range
 */
function quickSort(arr, predicate=(a, b) => a < b ? -1 : 1, begin=0, end=arr.length) {
    if (end - begin < 2) return arr;

    // arrange array where anything less than the pivot point (first element) is to the left of it
    // and anything greater than it is to the right of it
    let pivotIdx = begin;
    const pivot = arr[pivotIdx];
    for (let i = begin + 1; i < end; ++i) {
        if (predicate(pivot, arr[i]) > 0) { // current value must precede pivot point

            // swap to get current value on left side of pivot
            if (i - pivotIdx === 1) {  // current idx is right after pivot idx
                //
                arr[pivotIdx] = arr[i];
                arr[i] = pivot;
            } else {                   // current idx is several or more indices after pivot idx
                // swap pivot with one after it, which can be assumed is greater than it
                arr[pivotIdx] = arr[pivotIdx + 1];
                arr[pivotIdx + 1] = pivot;
                
                // swap current idx value with the greater than value, which now sits at pivot idx
                const temp = arr[i];
                arr[i] = arr[pivotIdx];
                arr[pivotIdx] = temp;
            }
            
            ++pivotIdx;
        }
    }

    // left
    quickSort(arr, predicate, begin, pivotIdx);
    // right
    quickSort(arr, predicate, pivotIdx + 1, end);

    return arr;
}

let arr = [1, 2, 3, 5, 4, 3, 2, 1];

quickSort(arr);
console.log(arr);

const compareArrays = require("./compareArrays");
console.assert(compareArrays(arr, [1, 1, 2, 2, 3, 3, 4, 5]));

module.exports = quickSort;
