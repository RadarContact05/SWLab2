#include <stdio.h>
#include <stdlib.h>

struct LinkedList {
    int id;
    double sensorData;
    struct LinkedList *next; 
};

struct LinkedList *add(int id, double sensorData) {
    struct LinkedList *el = malloc(sizeof(struct LinkedList));
    el->id = id;
    el->sensorData = sensorData;
    el->next = NULL;
    return el;
}

void insertFirst(struct LinkedList **first, struct LinkedList *el) {
    el->next = *first;
    *first = el;
}

int isMember(struct LinkedList **first, struct LinkedList *el) {
    struct LinkedList *current = *first;
    while (current != NULL) {
        if (current == el) {
            return 1;
        }
        current = current ->next;
    }
    return 0;
}

void printList(struct LinkedList *first) {
    struct LinkedList *current = first;
    while(current != NULL) {
        printf("%d\t%f\n", current->id, current->sensorData);
        current = current->next;
    }

}

void removeItem(struct LinkedList **first, struct LinkedList *el) {
    if (*first == el) {
        *first = el->next;
        el->next = NULL;
        return;
    }

    struct LinkedList *prev = *first;
    while (prev->next != NULL && prev->next != el) {
        prev = prev->next;
    }

    if (prev->next == el) {
        prev->next = el->next;
        el->next = NULL;
    }
}

struct LinkedList *readSensor(int id) {
    struct LinkedList *node = calloc(1, sizeof(struct LinkedList));

    node->id = id;
    node->sensorData = (double)rand() / (double)RAND_MAX;
    node->next = NULL;

    return node;
}

void sortList (struct LinkedList **first) {
    struct LinkedList *sortedHead = NULL;
    struct LinkedList *sortedTail = NULL;

    while(*first != NULL) {
        struct LinkedList *min = *first;
        struct LinkedList *cur = (*first)->next;
        while (cur != NULL) {
            if(cur->sensorData < min->sensorData) {
                min = cur;
            }
            cur = cur->next;
        }
        removeItem(first, min);

        min->next = NULL;

        if (sortedHead == NULL) {
            sortedHead = sortedTail = min;
        } else {
            sortedTail->next = min;
            sortedTail = min;
        }

    }
    *first = sortedHead;
}

int main(void) {
    struct LinkedList *first = NULL;

    for (int id = 1; id < 10; id++) {
        struct LinkedList *node = readSensor(id);
        insertFirst(&first, node);
    }
    sortList(&first);
    printf("\nSorted list:\n");
    printList(first);


    return 0;
}