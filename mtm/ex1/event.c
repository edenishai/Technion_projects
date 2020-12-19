
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "date.h"
#include "priority_queue.h"
#include "member.h"
#include "event.h"
#include "event_manager.h"

#define ERROR -1

/**
 * Defining the Event
 */

struct Event_t
{
    char* event_name;
    int event_id;
    Date date;
    PriorityQueue staff;
};

/**
 * createEvent: Allocates a new Event
 * 
 * @param event_name - The name of the new event
 * @param event_id - The id number of the new event
 * @param date - the date when the event occures
 * NULL - if allocation failed or date is NULL
 * a new Event in case of success
 */

Event createEvent(char* event_name,int event_id,Date date)
{
    if(!event_name||!date)
    {
        return NULL;
    }
    Event event=malloc(sizeof(*event));
    if(!event)
    {
        return NULL;
    }
    event->event_name = malloc(strlen(event_name)+1);
    if (event->event_name == NULL)
    {
        freeEvent(event);
        return NULL;
    }
    event->staff=pqCreate(copyMember,freeMember,compareMember,copyMemberID,freeMemberID,compareMemberID);
    if(!(event->staff))
    {
        freeEvent(event);
        return NULL;
    }
    strcpy(event->event_name,event_name);
    event->date=dateCopy(date);
    event->event_id=event_id;
    return event;
}

/**
 * copyEvent: Copies the event to a new allocated event
 * 
 * @param event - The event we want to copy
 * Returns NULL if the event it get is NULL or a new copy of the event in case of success
 */

PQElement copyEvent(PQElement event)
{
    if(!event)
    {
        return NULL;
    }
    Event copy_event=createEvent(((Event)event)->event_name,((Event)event)->event_id,((Event)event)->date);
    if(!copy_event)
    {
        return NULL;
    }
    pqDestroy(copy_event->staff);
    copy_event->staff=pqCopy(((Event)event)->staff);
    if(!(copy_event->staff))
    {
        freeEvent(copy_event);
        return NULL;
    }
    return copy_event;
}

/**
 * freeEvent: Deallocates the event
 * 
 * @param event - The event we want to deallocate
 * If it get a NULL, nothing will be done, and the event will be deallocated in case of success
 */

void freeEvent(PQElement event)
{
    if (event == NULL)
    {
        return;
    } 
    dateDestroy(((Event)event)->date);
    free(((Event)event)->event_name);
    pqDestroy(((Event)event)->staff);
    free((Event)event);
}

/**
 * getFirstPQStaff: Returns a pointer to the first member in the event's member list
 * 
 * @param event: The event which it's member list we want
 * Returns NULL in case the event it get is NULL, or a pointer to the member list in case of success
 */

PriorityQueue getFirstPQStaff(Event event)
{
    if(!event)
    {
        return NULL;
    }
    return pqGetFirst(event->staff);
}

/**
 * compareEvents: Compares between two events and returns if their id is equal or not
 * 
 * @param first_event - The first event in the comparision
 * @param second_event - The second event in the comparision
 * Returns false in case the event id's are not equal or one of them is NULL,
 * and true in case their id is equal
 */

bool compareEvents(PQElement first_event, PQElement second_event) 
{
    if (first_event == NULL || second_event == NULL)
    {
        return false;
    }
    if (((Event)first_event)->event_id == ((Event)second_event)->event_id)
    {
        return true;
    }
    return false;
}

/**
 * getEventDate: Returns a pointer to the event's date
 * 
 * @param event - The event which its date we want
 * Returns NULL in case the event it recieve is NULL,
 * and a pointer to the date in case of success
 */

Date getEventDate(Event event)
{
    if(!event)
    {
        return NULL;
    }
    return event->date;
}

/**
 * getEventName: Returns the name of the event
 * 
 * @param event - The event which its name we want
 * Returns NULL in case the event it recieve is NULL,
 * or a pointer to the name in case of success
 */

char* getEventName(Event event)
{
    if(!event)
    {
        return NULL;
    }
    return event->event_name;
}

