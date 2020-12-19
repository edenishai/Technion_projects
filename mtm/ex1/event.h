#ifndef EVENT_H
#define EVENT_H

#include "member.h"
#include "event_manager.h"


typedef struct Event_t* Event;




Event createEvent(char* event_name,int event_id,Date date);

PQElement copyEvent(PQElement event);

void freeEvent(PQElement event);

void subAllEventMembers(EventManager em,Event event);

bool compareEvents(PQElement first_event, PQElement second_event);

Date getEventDate(Event event);

char* getEventName(Event event);

int getEventID(Event event);

Event getEvent(PriorityQueue queue,int event_id);

void changeDate(Event event,Date new_date);

EventManagerResult addMemberToEvent(Event event,char* member_name,int involved_events,int member_id);

EventManagerResult removeMemberFromEvent(Event event,int member_id);

void printEventMembersList(Event event,FILE* outputFile);

int negativeDateCompare(PQElementPriority first_date, PQElementPriority second_date);









/*typedef enum EventListResult_t {
    EL_NULL_ARGUMENT,
    EL_SUCCESS,
    EL_OUT_OF_MEMORY,
    EL_INVALID_DATE,
    EL_EVENT_ALREADY_EXISTS,
    EVENT_ID_ALREADY_EXISTS,
    EVENT_NOT_EXISTS,
    EVENT_ID_NOT_EXISTS,
    EVENT_AND_MEMBER_ALREADY_LINKED,
    EVENT_AND_MEMBER_NOT_LINKED
} EventListResult;



EventList createEventList(Date date);

void destroyEventList(EventList event_list);

Event createEvent(char* event_name,int event_id,Date date);

Event copyEvent(Event event);

Date returnPresentDate(EventList event_list);

EventListResult insertEvent(EventList event_list,Event event);

EventListResult isEventIDExist(EventList event_list,int event_id);

EventListResult isEventNameExistInDate(EventList event_list,char* event_name,Date date);

Event returnPreviousEventByID(EventList event_list,int event_id);

EventListResult removeEventByID(EventList event_list,int event_id);

EventListResult changeEventDate(EventList event_list,int event_id,Date date);

EventListResult eventListTick(EventList event_list,int days);

int eventsAmount(EventList event_list);

EventListResult linkMemberToEventByID(EventList event_list,MemberList member_list,int event_id,int member_id,char* member_name);

EventListResult removeMemberFromEventByID(EventList event_list,MemberList member_list,int event_id,int member_id);

void printEvents(EventList event_list,const char* file_name);

char* getNextEvent(EventList event_list);

Event returnEventByID(EventList event_list,int event_id);*/

#endif