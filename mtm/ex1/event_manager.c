#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "date.h"
#include "event_manager.h"
#include "priority_queue.h"
#include "event.h"
#include "member.h"

#define ERROR -1

/**
 * Defining the Event Manager
 */
struct EventManager_t
{
    PriorityQueue events_list;
    PriorityQueue main_members_list;
    Date present;
};

/**
 * createEventManager: Allocates a new Event Manager System
 * 
 * @param date - the date when the event manager starts
 * NULL - if allocation failed or date is NULL
 * a new Event Manager system in case of success
 */

EventManager createEventManager(Date date)
{
    if(!date)
    {
        return NULL;
    }
    EventManager em=malloc(sizeof(*em));
    if(!em)
    {
        return NULL;
    }
    int day,month,year;
    dateGet(date,&day,&month,&year);
    em->events_list=pqCreate(copyEvent,freeEvent,compareEvents,(CopyPQElementPriority)dateCopy,
                                (FreePQElementPriority)dateDestroy,(ComparePQElementPriorities)negativeDateCompare);
    em->main_members_list=pqCreate(copyMember,freeMember,compareMember,
                                copyMemberPriority,freeMemberPriority,compareMemberPriority);
    em->present=dateCreate(day,month,year);
    return em;
}

/**
 * destroyEventManager: Deallocates an existing Event Manager system
 * 
 * @param em - Target Event Manager system to be deallocated.
 * If em is NULL nothing will be done
 */

void destroyEventManager(EventManager em)
{
    if(!em)
    {
        return;
    }
    pqDestroy(em->main_members_list);
    pqDestroy(em->events_list);
    dateDestroy(em->present);
    free(em);
}

/**
 * removeAllEventMembers: Removes all the members of the specific event in em(the event manager)
 *                        Helps us to control the event counters of each member
 * 
 * @param em - The event manager which the event exists in
 * @param event - The event we want to empty from members
 * If em or event are NULL nothing will be done
 */

static void removeAllEventMembers(EventManager em,Event event)
{
    if(!em||!event)
    {
        return;
    }
    Member iterator=((Member)getFirstPQStaff(event));
    while(iterator)
    {
        int member_id=getMemberID(iterator);
        emRemoveMemberFromEvent(em,member_id,getEventID(event));
        iterator=((Member)getFirstPQStaff(event));
    }
}

/**
 * emAddEventByDate: Adds an event to the system in the specific date
 * 
 * @param em - The Event Manager system which we add the event to
 * @param event_name - The name of the new event
 * @param date - The date of the new event
 * @param event_id - The id number of the new event
 * @return
 *      EM_NULL_ARGUMENT if a NULL was sent as one of the parameters
 *      EM_OUT_OF_MEMORY if an allocation failed
 *      EM_INVALID_DATE if the date of the event occurs before the present date of the event manager
 *      EM_INVALID_EVENT_ID if the event id number is negative
 *      EM_EVENT_ALREADY_EXISTS if there is already an event with the same name in the same date in event manager
 *      EM_EVENT_ID_ALREAD_EXISTS if there is akready an event with the same id number in event manager
 *      EM_SUCCESS if the event was added succesfuly to the event manager
 */

EventManagerResult emAddEventByDate(EventManager em, char* event_name, Date date, int event_id)
{
    if(!em||!event_name||!date)
    {
        return EM_NULL_ARGUMENT;
    }
    if((dateCompare(em->present,date))>0)
    {
        return EM_INVALID_DATE;
    }
    if(event_id<0)
    {
        return EM_INVALID_EVENT_ID;
    }
    Event iterator=pqGetFirst(em->events_list);
    while(iterator!=NULL)
    {
        if(strcmp(getEventName(iterator),event_name)==0&&dateCompare(date,getEventDate(iterator))==0)
        {
            return EM_EVENT_ALREADY_EXISTS;
        }
        iterator=pqGetNext(em->events_list);
    }
    iterator=pqGetFirst(em->events_list);
    while(iterator)
    {
        if (getEventID(iterator)==event_id)
        {
            return EM_EVENT_ID_ALREADY_EXISTS;
        }
        iterator=pqGetNext(em->events_list);
    }
    Event event=createEvent(event_name,event_id,date);
    if(!event)
    {
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }
    PriorityQueueResult result=pqInsert(em->events_list,event,date);
    freeEvent(event);
    if(result!=PQ_OUT_OF_MEMORY)
    {
        return EM_SUCCESS;
    }
    destroyEventManager(em);
    return EM_OUT_OF_MEMORY;
}

