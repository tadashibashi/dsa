/**
 * Bubble sort implementation.
 * Mutates the array that is passed into it.
 * 
 * @param arr
 * array to sort
 * 
 * @param predicate
 * A function that returns negative if `a` should come before `b`
 * and returns positive when `a` should come after b.
 * 
 * @returns
 * reference to the mutated array
 */
function bubbleSort<T>(arr: Array<T>, predicate=(a: T, b: T) => a < b ? -1 : 1) {
    for (let i = 0; i < arr.length-1; ++i) {
        let swapped = false;
        for (let j = 0; j < arr.length-1-i; ++j) {
            if (predicate(arr[j], arr[j+1]) > 0) {
                [arr[j], arr[j+1]] = [arr[j+1], arr[j]];
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }

    return arr;
}

let arr = [5, 4, 3, 2, 1];

bubbleSort(arr);
console.log(arr);

import compareArrays from "./compareArrays";
console.assert(compareArrays(arr, [1, 2, 3, 4, 5]));

export default bubbleSort;