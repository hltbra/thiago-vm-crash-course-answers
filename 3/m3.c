#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/* instruction set */
#define PUSH 0x1
#define POP 0x2
#define SUM 0x3
#define SUMX 0x4
#define PCALL 0x5


/* primitive routines */
#define PRIM_PRINT 255


#define STACK_MAX_SIZE 10000


typedef unsigned char t_word;

typedef struct {
    int i;
    t_word stack[STACK_MAX_SIZE];
} t_stack;


void init_stack(t_stack *s) {
    s->i = 0;
}


/* primitive operations */

int prim_print(t_word argv[]) {
    putchar(argv[0]);
    return 0;
}


/* instruction set */

void int_push(t_stack *s, t_word value) {
    s->stack[s->i++] = value;
}

int int_pop(t_stack *s) {
    return s->stack[--s->i];
}

void int_sum(t_stack *s) {
    t_word x, y;
    x = int_pop(s);
    y = int_pop(s);
    int_push(s, x + y);
}

void int_sumx(t_stack *s) {
    t_word sum = 0;
    t_word len = int_pop(s);
    for (int i = 0 ; i < len; i++) {
        sum += int_pop(s);
    }
    int_push(s, sum);
}

void int_pcall(t_stack *s, t_word id) {
    int argc = int_pop(s);
    t_word argv[argc];
    for (int i = 0 ; i < argc ; i++) {
        argv[i] = int_pop(s);
    }
    if (id == PRIM_PRINT) {
        prim_print(argv);
    }
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
            int_push(&s, value);
        } else if (token == POP) {
            int_pop(&s);
        } else if (token == SUM) {
            int_sum(&s);
        } else if (token == SUMX) {
            int_sumx(&s);
        } else if (token == PCALL) {
            int_pcall(&s, value);
        }
    }
    // dump(&s);

    return 0;
}
