#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "date.h"
#include "priority_queue.h"
#include "member.h"
#include "event_manager.h"

#define ERROR -1

/**
 * Defining the Member
 */

struct Member_t
{
    char* member_name;
    int member_id;
    int event_counter;
};

/**
 * Defining the Priority Member for the main list of members
 */

struct Priority_Member_t
{
    int member_id;
    int event_counter;
};

/**
 * createMember: Allocates a new member
 * 
 * @param member_name - The name of the new member
 * @param member_id - The id number of the new member
 * @param counter - Counts the events that linked to the member
 * @return
 *      NULL if the member_name is NULL
 *      A new member in case of success
 */

Member createMember(char* member_name,int member_id,int event_counter)
{
    if(!member_name)
    {
        return NULL;
    }
    Member member=malloc(sizeof(*member));
    if(!member)
    {
        return NULL;
    }
    member->member_name=malloc(strlen(member_name)+1);
    if(!member_name)
    {
        freeMember(member);
        return NULL;
    }
    strcpy(member->member_name,member_name);
    member->member_id=member_id;
    member->event_counter=event_counter;
    return member;
}

/**
 * copyMember: Copies the member to a new allocated member
 * 
 * @param member - The member we want to copy
 * @return
 *      NULL in case that member is NULL
 *      A new allocated member which is the same as the source
 */

PQElement copyMember(PQElement member)
{
    if (member == NULL)
    {
        return NULL;
    }
    Member new_member = malloc(sizeof(*new_member));
    if (new_member == NULL)
    {
        return NULL;
    }
    new_member->member_name=malloc(strlen(((Member)member)->member_name)+1);
    if(!(new_member->member_name))
    {
        freeMember(new_member);
        return NULL;
    }
    strcpy(new_member->member_name, ((Member)member)->member_name);
    new_member->member_id = ((Member)member)->member_id;
    new_member->event_counter=((Member)member)->event_counter;
    return new_member;
}

/**
 * freeMember: Deallocates the member
 * 
 * @param member - The member we want to deallocate
 * If the member is NULL, nothing will be done
 */

void freeMember(PQElement member)
{
    if(!member)
    {
        return;
    }
    free(((Member)member)->member_name);
    free(member);
}

/**
 * compareMember: Compares between the two members id
 * 
 * @param member1 - The first member for comparison
 * @param member2 - The second member for comparison
 * @return
 *      false in case that one of the members is NULL, or their id numbers are not equal
 *      true if the members id numbers are equal
 */

bool compareMember(PQElement member1,PQElement member2)
{
    if(!member1||!member2)
    {
        return false;
    }
    if(((Member)member1)->member_id==((Member)member2)->member_id)
    {
        return true;
    }
    return false;
}

/**
 * getMemberName: Returns the name of the member
 * 
 * @param member - The member which his name we want
 * @return
 *      NULL if member is NULL
 *      The member's name in case of succuess
 */

char* getMemberName(Member member)
{
    if (!member)
    {
        return NULL;
    }
    return member->member_name;
}

/**
 * getMemberID: Returns the member id number
 * 
 * @param member - The member whose id number we want
 * @return
 *      -1 in case that member is NULL
 *      the member's id number in case of success
 */

int getMemberID(Member member)
{
    if(!member)
    {
        return ERROR;
    }
    return member->member_id;
}

/**
 * copyMemberID: Allocates a new member id number which equal to the one it get
 * 
 * @param member_id - the member id number we want to copy
 * @return
 *      NULL in case that member_id is NULL
 *      An allocated copy of the member_id in case of success
 */

PQElementPriority copyMemberID(PQElementPriority member_id)
{
    if(!member_id)
    {
        return NULL;
    }
    int *new_member_id=malloc(sizeof(*new_member_id));
    *new_member_id=*(int*)member_id;
    return new_member_id;
}

/**
 * freeMemberID: Deallocates the member id number
 * 
 * @param member_id - the member id number we want to deallocate
 * If member_id is NULL, nothing will be done
 */

void freeMemberID(PQElementPriority member_id)
{
    free(member_id);
}

/**
 * compareMemberID: Compares the priority between two member id numbers
 * 
 * @param first_member_id - The first member id we want to compare
 * @param second_member_id - The second member id we want to compare
 * @return
 *      A positive value in case that the first id is lower
 *      0 in case that the two id numbers are equual
 *      A negative value in case that the second id is lower
 */

int compareMemberID(PQElementPriority first_member_id, PQElementPriority second_member_id)
{
    return (*(int*)second_member_id - *(int*)first_member_id);
}

/**
 * getMember: Returns the member who the member_id is his
 * 
 * @param queue - The members queue
 * @param member_id - The member idnumber we need for the search after the certain member
 * @return
 *      NULL in case the queue it get is NULL or empty
 *      The member in case of success
 */

