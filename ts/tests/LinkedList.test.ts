import {LinkedList, sumList} from "../dsa/data/LinkedList";

describe("linked list tests", () => {
    test("init list, length set", () => {
        let list = new LinkedList();
        expect(list.length).toBe(0);
    });

    test("append, length", () => {

    });
});


describe("sumList", () => {
    test("count total in a number list", () => {
        let list = new LinkedList<number>();
        list.append(1);
        list.append(2);
        list.append(3);
        list.append(4);
        list.append(5);
        expect(sumList(list)).toBe(15);
    });
});


describe("reverse", () => {
    test("reverse works", () => {
        let list = new LinkedList<number>();
        list.append(1);
        list.append(2);
        list.append(3);
        list.append(4);
        list.append(5);
        list.reverse();
        expect(list.get(0)).toBe(5);
        expect(list.get(1)).toBe(4);
        expect(list.get(2)).toBe(3);
        expect(list.get(3)).toBe(2);
        expect(list.get(4)).toBe(1);
    });
});