/** 
 * getEventName: Returns the id number of the event
 * 
 * @param event - The eveevnt ehivh its id number we want
 * Returns -1 in case the event it recieve is NULL,
 * or the integer value of the id in case of success
 */

int getEventID(Event event)
{
    if(!event)
    {
        return ERROR;
    }
    return event->event_id;
}

/**
 * getEvent: Returns a pointer to the event we want(according tto the id number)
 * 
 * @param queue - The priority queue of the event list
 * @param event_id - The id number of the event we want
 * Returns NULL in case the queue is NULL or the event id not exists in the queue,
 * or a pointer to the event in case of success(in finding the event)
 */

Event getEvent(PriorityQueue queue,int event_id)
{
    if(!queue)
    {
        return NULL;
    }
    Event iterator=pqGetFirst(queue);
    while(iterator)
    {
        if (getEventID(iterator)==event_id)
        {
            return iterator;
        }
        iterator=pqGetNext(queue);
    }
    return NULL;
}

/**
 * changeDate: Changes the date of the event
 * 
 * @param event - The event we want to change its date
 * @param new_date - The date we want to put in the date
 * If one of the parameters is NULL nothing will be done
 */

void changeDate(Event event,Date new_date)
{
    if(!event||!new_date)
    {
        return;
    }
    dateDestroy(event->date);
    event->date=dateCopy(new_date);
}

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

EventManagerResult addMemberToEvent(Event event,char* member_name,int involved_events,int member_id)
{
    if(!event||!member_name)
    {
        return EM_NULL_ARGUMENT;
    }
    Member member=createMember(member_name,member_id,involved_events);
    if(!member)
    {
        return EM_OUT_OF_MEMORY;
    }
    Member iterator=pqGetFirst(event->staff);
    while(iterator)
    {
        if (getMemberID(iterator)==member_id)
        {
            freeMember(member);
            return EM_EVENT_AND_MEMBER_ALREADY_LINKED;
        }
        iterator=pqGetNext(event->staff);
    }
    int* priority_member_id=malloc(sizeof(int));
    *priority_member_id=member_id;
    PriorityQueueResult result=pqInsert(event->staff,member,priority_member_id);
    freeMember(member);
    freeMemberID(priority_member_id);
    if(result==PQ_OUT_OF_MEMORY)
    {
        return EM_OUT_OF_MEMORY;
    }
    return EM_SUCCESS;
}

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

EventManagerResult removeMemberFromEvent(Event event,int member_id)
{
    if(!event)
    {
        return EM_NULL_ARGUMENT;
    }
    Member member=copyMember(getMember(event->staff,member_id));
    if(!member)
    {
        return EM_EVENT_AND_MEMBER_NOT_LINKED;
    }
    pqRemoveElement(event->staff,member);
    freeMember(member);
    return EM_SUCCESS;
}

/**
 * printDate: Prints a date
 * 
 * @param date - The date we want to print
 * @param outputFile - The pointer to the file we want to print in
 * If one of the parameters is NULL, nothing will be done
 */

static void printDate(Date date,FILE* outputFile)
{
    if(!date||!outputFile)
    {
        return;
    }
    int day,month,year;
    dateGet(date,&day,&month,&year);
    fprintf(outputFile,"%d.%d.%d",day,month,year);
}

/**
 * printEventMembersList: Prints all the members who linked with the event
 * 
 * @param event - The event which its members we want to print
 * @param outputFile - The pointer to the file we want to print in
 * If one of the parameters is NULL, nothing will be done
 */

void printEventMembersList(Event event,FILE* outputFile)
{
    if(!event||!outputFile)
    {
        return;
    }
    Member iterator=pqGetFirst(event->staff);
    fprintf(outputFile,"%s,",event->event_name);
    printDate(event->date,outputFile);
    while(iterator)
    {
        printMemberName(iterator,outputFile);
        iterator=pqGetNext(event->staff);
    }
    fprintf(outputFile,"\n");
}

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

int negativeDateCompare(PQElementPriority first_date, PQElementPriority second_date)
{
    return -(dateCompare(first_date,second_date));
}

/*******************************************************************************************/