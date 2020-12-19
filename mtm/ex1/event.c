
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "date.h"
#include "priority_queue.h"
#include "member.h"
#include "event.h"
#include "event_manager.h"

#define ERROR -1

/*******************************************************************************************/

struct Event_t{
    char* event_name;
    int event_id;
    Date date;
    PriorityQueue staff;
};

/*******************************************************************************************/

Event createEvent(char* event_name,int event_id,Date date){
    if(!event_name||!date){
        return NULL;
    }
    Event event=malloc(sizeof(*event));
    if(!event){
        return NULL;
    }
    event->event_name = malloc(strlen(event_name)+1);
    if (event->event_name == NULL) {
        freeEvent(event);
        return NULL;
    }
    event->staff=pqCreate(copyMember,freeMember,compareMember,copyMemberID,freeMemberID,compareMemberID);
    if(!(event->staff)){
        freeEvent(event);
        return NULL;
    }
    strcpy(event->event_name,event_name);
    event->date=dateCopy(date);
    event->event_id=event_id;
    return event;
}

/*******************************************************************************************/

PQElement copyEvent(PQElement event){
    if(!event){
        return NULL;
    }
    Event copy_event=createEvent(((Event)event)->event_name,((Event)event)->event_id,((Event)event)->date);
    if(!copy_event){
        return NULL;
    }
    pqDestroy(copy_event->staff);
    copy_event->staff=pqCopy(((Event)event)->staff);
    if(!(copy_event->staff)){
        freeEvent(copy_event);
        return NULL;
    }
    return copy_event;
}

/*******************************************************************************************/

void freeEvent(PQElement event){
    if (event == NULL) {
        return;
    } 
    dateDestroy(((Event)event)->date);
    free(((Event)event)->event_name);
    pqDestroy(((Event)event)->staff);
    free((Event)event);
}

/*******************************************************************************************/

PriorityQueue getFirstPQStaff(Event event){
    if(!event){
        return NULL;
    }
    return pqGetFirst(event->staff);
}

/*******************************************************************************************/

bool compareEvents(PQElement first_event, PQElement second_event) 
{
    if (first_event == NULL || second_event == NULL) {
        return false;
    }
    if (((Event)first_event)->event_id == ((Event)second_event)->event_id) {
        return true;
    }
    return false;
}

/*******************************************************************************************/

Date getEventDate(Event event){
    if(!event){
        return NULL;
    }
    return event->date;
}

/*******************************************************************************************/

char* getEventName(Event event){
    if(!event){
        return NULL;
    }
    return event->event_name;
}

/*******************************************************************************************/

int getEventID(Event event){
    if(!event){
        return ERROR;
    }
    return event->event_id;
}

/*******************************************************************************************/

Event getEvent(PriorityQueue queue,int event_id){
    if(!queue){
        return NULL;
    }
    Event iterator=pqGetFirst(queue);
    while(iterator){
        if (getEventID(iterator)==event_id)
        {
            return iterator;
        }
        iterator=pqGetNext(queue);
    }
    return NULL;
}

/*******************************************************************************************/

void changeDate(Event event,Date new_date){
    if(!event||!new_date){
        return;
    }
    dateDestroy(event->date);
    event->date=dateCopy(new_date);
}

/*******************************************************************************************/

EventManagerResult addMemberToEvent(Event event,char* member_name,int involved_events,int member_id){
    if(!event||!member_name){
        return EM_NULL_ARGUMENT;
    }
    Member member=createMember(member_name,member_id,involved_events);
    if(!member){
        return EM_OUT_OF_MEMORY;
    }
    Member iterator=pqGetFirst(event->staff);
    while(iterator){
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
    if(result==PQ_OUT_OF_MEMORY){
        return EM_OUT_OF_MEMORY;
    }
    return EM_SUCCESS;
}

/*******************************************************************************************/

EventManagerResult removeMemberFromEvent(Event event,int member_id){
    if(!event){
        return EM_NULL_ARGUMENT;
    }
    Member member=copyMember(getMember(event->staff,member_id));
    if(!member){
        return EM_EVENT_AND_MEMBER_NOT_LINKED;
    }
    pqRemoveElement(event->staff,member);
    freeMember(member);
    return EM_SUCCESS;
}

/*******************************************************************************************/

static void printDate(Date date,FILE* outputFile){
    if(!date){
        return;
    }
    int day,month,year;
    dateGet(date,&day,&month,&year);
    fprintf(outputFile,"%d.%d.%d",day,month,year);
}

/*******************************************************************************************/

void printEventMembersList(Event event,FILE* outputFile){
    if(!event){
        return;
    }
    Member iterator=pqGetFirst(event->staff);
    fprintf(outputFile,"%s,",event->event_name);
    printDate(event->date,outputFile);
    while(iterator){
        printMemberName(iterator,outputFile);
        iterator=pqGetNext(event->staff);
    }
    fprintf(outputFile,"\n");
}

/*******************************************************************************************/

int negativeDateCompare(PQElementPriority first_date, PQElementPriority second_date){
    return -(dateCompare(first_date,second_date));
}

/*******************************************************************************************/