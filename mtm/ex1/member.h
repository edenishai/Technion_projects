#ifndef MEMBER_H
#define MEMBER_H

#include "event_manager.h"
#include "event.h"

/**
 * Defining the Member
 */

typedef struct Member_t* Member;

/**
 * Defining the Priority Member for the main list of members
 */

typedef struct Priority_Member_t* PriorityMember;

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

Member createMember(char* member_name,int member_id,int event_counter);

/**
 * copyMember: Copies the member to a new allocated member
 * 
 * @param member - The member we want to copy
 * @return
 *      NULL in case that member is NULL
 *      A new allocated member which is the same as the source
 */

PQElement copyMember(PQElement member);

/**
 * freeMember: Deallocates the member
 * 
 * @param member - The member we want to deallocate
 * If the member is NULL, nothing will be done
 */

void freeMember(PQElement member);

/**
 * compareMember: Compares between the two members id
 * 
 * @param member1 - The first member for comparison
 * @param member2 - The second member for comparison
 * @return
 *      false in case that one of the members is NULL, or their id numbers are not equal
 *      true if the members id numbers are equal
 */

bool compareMember(PQElement member1,PQElement member2);

/**
 * getMemberName: Returns the name of the member
 * 
 * @param member - The member which his name we want
 * @return
 *      NULL if member is NULL
 *      The member's name in case of succuess
 */

char* getMemberName(Member member);

/**
 * getMemberID: Returns the member id number
 * 
 * @param member - The member whose id number we want
 * @return
 *      -1 in case that member is NULL
 *      the member's id number in case of success
 */

int getMemberID(Member member);

/**
 * copyMemberID: Allocates a new member id number which equal to the one it get
 * 
 * @param member_id - the member id number we want to copy
 * @return
 *      NULL in case that member_id is NULL
 *      An allocated copy of the member_id in case of success
 */

PQElementPriority copyMemberID(PQElementPriority member_id);

/**
 * freeMemberID: Deallocates the member id number
 * 
 * @param member_id - the member id number we want to deallocate
 * If member_id is NULL, nothing will be done
 */

void freeMemberID(PQElementPriority member_id);

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

int compareMemberID(PQElementPriority first_member_id, PQElementPriority second_member_id);

/**
 * getMember: Returns the member who the member_id is his
 * 
 * @param queue - The members queue
 * @param member_id - The member idnumber we need for the search after the certain member
 * @return
 *      NULL in case the queue it get is NULL or empty
 *      The member in case of success
 */

Member getMember(PriorityQueue queue,int member_id);

/**
 * getInvolvedEvents: Returns the amount of events that the member is linked with
 * 
 * @param member - The member who his counter of events we want to get
 * @return
 *      -1 in case we get NULL instead of member
 *      The amount of events that linked to the member
 */

int getInvolvedEvents(Member member);

/**
 * addToInvolvedEvents: Adds to the event linked counter of the member
 * 
 * @param member - The member who his event linked counter we want to increase
 * In case it gets NULL instead of member, nothing will be done
 */

void addToInvolvedEvents(Member member);

/**
 * subFromInvolvedEvents: Substracts from the event linked counter of the member
 * 
 * @param member - The member who his event linked counter we want to reduce
 * In case it gets NULL instead of member, nothing will be done
 */

void subFromInvolvedEvents(Member member);

/**
 * printMemberName: Prints the member name to the file which the outputDile is its pointer
 * 
 * @param member - The member whose name we want to print
 * @param outputFile - A pointer to the output file we want to print on
 * In case that one of the parameters are NULL, nothing will be done
 */

void printMemberName(Member member,FILE* outputFile);

/**
 * createPriorityMember: Creates a priority member type, which helps us to use in ordered queue
 * 
 * @param member_id - The member id number of the member who linked to that type
 * @param event_counter - The event linked counter of the member who linked to that type
 * @return
 *      NULL in case of failed allocation
 *      A new priority member type in case of success
 */

PriorityMember createPriorityMember(int member_id,int event_counter);

/**
 * copyMemberPriority: Copies a type of PriorityMember to an allocated one
 * 
 * @param member_priority - The priority we want to copy
 * @return
 *      NULL in case that the function get NULL instead of member_priority, and in case of failed allocated
 *      A new allocated PriorityMember which is equal to the one the function got in case of success
 */

PQElementPriority copyMemberPriority(PQElementPriority member_priority);

/**
 * freeMemberPriority: Deallocates the PriorityMember type
 * 
 * @param member_priority - The target PriorityMember to deallocate
 * in case of getting NULL instead of member_priority, nothing will be done
 */

void freeMemberPriority(PQElementPriority member_priority);

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

int compareMemberPriority(PQElementPriority first_member_priority, PQElementPriority second_member_priority);


#endif