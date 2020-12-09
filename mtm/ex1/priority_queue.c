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
    if (queue == NULL) {
        return PQ_SUCCESS;
    }

    if (newQueue == NULL) {
        return PQ_NULL_ARGUMENT;
    }

    while (queue->head) {
        newQueue->head = createNode(queue->copy_element(queue->head->element), queue->copy_priority(queue->head->priority));
        if (newQueue->head == NULL || newQueue->head->element || newQueue->head->priority) {
            pqDestroy(newQueue);
            return PQ_NULL_ARGUMENT;
        }
        queue->head = queue->head->next;
        newQueue->head = newQueue->head->next;
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
    return PQ_NULL_ARGUMENT;
}

PriorityQueueResult pqClear(PriorityQueue queue) {
    if (queue == NULL) {
        return PQ_NULL_ARGUMENT;
    }
    while (queue->head) {
        PriorityQueueResult pqRemove_output = pqRemove(queue);
        assert(pqRemove_output == PQ_SUCCESS);
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
    free(queue->iterator);
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
    PQElement current_element = pqGetFirst(queue);
    while (current_element) {
        current_element = pqGetNext(queue);
        ++size;
    }
    return size;
}

bool pqContains(PriorityQueue queue, PQElement element) {
    if (queue == NULL || element == NULL) {
        return false;
    }
    PQElement current_element = pqGetFirst(queue);
    while (current_element) {
        if (queue->equal_elements(current_element, element)) {
            return true;
        }
        current_element = pqGetNext(queue);
    }
    return false;
}

PriorityQueueResult pqInsert(PriorityQueue queue, PQElement element, PQElementPriority priority) {
    if (queue == NULL || element == NULL || priority == NULL) {
        return PQ_NULL_ARGUMENT;
    }
    queue->iterator = NULL;
    Node current_node = queue->head;
    while (current_node) {
        assert(current_node->priority == NULL || current_node->element == NULL);

        if (queue->compare_priorities(queue->head->priority, priority) >= 0) {
            current_node = current_node->next;
        } 
        
        else {
            Node newNode = createNode(queue->copy_element(current_node->element), queue->copy_priority(current_node->priority));
            if (newNode == NULL) {
                return PQ_OUT_OF_MEMORY;
            }
            newNode->next = current_node->next;

            current_node->element = queue->copy_element(element);
            current_node->priority = queue->copy_priority(priority);
            current_node->next = newNode;
            
            return PQ_SUCCESS;
        } 
    }
    current_node = createNode(queue->copy_element(element), queue->copy_priority(priority));
    if (current_node == NULL) {
        return PQ_OUT_OF_MEMORY;
    }
    return PQ_SUCCESS;
}

PriorityQueueResult pqChangePriority(PriorityQueue queue, PQElement element,
                                     PQElementPriority old_priority, PQElementPriority new_priority) 
{
    if (queue == NULL || element == NULL || old_priority == NULL || new_priority == NULL) {
        return PQ_NULL_ARGUMENT;
    }
    queue->iterator = NULL;
    Node current_node = queue->head;
    while (current_node) {
        assert (current_node->element == NULL || current_node->priority == NULL);
        
        int compare_output = queue->compare_priorities(current_node->priority, old_priority);

        if (compare_output < 0) {
            return PQ_ELEMENT_DOES_NOT_EXISTS;
        }

        else if (compare_output > 0) {
            current_node = current_node->next;
        }

        else {
            if (queue->equal_elements(current_node->element, element) == false) {
                current_node = current_node->next;
            }
            else {
                if (pqInsert(queue, element, new_priority) != PQ_SUCCESS) {
                    return PQ_OUT_OF_MEMORY;
                }
                Node head = queue->head;
                queue->head = current_node;
                pqRemove(queue);
                queue->head = head;
                return PQ_SUCCESS;
            }
        }
    }
    return PQ_ELEMENT_DOES_NOT_EXISTS;
}
                       
PriorityQueueResult pqRemoveElement(PriorityQueue queue, PQElement element) {
    if (queue == NULL || element == NULL) {
        return PQ_NULL_ARGUMENT;
    }
    queue->iterator = NULL;
    Node current_node = queue->head;
    while (current_node) {
        if (queue->equal_elements(current_node->element, element) == false) {
            current_node = current_node->next;
            continue;
        }
        Node head = queue->head;
        queue->head = current_node;
        pqRemove(queue);
        queue->head = head;

        return PQ_SUCCESS;
    }
    return PQ_ELEMENT_DOES_NOT_EXISTS;
}

PQElement pqGetFirst(PriorityQueue queue) {
    if (queue == NULL || queue->head == NULL) {
        return NULL;
    }
    return queue->head->element;
}

PQElement pqGetNext(PriorityQueue queue) {
    if (queue == NULL || queue->head == NULL || queue->head->next == NULL) {
        return NULL;
    }
    return queue->head->next->element;
}