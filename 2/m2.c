#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define PUSH 0x1
#define POP 0x2
#define SUM 0x3
#define SUMX 0x4

#define STACK_MAX_SIZE 10000


typedef unsigned char t_word;

typedef struct {
    int i;
    t_word stack[STACK_MAX_SIZE];
} t_stack;


void push(t_stack *s, t_word value) {
    s->stack[s->i++] = value;
}

int pop(t_stack *s) {
    return s->stack[--s->i];
}

void init_stack(t_stack *s) {
    s->i = 0;
}

void sum(t_stack *s) {
    t_word x, y;
    x = pop(s);
    y = pop(s);
    push(s, x + y);
}

void sumx(t_stack *s) {
    t_word sum = 0;
    t_word len = pop(s);
    for (int i = 0 ; i < len; i++) {
        sum += pop(s);
    }
    push(s, sum);
}


void dump(t_stack *s) {
    printf("[");
    for (int i = 0 ; i < s->i ; i++) {
        printf("%d", s->stack[i]);
        if (i < (s->i - 1)) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(int argc, char *argv[]) {
    t_word token, value;
    t_stack s;
    init_stack(&s);

    if (argc < 2) {
        printf("ERROR: missing input file!\n");
        return 1;
    }
    int fd = open(argv[1], O_RDONLY);

    while (read(fd, &token, sizeof(t_word)) > 0) {
        // there always exist an operand
        read(fd, &value, sizeof(t_word));
        if (token == PUSH) {
            push(&s, value);
        } else if (token == POP) {
            pop(&s);
        } else if (token == SUM) {
            sum(&s);
        } else if (token == SUMX) {
            sumx(&s);
        }
    }
    dump(&s);

    return 0;
}