Member getMember(PriorityQueue queue,int member_id)
{
    if(!queue)
    {
        return NULL;
    }
    Member iterator=pqGetFirst(queue);
    if(!iterator)
    {
        return NULL;
    }
    while(iterator)
    {
        if (getMemberID(iterator)==member_id)
        {
            return iterator;
        }
        iterator=pqGetNext(queue);
    }
    return NULL;
}

/**
 * getInvolvedEvents: Returns the amount of events that the member is linked with
 * 
 * @param member - The member who his counter of events we want to get
 * @return
 *      -1 in case we get NULL instead of member
 *      The amount of events that linked to the member
 */

int getInvolvedEvents(Member member)
{
    if(!member)
    {
        return ERROR;
    }
    return member->event_counter;
}

/**
 * addToInvolvedEvents: Adds to the event linked counter of the member
 * 
 * @param member - The member who his event linked counter we want to increase
 * In case it gets NULL instead of member, nothing will be done
 */

void addToInvolvedEvents(Member member)
{
    if(!member)
    {
        return;
    }
    ++(member->event_counter);
}

/**
 * subFromInvolvedEvents: Substracts from the event linked counter of the member
 * 
 * @param member - The member who his event linked counter we want to reduce
 * In case it gets NULL instead of member, nothing will be done
 */

void subFromInvolvedEvents(Member member)
{
    if(!member)
    {
        return;
    }
    --(member->event_counter);
}

/**
 * printMemberName: Prints the member name to the file which the outputDile is its pointer
 * 
 * @param member - The member whose name we want to print
 * @param outputFile - A pointer to the output file we want to print on
 * In case that one of the parameters are NULL, nothing will be done
 */

void printMemberName(Member member,FILE* outputFile)
{
    if(!member)
    {
        return;
    }
    fprintf(outputFile,",%s",member->member_name);
}

/**
 * createPriorityMember: Creates a priority member type, which helps us to use in ordered queue
 * 
 * @param member_id - The member id number of the member who linked to that type
 * @param event_counter - The event linked counter of the member who linked to that type
 * @return
 *      NULL in case of failed allocation
 *      A new priority member type in case of success
 */

PriorityMember createPriorityMember(int member_id,int event_counter)
{
    PriorityMember priority_member=malloc(sizeof(*priority_member));
    if(!priority_member)
    {
        return NULL;
    }
    priority_member->member_id=member_id;
    priority_member->event_counter=event_counter;
    return priority_member;
}

/**
 * copyMemberPriority: Copies a type of PriorityMember to an allocated one
 * 
 * @param member_priority - The priority we want to copy
 * @return
 *      NULL in case that the function get NULL instead of member_priority, and in case of failed allocated
 *      A new allocated PriorityMember which is equal to the one the function got in case of success
 */

PQElementPriority copyMemberPriority(PQElementPriority member_priority) 
{
    if (member_priority == NULL)
    {
        return NULL;
    }
    PriorityMember new_member_priority = malloc(sizeof(*new_member_priority));
    if (new_member_priority == NULL)
    {
        return NULL;
    }
    new_member_priority->event_counter = ((PriorityMember)member_priority)->event_counter;
    new_member_priority->member_id=((PriorityMember)member_priority)->member_id;

    return (PriorityMember)new_member_priority;
}

/**
 * freeMemberPriority: Deallocates the PriorityMember type
 * 
 * @param member_priority - The target PriorityMember to deallocate
 * in case of getting NULL instead of member_priority, nothing will be done
 */

void freeMemberPriority(PQElementPriority member_priority)  
{
    if(!member_priority)
    {
        return;
    }
    free((PriorityMember)member_priority);
}

/**
 * compareMemberPriority: Compares between two PriorityMember considering their event linked counter,
 *                        and their id numbers(in case their counters are equal)
 * 
 * @param first_member_priority - The first PriorityMember we want to compare
 * @param second_member_priority - The second PriorityMember we want to compare
 * @return
 *      A positive integer value in case that the first is in higher priority
 *      0 in case one of them is NULL, or their priority is equal(not likely to happen when their id is different)
 *      A negative integer value in case that the second is in higher priority
 */

int compareMemberPriority(PQElementPriority first_member_priority, PQElementPriority second_member_priority) 
{
    if(!first_member_priority||!second_member_priority)
    {
        return 0;
    }
    if ((((PriorityMember)first_member_priority)->event_counter) 
                                != (((PriorityMember)second_member_priority)->event_counter))
    {
        return (((PriorityMember)first_member_priority)->event_counter) 
                        - (((PriorityMember)second_member_priority)->event_counter);
    }
    return (((PriorityMember)second_member_priority)->member_id)-(((PriorityMember)first_member_priority)->member_id);
}

/**************************************/