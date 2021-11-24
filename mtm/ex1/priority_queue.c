#include "priority_queue.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define SIZE_ERROR -1

typedef struct node 
{
    PQElement element;
    PQElementPriority priority;
    struct node* next;
} *Node;

struct PriorityQueue_t 
{
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
//createNode: Creates a new node with a specified element and a specified priority.
static Node createNode(PQElement element, PQElementPriority priority) 
{
    if (element == NULL || priority == NULL) {
		return NULL;
	}
	Node new_node = malloc(sizeof(*new_node));
	if (new_node == NULL) {
		return NULL;
	}
	new_node->element = element;
    new_node->priority = priority;
	new_node->next = NULL;
	return new_node;
}

//removeHeadOrNextNode: Deallocates the next node of the target node if the head argument is false.
//                      Otherwise, deallocates queue->head, regardless the node argument.
static PriorityQueueResult removeHeadOrNextNode(PriorityQueue queue, Node node, bool head) {
    if (queue == NULL) {
        return PQ_NULL_ARGUMENT;
    }
    Node* ptr_to_delete = NULL;
    if (head == true && queue->head != NULL) {
        ptr_to_delete = &(queue->head);
    }
    else if (head == false && node != NULL && node->next != NULL) {
        ptr_to_delete = &(node->next);
    }
    else {
        return PQ_SUCCESS;
    }

    queue->free_element((*ptr_to_delete)->element);
    queue->free_priority((*ptr_to_delete)->priority);
    Node to_delete = *ptr_to_delete;
    *ptr_to_delete = (*ptr_to_delete)->next;
    free(to_delete);

    return PQ_SUCCESS;
}

//pqCopyAllOrDestroy: Copies a target priority queue to an new empty priority queue.
//                    Deallocates the new priority queue in case of failure.
static PriorityQueueResult pqCopyAllOrDestroy(PriorityQueue new_queue, PriorityQueue queue) 
{
    if (queue == NULL || queue->head == NULL) {
        return PQ_SUCCESS;
    }
    if (new_queue == NULL) {
        return PQ_NULL_ARGUMENT;
    }
    new_queue->head = createNode(queue->copy_element(queue->head->element),
        queue->copy_priority(queue->head->priority));
    if (new_queue->head == NULL || new_queue->head->element == NULL || new_queue->head->priority == NULL) {
        pqDestroy(new_queue);
        return PQ_NULL_ARGUMENT;
    }
    Node queue_iterator = queue->head->next;
    Node new_queue_iterator = new_queue->head;
    while (queue_iterator) { 
        new_queue_iterator->next = createNode(queue->copy_element(queue_iterator->element),
            queue->copy_priority(queue_iterator->priority));
        new_queue_iterator = new_queue_iterator->next;
        if (!new_queue_iterator || !(new_queue_iterator->element) || !(new_queue_iterator->priority)) {
            pqDestroy(new_queue);
            return PQ_NULL_ARGUMENT;
        }
        queue_iterator = queue_iterator->next;
    }
    return PQ_SUCCESS;
}
/*------------------------------------------------------------------------------------------*/

//pqCreate: Allocates a new empty priority queue.
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

//pqRemove: Removes the highest priority element from the priority queue.
PriorityQueueResult pqRemove(PriorityQueue queue) 
{
    if (queue == NULL) {
        return PQ_NULL_ARGUMENT;
    }
    queue->iterator = NULL;
    return removeHeadOrNextNode(queue, queue->head, true);
}

//pqClear: Removes all elements and priorities from target priority queue.
PriorityQueueResult pqClear(PriorityQueue queue) 
{
    if (queue == NULL) {
        return PQ_NULL_ARGUMENT;
    }
    while (queue->head) {
        PriorityQueueResult remove_result = pqRemove(queue);
        if (remove_result != PQ_SUCCESS) {
            return remove_result;
        }
    }
    queue->iterator = NULL;
    return PQ_SUCCESS;
}

//pqDestroy: Deallocates an existing priority queue.
void pqDestroy(PriorityQueue queue) 
{
    if (queue == NULL) {
        return;
    }
    if (queue->head) {
        pqClear(queue);
    }
    free(queue);
}

//pqCopy: Creates a copy of target priority queue.
PriorityQueue pqCopy(PriorityQueue queue) 
{
    if (queue == NULL) {
        return NULL;
    }
    queue->iterator = NULL;
    PriorityQueue new_queue = pqCreate(queue->copy_element, queue->free_element, 
        queue->equal_elements, queue->copy_priority, queue->free_priority, queue->compare_priorities);

    if (new_queue == NULL) {
        return NULL;
    }
    new_queue->iterator = NULL;
    if (pqCopyAllOrDestroy(new_queue, queue) != PQ_SUCCESS) {
        return NULL;
    }
    return new_queue;
}

//pqGetSize: Returns the number of elements in a priority queue.
int pqGetSize(PriorityQueue queue) 
{
    if (queue == NULL) {
        return SIZE_ERROR;
    }
    int pq_size = 0;
    Node iterator = queue->head;
    while (iterator) {
        iterator = iterator->next;
        ++pq_size;
    }
    return pq_size;
}

//pqContains: Checks if an element exists in the priority queue.
bool pqContains(PriorityQueue queue, PQElement element) 
{
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

//pqInsert: add a specified element with a specific priority.
PriorityQueueResult pqInsert(PriorityQueue queue, PQElement element, PQElementPriority priority) 
{
    if (queue == NULL || element == NULL || priority == NULL) {
        return PQ_NULL_ARGUMENT;
    }
    queue->iterator = NULL;
    Node new_node = createNode(queue->copy_element(element), queue->copy_priority(priority));
    if (new_node == NULL) {
        return PQ_OUT_OF_MEMORY;
    }
    if (queue->head == NULL) {
        queue->head = new_node;
        return PQ_SUCCESS;
    }
    if (queue->compare_priorities(queue->head->priority, priority) < 0) {
        new_node->next = queue->head;
        queue->head = new_node;
        return PQ_SUCCESS;
    }
    Node iterator = queue->head;
    while (iterator->next) {
        if (queue->compare_priorities(iterator->next->priority, priority) < 0) {
            new_node->next = iterator->next;
            iterator->next = new_node; 
            return PQ_SUCCESS;
        }
        iterator = iterator->next;
    }
    iterator->next = new_node;
    return PQ_SUCCESS;
}

//pqChangePriority: Changes a priority of specific element with a specific priority in the priority queue.
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
    Node to_delete = NULL;
    if (queue->compare_priorities(queue->head->priority, old_priority) == 0) {
        if (queue->equal_elements(queue->head->element, element)) {
            to_delete = queue->head;
        }
    }
    Node previous_to_delete = NULL;
    Node iterator = queue->head;
    while(iterator->next && to_delete == NULL) {
        if (queue->compare_priorities(iterator->next->priority, old_priority) == 0) {
            if (queue->equal_elements(iterator->next->element, element)) {
                previous_to_delete = iterator;
                to_delete = iterator->next;
                break;
            }
        }
        iterator = iterator->next;
    }
    if (to_delete != NULL) {
        if (pqInsert(queue, element, new_priority) != PQ_SUCCESS) {
            return PQ_OUT_OF_MEMORY;
        } 
        if (queue->compare_priorities(to_delete->priority, old_priority) == 0) {
            if (queue->equal_elements(to_delete->element, element)) {
                return removeHeadOrNextNode(queue, previous_to_delete, to_delete == queue->head);
            }
        }
        previous_to_delete = iterator->next;
        return removeHeadOrNextNode(queue, previous_to_delete, false);
    }
    return PQ_ELEMENT_DOES_NOT_EXISTS;
}

//pqRemoveElement: Removes the highest priority element from the priority queue which have its value equal to element.                    
PriorityQueueResult pqRemoveElement(PriorityQueue queue, PQElement element) 
{
    if (queue == NULL || element == NULL || queue->head == NULL) {
        return PQ_NULL_ARGUMENT;
    }
    queue->iterator = NULL;
    if (queue->equal_elements(queue->head->element, element)) {
        return removeHeadOrNextNode(queue, queue->head, true);
    }
    Node iterator = queue->head;
    while (iterator->next) {
        if (queue->equal_elements(iterator->next->element, element)) {
            return removeHeadOrNextNode(queue, iterator, false);
        }
        iterator = iterator->next;
    }
    return PQ_ELEMENT_DOES_NOT_EXISTS;
}

//pqGetFirst: Sets the internal iterator to the first element in the priority queue.
PQElement pqGetFirst(PriorityQueue queue) 
{
    if (queue == NULL || queue->head == NULL) {
        return NULL;
    }
    queue->iterator = queue->head;
    return queue->iterator->element;
}

//pqGetNext: Advances the priority queue iterator to the next element and returns it.
PQElement pqGetNext(PriorityQueue queue) 
{
    if (queue == NULL || queue->iterator == NULL || queue->iterator->next == NULL) {
        return NULL;
    }
    queue->iterator = queue->iterator->next;
    return queue->iterator->element;
}