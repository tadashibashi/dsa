
/**
 * Merge sort implementation.
 * 
 * @param {Array<number>} arr 
 * 
 * @param {(a: T, b: T) => number} predicate 
 * comparison function that returns negative when `a` should come before `b`, 
 * and positve when `a` should come after `b`.
 * This needs to be set if comparing anything besides a string or number.
 * @returns new sorted array
 */
function mergeSort(arr, predicate=(a, b) => a < b ? -1 : 1) {
    if (arr.length < 2) return arr; // length of 1 or 0 is sorted

    // recursively split array until it reaches a length of 1
    const mid = Math.floor(arr.length/2);
    const left = mergeSort(arr.slice(0, mid), predicate);
    const right = mergeSort(arr.slice(mid), predicate);

    // then merge back until it is formed
    return merge(left, right, predicate);
}


/**
 * Merges and sorts two arrays.
 * @param {Array<number>} a 
 * @param {Array<number>} b 
 * @returns new sorted array
 */
function merge(a, b, predicate) {
    const res = [];

    let i = 0, j = 0;
    while (i < a.length && j < b.length) {
        if (predicate(a[i], b[j]) < 0) {
            res.push(a[i++]);
        } else {
            res.push(b[j++]);
        }
    }

    // append leftovers
    while (i < a.length)
        res.push(a[i++]);
    while (j < b.length)
        res.push(b[j++]);
    
    return res;
}

const arr = [5, 2, 9, 1, 4, 10, 0, 7, -3];
const expected = [-3, 0, 1, 2, 4, 5, 7, 9, 10];

const compareArrays = require("./compareArrays");

const sorted = mergeSort(arr);
console.assert(compareArrays(sorted, expected));
console.log(sorted);

module.exports = mergeSort;
