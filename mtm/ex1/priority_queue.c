#include "priority_queue.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define SIZE_ERROR -1

typedef struct node {
    PQElement element;
    PQElementPriority priority;
    struct node* next;
} *Node;

struct PriorityQueue_t {
    Node head;     //linked list
    PQElement iterator;

    CopyPQElement copy_element;
    FreePQElement free_element;
    EqualPQElements equal_elements;
    CopyPQElementPriority copy_priority;
    FreePQElementPriority free_priority;
    ComparePQElementPriorities compare_priorities;
};

PriorityQueue pqCreate(CopyPQElement copy_element,
                       FreePQElement free_element,
                       EqualPQElements equal_elements,
                       CopyPQElementPriority copy_priority,
                       FreePQElementPriority free_priority,
                       ComparePQElementPriorities compare_priorities) 
{
    if (!copy_element || !free_element || !equal_elements || !copy_priority 
    || !free_priority || !compare_priorities) {
        return NULL;
    }

    PriorityQueue queue = malloc(sizeof(*queue));
    if (queue == NULL) {
        return NULL;
    }

    queue->head = NULL;
    queue->iterator = NULL;

    queue->copy_element = copy_element;
    queue->free_element = free_element;
    queue->equal_elements = equal_elements;
    queue->copy_priority = copy_priority;
    queue->free_priority = free_priority;
    queue->compare_priorities = compare_priorities;

    return queue;
}

PriorityQueueResult pqRemove(PriorityQueue queue) {
    if (queue == NULL) {
        return PQ_NULL_ARGUMENT;
    }
    if (queue->head) {
        queue->free_element(queue->head->element);
        queue->free_priority(queue->head->priority);
        Node toDelete = queue->head;
        queue->head = queue->head->next;
        free(toDelete);
    }
    return PQ_SUCCESS;
}

PriorityQueueResult pqClear(PriorityQueue queue) {
    if (queue == NULL) {
        return PQ_NULL_ARGUMENT;
    }
    while (queue->head) {
        pqRemove(queue);
    }
    return PQ_SUCCESS;
}

void pqDestroy(PriorityQueue queue) {
    if (queue == NULL) {
        return;
    }
    while (queue->head) {
        pqClear(queue);
    }
    free(queue);
}

PriorityQueue pqCopy(PriorityQueue queue) {
    if (queue == NULL) {
        return NULL;
    }
    PriorityQueue newQueue = pqCreate(queue->copy_element, queue->free_element,
     queue->equal_elements, queue->copy_priority, queue->free_priority, queue->compare_priorities);

    if (newQueue == NULL) {
        return NULL;
    }

    if (copyAllOrDestroy(newQueue, queue) != PQ_SUCCESS) {
        return NULL;
    }

    return newQueue;
}

/*static area*/
static Node createNode(PQElement element, PQElementPriority priority) {
    if (element == NULL || priority == NULL) {
		return NULL;
	}
	Node newNode = malloc(sizeof(*newNode));
	if (newNode == NULL) {
		return NULL;
	}
	newNode->element = element;
    newNode->priority = priority;
	newNode->next = NULL;
	return newNode;
}

static PriorityQueueResult copyAllOrDestroy(PriorityQueue newQueue, PriorityQueue queue) {
    if (queue == NULL) {
        return PQ_SUCCESS;
    }

    if (newQueue == NULL) {
        return PQ_NULL_ARGUMENT;
    }

    while (queue->head) {
        newQueue->head = createNode(queue->copy_element(queue->head->element), queue->copy_priority(queue->head->priority));
        if (newQueue->head == NULL) {
            pqDestroy(newQueue);
            return PQ_NULL_ARGUMENT;
        }
        queue->head = queue->head->next;
        newQueue->head = newQueue->head->next;
    }
    return PQ_SUCCESS;
}
/*end area*/

int pqGetSize(PriorityQueue queue) {
    int size = 0;
    if (queue == NULL) {
        return SIZE_ERROR;
    }
    while (queue->head) {
        ++size;
        queue->head = queue->head->next;
    }
    return size;
}

bool pqContains(PriorityQueue queue, PQElement element) {
    if (queue == NULL || element == NULL) {
        return false;
    }
    while (queue->head) {
        if (queue->equal_elements(queue->head->element, element)) {
            return true;
        }
        queue->head = queue->head->next;
    }
    return false;
}

PriorityQueueResult pqInsert(PriorityQueue queue, PQElement element, PQElementPriority priority) {
    if (queue == NULL || element == NULL || priority == NULL) {
        return PQ_NULL_ARGUMENT;
    }
    while (queue->head) {
        if (queue->head->priority == NULL) {
            return PQ_NULL_ARGUMENT;
        }
        else if (queue->compare_priorities(queue->head->priority, priority) >= 0) {
            queue->head = queue->head->next;
        } 
        else if (queue->head->element == NULL) {
            return PQ_NULL_ARGUMENT;
        }
        else if (queue->compare_priorities(queue->head->priority, priority) < 0) {
            Node newNode = createNode(queue->copy_element(queue->head->element), queue->copy_priority(queue->head->priority));
            if (newNode == NULL) {
                return PQ_OUT_OF_MEMORY;
            }
            newNode->next = queue->head->next;

            queue->head->element = queue->copy_element(element);
            queue->head->priority = queue->copy_priority(priority);
            queue->head->next = newNode;
            
            return PQ_SUCCESS;
        } 
    }
    queue->head = createNode(queue->copy_element(element), queue->copy_priority(priority));
    if (queue->head) {
        return PQ_NULL_ARGUMENT;
    }
    return PQ_SUCCESS;
}
//to fix pqChangePriority
PriorityQueueResult pqChangePriority(PriorityQueue queue, PQElement element,
                                     PQElementPriority old_priority, PQElementPriority new_priority) 
{
    if (queue == NULL || element == NULL) {
        return PQ_ITEM_DOES_NOT_EXIST;
    }
    while (queue->head) {
        if (queue->compare_priorities(queue->head->priority, old_priority) != 0
        || queue->equal_elements(queue->head->element, element) == false) {
            queue->head = queue->head->next;
        }
        else {
            Node toDelete = queue->head;
            queue->head = queue->head->next;
            free(toDelete);

            pqInsert(queue, element, new_priority);
            return PQ_SUCCESS;
        }
    }
    return PQ_ITEM_DOES_NOT_EXIST;
}
                       
PriorityQueueResult pqRemoveElement(PriorityQueue queue, PQElement element);

PQElement pqGetFirst(PriorityQueue queue);

PQElement pqGetNext(PriorityQueue queue);


