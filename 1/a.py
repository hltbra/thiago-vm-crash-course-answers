"""
# Machine #1

Opcodes: `PUSH`, `POP`, `SUM`, `SUMX`

Basic API:

>>> m1 = Machine1()
>>> m1.dump_stack()
[]

### `PUSH <ARG>`

>>> m1 = Machine1()
>>> m1.evaluate(['PUSH', 10])
>>> m1.dump_stack()
[10]

### `POP`

>>> m1 = Machine1()
>>> m1.evaluate(['PUSH', 10, 'POP'])
>>> m1.dump_stack()
[]


### `SUM`

pops and sums the 2 topmost values on the stack and pushes the result.

>>> m1 = Machine1()
>>> m1.evaluate(['PUSH', 11, 'PUSH', 22, 'PUSH', 33, 'SUM'])
>>> m1.dump_stack()
[11, 55]

### `SUMX`

let `len` be the topmost value popped from the stack: `SUMX` pops and sums the top `len` values on the stack and pushes the result.

>>> m1 = Machine1()
>>> m1.evaluate(['PUSH', 4, 'PUSH', 5, 'PUSH', 6, 'PUSH', 3, 'SUMX'])
>>> m1.dump_stack()
[15]

"""


class Machine1(object):

    def __init__(self):
        self._stack = []

    def evaluate(self, operations):
        while operations:
            op = operations.pop(0)
            if op == 'PUSH':
                value = operations.pop(0)
                self._push(value)
            elif op == 'POP':
                self._pop()
            elif op == 'SUM':
                x = self._pop()
                y = self._pop()
                self._push(x + y)
            elif op == 'SUMX':
                length = self._pop()
                values = []
                for _ in range(length):
                    values.append(self._pop())
                self._push(sum(values))

    def _push(self, value):
        self._stack.append(value)

    def _pop(self):
        return self._stack.pop()

    def dump_stack(self):
        return self._stack


if __name__ == '__main__':
    import doctest
    doctest.testmod(verbose=True)
