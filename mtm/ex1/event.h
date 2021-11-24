#ifndef EVENT_H
#define EVENT_H

#include "member.h"
#include "event_manager.h"
#include "priority_queue.h"

/**
 * Type for defining the Event
 */
typedef struct Event_t* Event;


/**
 * createEvent: Allocates a new Event
 * 
 * @param event_name - The name of the new event
 * @param event_id - The id number of the new event
 * @param date - the date when the event occures
 * NULL - if allocation failed or date is NULL
 * a new Event in case of success
 */
Event createEvent(char* event_name,int event_id,Date date);

/**
 * copyEvent: Copies the event to a new allocated event
 * 
 * @param event - The event we want to copy
 * Returns NULL if the event it get is NULL or a new copy of the event in case of success
 */

PQElement copyEvent(PQElement event);

/**
 * freeEvent: Deallocates the event
 * 
 * @param event - The event we want to deallocate
 * If it get a NULL, nothing will be done, and the event will be deallocated in case of success
 */

void freeEvent(PQElement event);

/**
 * compareEvents: Compares between two events and returns if their id is equal or not
 * 
 * @param first_event - The first event in the comparision
 * @param second_event - The second event in the comparision
 * Returns false in case the event id's are not equal or one of them is NULL,
 * and true in case their id is equal
 */

bool compareEvents(PQElement first_event, PQElement second_event);

/**
 * getEventDate: Returns a pointer to the event's date
 * 
 * @param event - The event which its date we want
 * Returns NULL in case the event it recieve is NULL,
 * and a pointer to the date in case of success
 */

Date getEventDate(Event event);

/**
 * getEventName: Returns the name of the event
 * 
 * @param event - The event which its name we want
 * Returns NULL in case the event it recieve is NULL,
 * or a pointer to the name in case of success
 */

char* getEventName(Event event);

/** 
 * getEventName: Returns the id number of the event
 * 
 * @param event - The eveevnt ehivh its id number we want
 * Returns -1 in case the event it recieve is NULL,
 * or the integer value of the id in case of success
 */

int getEventID(Event event);

/**
 * getEvent: Returns a pointer to the event we want(according tto the id number)
 * 
 * @param queue - The priority queue of the event list
 * @param event_id - The id number of the event we want
 * Returns NULL in case the queue is NULL or the event id not exists in the queue,
 * or a pointer to the event in case of success(in finding the event)
 */

Event getEvent(PriorityQueue queue,int event_id);

/**
 * changeDate: Changes the date of the event
 * 
 * @param event - The event we want to change its date
 * @param new_date - The date we want to put in the date
 * If one of the parameters is NULL nothing will be done
 */

void changeDate(Event event,Date new_date);

/**
 * addMemberToEvent: Adds a member to the event
 * 
 * @param event - The event we want to link with the member
 * @param member_name - The name of the member we want to link with the event
 * @param return
 *      EM_NULL_ARGUMENT if a NULL was sent as one of the parameters
 *      EM_OUT_OF_MEMORY if an allocation failed
 *      EM_EVENT_AND_MEMBER_ALREADY_LINKED if the member and the event are already linked
 *      EM_SUCCESS if the member and the event were linked together successfuly
 */

EventManagerResult addMemberToEvent(Event event,char* member_name,int involved_events,int member_id);

/**
 * removeMemberFromEvent: Removes the member from the event
 * 
 * @param event - The event we want to delete the member from
 * @param member_id - The id number of the member we want to unlink from the event
 * @param return
 *      EM_NULL_ARGUMENT if a NULL was sent as one of the parameters
 *      EM_EVENT_AND_MEMBER_NOT_LINKED if the member and event are not linked anyway
 *      EM_SUCCESS if the member was removed from the event successfuly
 */

EventManagerResult removeMemberFromEvent(Event event,int member_id);

/**
 * printEventMembersList: Prints all the members who linked with the event
 * 
 * @param event - The event which its members we want to print
 * @param outputFile - The pointer to the file we want to print in
 * If one of the parameters is NULL, nothing will be done
 */

void printEventMembersList(Event event,FILE* outputFile);

/**
 * negativeDateCompare: Takes the result of the comparison between two dates in date.h, and multiplys it
 *                      by -1, for helping us to insert the events to PriorityQueue in the right order
 * 
 * @param first_date - The first date we want to compare
 * @param second_date - The second date we want to compare
 * Returns a positive number if the first date occurs first
 *           0 if thw two dates occurs in the same date, or one of them is NULL
 *           negative number if the second date occurs first
 */

int negativeDateCompare(PQElementPriority first_date, PQElementPriority second_date);

/**
 * getFirstPQStaff: Returns a pointer to the first member in the event's member list
 * 
 * @param event: The event which it's member list we want
 * Returns NULL in case the event it get is NULL, or a pointer to the member list in case of success
 */

PriorityQueue getFirstPQStaff(Event event);


#endif