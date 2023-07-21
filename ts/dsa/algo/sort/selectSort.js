/**
 * Selection sort implementation.
 *
 * Mutates the array passed into it.
 *
 * @param {ArrayLike<T>} arr - array to search
 * @param {(a: T, b: T) => number} predicate
 * A comparison function that describes the ordering of the provided array.
 * Should return positive when `a` comes after `b`, and negative when
 * `a` comes before `b`, and 0 when `a` is equal to `b`.
 * By default, it describes an array of numbers or strings in ascending order.
 * @param {number} value - value to find
 *
 * @returns the index of the value, or -1 if the value was not found
 */
function selectionSort(arr, predicate=(a, b)=> a<b ? -1 : 1) {

	const mid = Math.floor(arr.length/2);
	for (let i = 0; i < mid; ++i) {
		// find minimum and maximum value indices
		let min = Infinity;
		let max = -Infinity;
		let minIdx, maxIdx;
		
		for (let j = i; j < arr.length-i; ++j) {
			if (predicate(arr[j], min) < 0) {
				min = arr[j];
				minIdx = j;
			}
			if (predicate(arr[j], max) >= 0) {
				max = arr[j];
				maxIdx = j;
			}
		}

		// swap minIdx with i
		let temp;
        if (minIdx !== i) {
            temp = arr[minIdx];
            arr[minIdx] = arr[i];
            arr[i] = temp;
            
        }

		// swap max with arr.length-1-i
        if (maxIdx !== i && maxIdx !== arr.length-1-i) {
            temp = arr[maxIdx];
            arr[maxIdx] = arr[arr.length-1-i];
            arr[arr.length-1-i] = temp;
        }
	}
	return arr;
}

const compareArrays = require("./compareArrays");

let arr = [5, 1, 3, 2, 0];
selectionSort(arr);

console.assert(compareArrays(arr, [0, 1, 2, 3, 5]));
console.log(arr);
