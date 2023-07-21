class Stack:
    def __init__(self):
        self.__stack = []

    def __len__(self):
        return len(self.__stack)

    def push(self, val):
        self.__stack.append(val)

    def is_empty(self):
        return len(self.__stack) == 0

    def pop(self):
        return self.__stack.pop()

    def peek(self):
        return self.__stack[-1]

    def __str__(self):
        return str(self.__stack)


_BRACKETS = {"]": "[", ")": "(", "}": "{"}
def balanced_brackets(brackets: str) -> bool:

    stack = Stack()

    for bracket in brackets:
        match bracket:
            case "[" | "{" | "(":
                stack.push(bracket)
            case "]" | "}" | ")":
                if stack.is_empty() or stack.peek() != _BRACKETS[bracket]:
                    return False
                stack.pop()

    return stack.is_empty()

print(balanced_brackets("((()))"))     # True
print(balanced_brackets("[{([{}])}]")) # True
print(balanced_brackets("{[[[[]]"))     # False
print(balanced_brackets("[{()))}]")) # False
print(balanced_brackets(""))        # True