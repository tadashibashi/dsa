import bubbleSort from "../dsa/algo/sort/bubbleSort";

describe("bubbleSort", () => {
    test("can call on empty array", () => {
        expect(bubbleSort([])).toEqual([]);
    });
});