/**
 * emAddEventByDiff: Adds an event to the system in the specific date
 * 
 * @param em - The Event Manager system which we add the event to
 * @param event_name - The name of the new event
 * @param days - The days from the present date of event manager to the date of the new event
 * @param event_id - The id number of the new event
 * @return
 *      EM_NULL_ARGUMENT if a NULL was sent as one of the parameters
 *      EM_OUT_OF_MEMORY if an allocation failed
 *      EM_INVALID_DATE if the number of days is negative(and therefore occures in the past)
 *      EM_INVALID_EVENT_ID if the event id number is negative
 *      EM_EVENT_ALREADY_EXISTS if there is already an event with the same name in the same date in event manager
 *      EM_EVENT_ID_ALREAD_EXISTS if there is akready an event with the same id number in event manager
 *      EM_SUCCESS if the event was added succesfuly to the event manager
 */

EventManagerResult emAddEventByDiff(EventManager em, char* event_name, int days, int event_id)
{
    if(!em||!event_name)
    {
        return EM_NULL_ARGUMENT;
    }
    if(days<0)
    {
        return EM_INVALID_DATE;
    }
    if(event_id<0)
    {
        return EM_INVALID_EVENT_ID;
    }
    Date present_date=dateCopy(em->present);
    if(!present_date)
    {
        return EM_OUT_OF_MEMORY;
    }
    for(int i=0;i<days;i++)
    {
        dateTick(present_date);
    }
    EventManagerResult result=emAddEventByDate(em,event_name,present_date,event_id);
    dateDestroy(present_date);
    return result;
}

/**
 * emRemoveEvent: Removes an event from the event manager system
 * 
 * @param em - The Event Manager system which we remove the event from
 * @param event_id - The id number of the event we want to remove
 * @param return
 *      EM_NULL_ARGUMENT if a NULL was sent as the parameter em
 *      EM_INVALID_EVENT_ID if the event id number us negative
 *      EM_NOT_EXISTS if there is no event with the id number in the event manager system
 *      EM_OUT_OF_MEMORY if an allocation failed
 *      EM_SUCCESS if the event was removed successfuly from the system
 */

EventManagerResult emRemoveEvent(EventManager em, int event_id)
{
    if(!em)
    {
        return EM_NULL_ARGUMENT;
    }
    if(event_id<0)
    {
        return EM_INVALID_EVENT_ID;
    }
    Event the_event=getEvent(em->events_list,event_id);
    if(!the_event)
    {
        return EM_EVENT_NOT_EXISTS;
    }
    removeAllEventMembers(em,the_event);
    PriorityQueueResult result=pqRemoveElement(em->events_list,the_event);
    if(result==PQ_OUT_OF_MEMORY)
    {
            return EM_OUT_OF_MEMORY;
    }
    return EM_SUCCESS;
}

/**
 * emChangeEventDate: Changes the event's date of the date which the event id belongs to
 * 
 * @param em - The Event Manager system which the event exists in
 * @param event_id - The id number of the event we want to change
 * @param new_date - The new date of the event
 * @param return
 *      EM_NULL_ARGUMENT if a NULL was sent as one of the parameters
 *      EM_INVALID_DATE if the date of the event occurs before the present date of the event manager
 *      EM_INVALID_EVENT_ID if the event id number us negative
 *      EM_EVENT_ID_NOT_EXISTS if the event id not exists in the event manager system
 *      EM_EVENT_ALREADY_EXISTS if there is already an event with the same name in the same date in event manager
 *      EM_OUT_OF_MEMORY if an allocation failed
 *      EM_SUCCESS if the event's date was changed successfuly
 */

EventManagerResult emChangeEventDate(EventManager em, int event_id, Date new_date)
{
    if(!em||!new_date)
    {
        return EM_NULL_ARGUMENT;
    }
    if(dateCompare(new_date,em->present)<0)
    {
        return EM_INVALID_DATE;
    }
    if(event_id<0)
    {
        return EM_INVALID_EVENT_ID;
    }
    Event event=getEvent(em->events_list,event_id);
    if(!event)
    {
        return EM_EVENT_ID_NOT_EXISTS;
    }
    Event iterator=pqGetFirst(em->events_list);
    while(iterator)
    {
        if((strcmp(getEventName(iterator),getEventName(event))==0)&&
                    (dateCompare(getEventDate(iterator),new_date)==0))
        {
            return EM_EVENT_ALREADY_EXISTS;
        }
        iterator=pqGetNext(em->events_list);
    }
    Date copy_date=dateCopy(getEventDate(event));
    changeDate(event,new_date);
    if(pqChangePriority(em->events_list,event,copy_date,new_date)==PQ_OUT_OF_MEMORY)
    {
        changeDate(event,copy_date);
        dateDestroy(copy_date);
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }
    dateDestroy(copy_date);
    return EM_SUCCESS;
}

