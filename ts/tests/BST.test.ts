import { BST } from "../dsa/data/BST";

describe("BST", () => {
    const t = new BST<number>();

    test("BST insert", () => {
        t.emplace(5);

        expect(t.has(5)).toBe(true);
    });

    test("BST forEachBreadth", () => {
        t.emplace(5);
        t.emplace(10);
        t.emplace(7);
        t.emplace(8);
        t.emplace(4);

        const expected: number[] = [5, 4, 10, 7, 8];
        const actual: number[] = [];
        t.forEachBFS((val) => {
            actual.push(val);
        });

        expect(actual).toEqual(expected);
    });
});
