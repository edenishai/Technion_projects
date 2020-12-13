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
    Node iterator;

    CopyPQElement copy_element;
    FreePQElement free_element;
    EqualPQElements equal_elements;
    CopyPQElementPriority copy_priority;
    FreePQElementPriority free_priority;
    ComparePQElementPriorities compare_priorities;
};
/*--------------------------------------static area-----------------------------------------*/
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
    if (queue == NULL || queue->head == NULL) {
        return PQ_SUCCESS;
    }
    if (newQueue == NULL) {
        return PQ_NULL_ARGUMENT;
    }
    newQueue->head = createNode(queue->copy_element(queue->head->element), queue->copy_priority(queue->head->priority));
    if (newQueue->head == NULL || newQueue->head->element == NULL || newQueue->head->priority == NULL) {
        pqDestroy(newQueue);
        return PQ_NULL_ARGUMENT;
    }
    Node queue_iterator = queue->head->next;
    Node newQueue_iterator = newQueue->head;
    while (queue_iterator) { 
        newQueue_iterator->next = createNode(queue->copy_element(queue_iterator->element), queue->copy_priority(queue_iterator->priority));
        newQueue_iterator = newQueue_iterator->next;
        if (newQueue_iterator == NULL || newQueue_iterator->element == NULL || newQueue_iterator->priority == NULL) {
            pqDestroy(newQueue);
            return PQ_NULL_ARGUMENT;
        }
        queue_iterator = queue_iterator->next;
    }
    return PQ_SUCCESS;
}
/*------------------------------------------------------------------------------------------*/
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
    queue->iterator = NULL;
    if (queue->head) {
        queue->free_element(queue->head->element);
        queue->free_priority(queue->head->priority);
        Node toDelete = queue->head;
        queue->head = queue->head->next;
        free(toDelete);
        return PQ_SUCCESS;
    }
    return PQ_SUCCESS;
}

PriorityQueueResult pqClear(PriorityQueue queue) {
    if (queue == NULL) {
        return PQ_NULL_ARGUMENT;
    }
    while (queue->head) {
        PriorityQueueResult removeResult = pqRemove(queue);
        assert(removeResult == PQ_SUCCESS);
    }
    queue->iterator = NULL;
    return PQ_SUCCESS;
}

void pqDestroy(PriorityQueue queue) {
    if (queue == NULL) {
        return;
    }
    if (queue->head) {
        pqClear(queue);
    }
    free(queue);
}

PriorityQueue pqCopy(PriorityQueue queue) {
    if (queue == NULL) {
        return NULL;
    }
    queue->iterator = NULL;
    PriorityQueue newQueue = pqCreate(queue->copy_element, queue->free_element,
     queue->equal_elements, queue->copy_priority, queue->free_priority, queue->compare_priorities);

    if (newQueue == NULL) {
        return NULL;
    }
    newQueue->iterator = NULL;
    if (copyAllOrDestroy(newQueue, queue) != PQ_SUCCESS) {
        return NULL;
    }
    return newQueue;
}

int pqGetSize(PriorityQueue queue) {
    if (queue == NULL) {
        return SIZE_ERROR;
    }
    int size = 0;
    Node iterator = queue->head;
    while (iterator) {
        iterator = iterator->next;
        ++size;
    }
    return size;
}

bool pqContains(PriorityQueue queue, PQElement element) {
    if (queue == NULL || element == NULL) {
        return false;
    }
    Node iterator = queue->head;
    while (iterator) {
        if (queue->equal_elements(iterator->element, element)) {
            return true;
        }
        iterator = iterator->next;
    }
    return false;
}