/**
 * emAddMember: Adds a member to the total list of members
 * 
 * @param em - The Event Manager system which the member will be added to
 * @param member_name - The name of the new member
 * @param member_id - The id number of the new member
 * @param return
 *      EM_NULL_ARGUMENT if a NULL was sent as one of the parameters
 *      EM_INVALID_MEMBER_ID if the id number is negative
 *      EM_MEMBER_ID_ALREADY_EXISTS if the member id number is already exists in the system
 *      EM_OUT_OF_MEMORY if an allocation failed
 *      EM_SUCCESS if the member was added to the system successfuly
 */

EventManagerResult emAddMember(EventManager em, char* member_name, int member_id)
{
    if(!em||!member_name)
    {
        return EM_NULL_ARGUMENT;
    }
    if(member_id<0)
    {
        return EM_INVALID_MEMBER_ID;
    }
    Member iterator=pqGetFirst(em->main_members_list);
    while(iterator)
    {
        if (getMemberID(iterator)==member_id)
        {
            return EM_MEMBER_ID_ALREADY_EXISTS;
        }
        iterator=pqGetNext(em->main_members_list);
    }
    Member member=createMember(member_name,member_id,0);
    PriorityMember priority_member=createPriorityMember(member_id,0);
    if(!priority_member)
    {
        freeMember(member);
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }
    PriorityQueueResult result=pqInsert(em->main_members_list,member,priority_member);
    freeMemberPriority(priority_member);
    freeMember(member);
    if(result==PQ_OUT_OF_MEMORY)
    {
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }
    return EM_SUCCESS;
}

/**
 * emAddMemberToEvent: Adds a member in charge of an event
 * 
 * @param em - The event manager system we deal with
 * @param member_id - The id number of the member
 * @param event_id - the id number of the event we want to link to the member
 * @param return
 *      EM_NULL_ARGUMENT if a NULL was sent as one of the parameters
 *      EM_INVALID_EVENT_ID if the event id number us negative
 *      EM_INVALID_MEMBER_ID if the id number is negative
 *      EM_EVENT_ID_NOT_EXISTS if the event id not exists in the event manager system
 *      EM_MEMBER_ID_NOT_EXISTS if the member id not exists in the event manager system
 *      EM_OUT_OF_MEMORY if an allocation failed
 *      EM_SUCCESS if the member was linked to the event successfuly
 */

EventManagerResult emAddMemberToEvent(EventManager em, int member_id, int event_id)
{
    if (!em)
    {
        return EM_NULL_ARGUMENT;
    }
    if(event_id<0)
    {
        return EM_INVALID_EVENT_ID;
    }
    if(member_id<0)
    {
        return EM_INVALID_MEMBER_ID;
    }
    Event event=getEvent(em->events_list,event_id);
    if(!event)
    {
        return EM_EVENT_ID_NOT_EXISTS;
    }
    Member member=getMember(em->main_members_list,member_id);
    if(!member)
    {
        return EM_MEMBER_ID_NOT_EXISTS;
    }
    EventManagerResult result=addMemberToEvent(event,getMemberName(member),0,getMemberID(member));
    if(result==EM_SUCCESS)
    {
        Member copy_member=copyMember(member);
        if(!copy_member)
        {
            destroyEventManager(em);
            return EM_OUT_OF_MEMORY;
        }
        addToInvolvedEvents(copy_member);
        int event_counter=getInvolvedEvents(copy_member);
        pqRemoveElement(em->main_members_list,member);
        PriorityMember new_priority=createPriorityMember(member_id,event_counter);
        if(!new_priority)
        {
            freeMember(copy_member);
            destroyEventManager(em);
            return EM_OUT_OF_MEMORY;
        }
        pqInsert(em->main_members_list,copy_member,new_priority);
        freeMember(copy_member);
        freeMemberPriority(new_priority);
    }
    return result;
}

/**
 * emRemoveMemberFromEvent: Removes a member from the list member who in charge of the event
 * 
 * @param em - The event manager which the event exists in
 * @param member_id - The id number of the member
 * @param event_id - the id number of the event we wat to unlink from the member
 * @param return
 *      EM_NULL_ARGUMENT if a NULL was sent as one of the parameters
 *      EM_INVALID_EVENT_ID if the event id number us negative
 *      EM_INVALID_MEMBER_ID if the id number is negative
 *      EM_EVENT_ID_NOT_EXISTS if the event id not exists in the event manager system
 *      EM_MEMBER_ID_NOT_EXISTS if the member id not exists in the event manager system
 *      EM_OUT_OF_MEMORY if an allocation failed
 *      EM_SUCCESS if the member was unlinked from the event successfuly
 */

