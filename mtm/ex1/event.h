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

PriorityQueue getFirstPQStaff(Event event);


#endif