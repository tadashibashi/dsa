/**
 * Insertion sort implementation.
 * Mutates the array that is passed into it.
 * 
 * @param {ArrayLike<T>} arr 
 * array to sort
 * 
 * @param {(a: T, b: T) => number} predicate
 * A function that returns negative if `a` should come before `b`
 * and returns positive when `a` should come after b.
 * 
 * @returns {ArrayLike<T>}
 * reference to the mutated array
 */
function insertionSort(arr, predicate=(a, b) => a < b ? -1 : 1) {
    for (let i = 0; i < arr.length; ++i) {
        for (let j = i; j > 0; --j) {
            if (predicate(arr[j], arr[j-1]) < 0) {
                [arr[j], arr[j-1]] = [arr[j-1], arr[j]];
            } else {
                break;
            }
        }
    }

    return arr;
}

let arr = [5, 4, 3, 2, 1];

insertionSort(arr);
console.log(arr);

const compareArrays = require("./compareArrays");

console.assert(compareArrays(arr, [1, 2, 3, 4, 5]));

module.exports = insertionSort;