EventManagerResult emRemoveMemberFromEvent (EventManager em, int member_id, int event_id)
{
    if (!em)
    {
        return EM_NULL_ARGUMENT;
    }
    if(event_id<0)
    {
        return EM_INVALID_EVENT_ID;
    }
    if(member_id<0)
    {
        return EM_INVALID_MEMBER_ID;
    }
    Event event=getEvent(em->events_list,event_id);
    if(!event)
    {
        return EM_EVENT_ID_NOT_EXISTS;
    }
    Member member=getMember(em->main_members_list,member_id);
    if(!member)
    {
        return EM_MEMBER_ID_NOT_EXISTS;
    }
    EventManagerResult result=removeMemberFromEvent(event,getMemberID(member));
    if(result==EM_SUCCESS)
    {
        Member copy_member=copyMember(member);
        if(!copy_member)
        {
            destroyEventManager(em);
            return EM_OUT_OF_MEMORY;
        }
        subFromInvolvedEvents(copy_member);
        int event_counter=getInvolvedEvents(copy_member);
        pqRemoveElement(em->main_members_list,member);
        PriorityMember new_priority=createPriorityMember(member_id,event_counter);
        if(!new_priority)
        {
            freeMember(copy_member);
            destroyEventManager(em);
            return EM_OUT_OF_MEMORY;
        }
        pqInsert(em->main_members_list,copy_member,new_priority);
        freeMember(copy_member);
        freeMemberPriority(new_priority);
    }
    return result;
}

/**
 * emTick: Increases the present day of the event manager system by tthe number of days(days parameter)
 * 
 * @param em - The event manager system we want to change the present day in
 * @param days - The number of days we want to increase in the present date of the event manager
 * @param return
 *      EM_NULL_ARGUMENT if a NULL was sent as one of the parameters
 *      EM_INVALID_DATE if the numbers of days is illegal(negative or zero)
 *      EM_SUCCESS if the date of the system was succesfuly increased
 */

EventManagerResult emTick(EventManager em, int days)
{
    if(!em)
    {
        return EM_NULL_ARGUMENT;
    }
    if(days<=0)
    {
        return EM_INVALID_DATE;
    }
    for(int i=0;i<days;i++)
    {
        dateTick(em->present);
        while(dateCompare(getEventDate(pqGetFirst(em->events_list)),em->present)<0)
        {
            emRemoveEvent(em,getEventID(pqGetFirst(em->events_list)));
        }
    }
    return EM_SUCCESS;
}

/**
 * emGetEventsAmount: Returns the number of events which exist in the event manager system
 * 
 * @param em - The system we want to count it's events
 * If the em is NULL, return -1
 */

int emGetEventsAmount(EventManager em)
{
    if(!em)
    {
        return ERROR;
    }
    return pqGetSize(em->events_list);
}

/**
 * emGetNextEvent: Returns the next event's name
 * 
 * @param em - The system we deal with
 * returns NULL if em is NULL, or allocation was failed
 */

char* emGetNextEvent(EventManager em)
{
    if(!em)
    {
        return NULL;
    }
    Event iterator=pqGetFirst(em->events_list);
    if(!iterator)
    {
        return NULL;
    }
    return getEventName(iterator);
}

/**
 * emPrintAllEvents: Prints all the event list with the dates and the members list of each event
 *                   in the file which called file_name
 * 
 * @param em - The event manager system which it's events we want to print
 * @param file_name - The file name we want to print in
 * If em is NULL so nothing will be done
 */

void emPrintAllEvents(EventManager em, const char* file_name)
{
    if(!em)
    {
        return;
    }
    FILE *fp=fopen(file_name,"w");
    Event iterator=pqGetFirst(em->events_list);
    while(iterator)
    {
        printEventMembersList(iterator,fp);
        iterator=pqGetNext(em->events_list);
    }
    fclose(fp);
}

/**
 * emPrintAllResponsileMembers: Prints all the members in the list which in charge of at least one event
 *                              with the number of events they are in charge on
 * 
 * @param em - The event manager system which it's members we want to print
 * @param file_name - The file we want to print in
 * If em is NULL so nothing will be done
 */

void emPrintAllResponsibleMembers(EventManager em, const char* file_name)
{
    Member iterator=pqGetFirst(em->main_members_list);
    FILE *fp=fopen(file_name,"w");
    while(iterator)
    {
        if(getInvolvedEvents(iterator)>0)
        {
            fprintf(fp,"%s,%d\n",getMemberName(iterator),getInvolvedEvents(iterator));
        }
        iterator=pqGetNext(em->main_members_list);
    }
    fclose(fp);
}

/*******************************************************************************************/