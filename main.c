#include <stdio.h>
#include <stdlib.h>

struct Queue {
    int *a;
    int cap;
    int head;
    int size;
};

int init(struct Queue *q, int cap) {
    q->a = (int *)malloc(cap * sizeof(int));
    if (q->a == NULL) {
        printf("Xato: xotira ajratilmadi!\n");
        return 0;
    }
    q->cap = cap;
    q->head = 0;
    q->size = 0;
    return 1;
}

int grow(struct Queue *q) {
    int i;
    int *b = (int *)malloc(q->cap * 2 * sizeof(int));
    if (b == NULL) {
        printf("Xato: xotira ajratilmadi!\n");
        return 0;
    }
    for (i = 0; i < q->size; i++) {
        b[i] = q->a[(q->head + i) % q->cap];
    }
    free(q->a);
    q->a = b;
    q->head = 0;
    q->cap = q->cap * 2;
    return 1;
}

int enqueue(struct Queue *q, int x) {
    if (q->size == q->cap) {
        if (!grow(q)) {
            return 0;
        }
        printf("Sig'im %d ga oshirildi\n", q->cap);
    }
    q->a[(q->head + q->size) % q->cap] = x;
    q->size++;
    return 1;
}

int dequeue(struct Queue *q, int *x) {
    if (q->size == 0) {
        return 0;
    }
    *x = q->a[q->head];
    q->head = (q->head + 1) % q->cap;
    q->size--;
    return 1;
}

void print(struct Queue *q) {
    int i;
    if (q->size == 0) {
        printf("Navbat bo'sh.\n");
        return;
    }
    printf("Navbat: ");
    for (i = 0; i < q->size; i++) {
        printf("%d ", q->a[(q->head + i) % q->cap]);
    }
    printf("\n");
}

int main() {
    struct Queue q;
    int cap, c, x;

    printf("Sig'imni kiriting (1..1000): ");
    if (scanf("%d", &cap) != 1) {
        printf("Xato: butun son kiriting!\n");
        return 1;
    }
    if (cap <= 0 || cap > 1000) {
        printf("Xato: sig'im 1 dan 1000 gacha bo'lishi kerak!\n");
        return 1;
    }
    if (!init(&q, cap)) {
        return 1;
    }

    do {
        printf("\n1 - enqueue, 2 - dequeue, 3 - chiqarish, 0 - chiqish: ");
        if (scanf("%d", &c) != 1) {
            printf("Xato: butun son kiriting!\n");
            break;
        }
        if (c == 1) {
            printf("Son: ");
            if (scanf("%d", &x) != 1) {
                printf("Xato: butun son kiriting!\n");
                break;
            }
            if (!enqueue(&q, x)) {
                break;
            }
        } else if (c == 2) {
            if (dequeue(&q, &x)) {
                printf("Olindi: %d\n", x);
            } else {
                printf("Xato: navbat bo'sh!\n");
            }
        } else if (c == 3) {
            print(&q);
        } else if (c != 0) {
            printf("Xato: 0..3 oralig'ida tanlang!\n");
        }
    } while (c != 0);

    free(q.a);
    return 0;
}