PriorityQueueResult pqInsert(PriorityQueue queue, PQElement element, PQElementPriority priority) {
    if (queue == NULL || element == NULL || priority == NULL) {
        return PQ_NULL_ARGUMENT;
    }
    queue->iterator = NULL;
    Node newNode = createNode(queue->copy_element(element), queue->copy_priority(priority));
    if (newNode == NULL) {
        return PQ_OUT_OF_MEMORY;
    }
    if (pqGetSize(queue) == 0) {
        queue->head = newNode;
        return PQ_SUCCESS;
    }
    if (queue->compare_priorities(queue->head->priority, priority) < 0) {
        newNode->next = queue->head;
        queue->head = newNode;
        return PQ_SUCCESS;
    }
    Node iterator = queue->head;
    while (iterator->next) {
        if (queue->compare_priorities(iterator->next->priority, priority) < 0) {
            newNode->next = iterator->next;
            iterator->next = newNode; 
            return PQ_SUCCESS;
        }
        iterator = iterator->next;
    }
    iterator->next = newNode;
    return PQ_SUCCESS;
}

PriorityQueueResult pqChangePriority(PriorityQueue queue, PQElement element,
                                     PQElementPriority old_priority, PQElementPriority new_priority) 
{
    if (queue == NULL || element == NULL || old_priority == NULL || new_priority == NULL) {
        return PQ_NULL_ARGUMENT;
    }
    queue->iterator = NULL;
    if (queue->head == NULL) {
        return PQ_ELEMENT_DOES_NOT_EXISTS;
    }
    if (queue->compare_priorities(queue->head->priority, old_priority) == 0) {
        if (queue->equal_elements(queue->head->element, element)) {
            if (pqInsert(queue, element, new_priority) != PQ_SUCCESS) {
                return PQ_OUT_OF_MEMORY;
            }
            PriorityQueueResult removeResult = pqRemove(queue);
            assert(removeResult == PQ_SUCCESS);
            return PQ_SUCCESS;
        }
    }
    Node iterator = queue->head;
    while (iterator->next) {
        assert (iterator->next->element && iterator->next->priority);
        int comparePriorities = queue->compare_priorities(iterator->next->priority, old_priority);
        if (comparePriorities < 0) {
            return PQ_ELEMENT_DOES_NOT_EXISTS;
        }
        else if (comparePriorities > 0) {
            iterator = iterator->next;
        }
        else { //there's a problem if the new priority is between iterator and iterator->next(or the other side).
            if (queue->equal_elements(iterator->next->element, element)) {
                if (pqInsert(queue, element, new_priority) != PQ_SUCCESS) {
                    return PQ_OUT_OF_MEMORY;
                }
                queue->free_element(iterator->next->element);
                queue->free_priority(iterator->next->priority);
                Node toDelete = iterator->next;
                iterator->next = iterator->next->next;
                free(toDelete);
                return PQ_SUCCESS;
            }
            iterator = iterator->next;
        }
    }
    return PQ_ELEMENT_DOES_NOT_EXISTS;
}
                      
PriorityQueueResult pqRemoveElement(PriorityQueue queue, PQElement element) {
    if (queue == NULL || element == NULL || queue->head == NULL) {
        return PQ_NULL_ARGUMENT;
    }
    queue->iterator = NULL;
    if (queue->equal_elements(queue->head->element, element)) {
        pqRemove(queue);
        return PQ_SUCCESS; //assert?
    }
    Node iterator = queue->head;
    while (iterator->next) {
        if (queue->equal_elements(iterator->next->element, element)) {
            queue->free_element(iterator->next->element);
            queue->free_priority(iterator->next->priority);
            Node toDelete = iterator->next;
            iterator->next = iterator->next->next;
            free(toDelete);
            return PQ_SUCCESS;
        }
        iterator = iterator->next;
    }
    return PQ_ELEMENT_DOES_NOT_EXISTS;
}

PQElement pqGetFirst(PriorityQueue queue) {
    if (queue == NULL || queue->head == NULL) {
        return NULL;
    }
    queue->iterator = queue->head;
    return queue->iterator->element;
}

PQElement pqGetNext(PriorityQueue queue) {
    if (queue == NULL || queue->iterator == NULL || queue->iterator->next == NULL) {
        return NULL;
    }
    queue->iterator = queue->iterator->next;
    return queue->iterator->element;
}