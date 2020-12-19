
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
    event->event_name = malloc(sizeof(char)*(strlen(event_name)+1));
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

void subAllEventMembers(EventManager em,Event event){
    if(!em||!event){
        return;
    }
    Member iterator=pqGetFirst(event->staff);
    while(iterator){
        Member copy=iterator;
        iterator=pqGetNext(event->staff);
        emRemoveMemberFromEvent(em,getMemberID(copy),event->event_id);//////
    }
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
/*    if (strcmp(((Event)first_event)->event_name, ((Event)second_event)->event_name)) {
        return true;
    }*/
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
/*******************************************************************************************/
void changeDate(Event event,Date new_date){
    if(!event||!new_date){
        return;
    }
    dateDestroy(event->date);
    event->date=dateCopy(new_date);
}
/*******************************************************************************************/
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
    PriorityQueueResult result=pqInsert(event->staff,member,getMemberIDPointer(member));///////////
    if(result==PQ_OUT_OF_MEMORY){
        return EM_OUT_OF_MEMORY;
    }
    freeMember(member);
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

void printEventMembersList(Event event,FILE* outputFile){
    if(!event){
        return;
    }
    Member iterator=pqGetFirst(event->staff);
    fprintf(outputFile,"%s,",event->event_name);
    printDate(event->date,outputFile);
/*    printMemberName(iterator,outputFile);
    iterator=pqGetNext(event->staff);*/
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

/*
EventList createEventList(Date date){
    if(!date){
        return NULL;
    }
    EventList event_list = malloc(sizeof(*event_list));
    if(!event_list){
        return NULL;
    }
    event_list->present=dateCreate(getDay(date),getMonthNum(date),getYear(date));
    event_list->head=NULL;
    return event_list;
}

Event createEvent(char* event_name,int event_id,Date date){
    if(!date){
        return NULL;
    }
    Event event=malloc(sizeof(*event));
    if(!event){
        free(event);
        return NULL;
    }
    event->date=dateCreate(getDay(date),getMonthNum(date),getYear(date));
    event->event_name=malloc(sizeof(strlen(event_name)+1));
    strcpy(event->event_name,event_name);
    event->event_id=event_id;
    event->date=date;
    event->staff=createMemberList();
    return event;
}

 Event copyEvent(Event event){
    Event copy;
    strcpy(copy->event_name,event->event_name);
    copy->event_id=event->event_id;
    copy->staff=pqCopy(event->staff);
    return copy;
}

EventListResult insertEvent(EventList event_list,Event event){
    if(!event||!event_list){
        return EL_OUT_OF_MEMORY;
    }
    if(dateCompare(event->date,event_list->present)<0){
        return EL_INVALID_DATE;
    }
    if(isEventNameExistInDate(event_list,event->event_name,event->date)==EVENT_ALREADY_EXISTS){
        return EVENT_ALREADY_EXISTS;
    }
    Event iterator=event_list->head;
    while (iterator)
    {
        if(dateCompare(iterator->next->date,event->date)>0){
            event->next=iterator->next;
            iterator->next=event;
            return EVENT_LIST_SUCCESS;
        }
        iterator=iterator->next;
    }
    
     while(dateCompare(iterator->next->date,event->date)<=0&&iterator->next){
        iterator=iterator->next;
    }
    event->next=iterator->next;
    iterator->next=event;
    return EVENT_LIST_SUCCESS;
}

EventListResult isEventIDExist(EventList event_list,int event_id){
    Event iterator=event_list->head;
    while(iterator){
        if(iterator->event_id==event_id){
            return EVENT_ID_ALREADY_EXISTS;
        }
    }
    return EVENT_ID_NOT_EXISTS;
}

EventListResult isEventNameExistInDate(EventList event_list,char* event_name,Date date){
    if(!event_list||!event_name||!date){
        return EVENT_NOT_EXISTS;
    }
    Event iterator=event_list->head;
    while(iterator){
        if(!strcmp(iterator->event_name,event_name)&&dateCompare(iterator->date,date)==0){
            return EVENT_ALREADY_EXISTS;
        }
        iterator=iterator->next;
    }
    return EVENT_NOT_EXISTS;
}

Event returnPreviousEventByID(EventList event_list,int event_id){
    Event iterator=event_list->head;
    while(iterator){
        if(iterator->next->event_id==event_id){
            return iterator;
        }
    }
    return NULL;
}

void destroyEventList(EventList event_list){
    if(!event_list){
        return;
    }
    while(event_list->head){
        destroyMemberList(event_list->head->staff);
        dateDestroy(event_list->head->date);
        Event toDelete=event_list->head;
        event_list->head=event_list->head->next;
        free(toDelete);
    }
    dateDestroy(event_list->present);
    free(event_list);
}

Date returnPresentDate(EventList event_list){
    if(!event_list){
        return NULL;
    }
    return event_list->present;
}

EventListResult removeEventByID(EventList event_list,int event_id){
    Event iterator=event_list->head;
    while(iterator){
        if(iterator->next->event_id==event_id){
            destroyMemberList(event_list->head->staff);
            Event toDelete=iterator->next;
            iterator->next=iterator->next->next;
            free(toDelete);
            return EVENT_LIST_SUCCESS;
        }
    }
    return EVENT_NOT_EXISTS;
}

EventListResult changeEventDate(EventList event_list,int event_id,Date date){
    Event event=returnPreviousEventByID(event_list,event_id);
    if(!event){
        return EVENT_ID_NOT_EXISTS;
    }
    Event theEvent=event->next;
    event->next=event->next->next;
    theEvent->date=date;
    return insertEvent(event_list,theEvent);
}

EventListResult eventListTick(EventList event_list,int days){
    for(int i=0;i<days;i++){
        while(dateCompare(event_list->present,event_list->head->date)==0){
            Event toDelete=event_list->head;
            event_list->head=event_list->head->next;
            free(toDelete);
        }
        dateTick(event_list->present);
    }
    return EVENT_LIST_SUCCESS;
}

int eventsAmount(EventList event_list){
    Event event=event_list->head;
    int counter=0;
    while(event){
        ++counter;
        event=event->next;
    }
    return counter;
}

char* getNextEvent(EventList event_list){
    return event_list->head->event_name;
}

 static int copyMemberID(int member_id){
    return member_id;
}

static void removeMemberID(int member_id){
    return;
}

static int compareMemberID(int member_id1,int member_id2){
    return member_id1-member_id2;
}

EventListResult linkMemberToEventByID(EventList event_list ,MemberList member_list ,int event_id,int member_id,char* member_name){
    if(!event_list ||!member_list ){
        return EL_NULL_ARGUMENT;
    }
    Event event=event_list->head;
    while(event&&event->event_id!=event_id){
        event=event->next;
    }
    if(isMemberAlreadyExists(event->staff,member_id)==MEMBER_ID_ALREADY_EXISTS){
        return EVENT_AND_MEMBER_ALREADY_LINKED;
    }
    MemberListResult result=insertMember(event->staff ,getMemberName(member_list,member_id) ,member_name,member_id);
    if(result==MEMBER_LIST_SUCCESS){
 //       addToCounter(member_list,member_id);
        return EVENT_LIST_SUCCESS;
    }
    return EVENT_LIST_SUCCESS;
}

EventListResult removeMemberFromEventByID(EventList event_list ,MemberList member_list ,int event_id,int member_id){
    if(!event_list ||!member_list ){
        return EL_NULL_ARGUMENT;
    }
    Event event=event_list->head;
    while(event&&event->event_id!=event_id){
        event=event->next;
    }
    if(isMemberAlreadyExists(event->staff,member_id)==MEMBER_ID_NOT_EXISTS){
        return EVENT_AND_MEMBER_NOT_LINKED;
    }
    MemberListResult result=removeMember(event->staff,member_id);
    if(result==MEMBER_LIST_SUCCESS){
//      reduceFromCounter(member_list,member_id);
        return EVENT_LIST_SUCCESS;
    }
    return EVENT_LIST_SUCCESS;
}

void printEvents(EventList event_list,const char* file_name){
    Event event=event_list->head;
    FILE *fp=fopen(file_name,"+w");
    while(event){
        fprintf(fp,"%s,",event->event_name);
        printDate(event->date,file_name);
        printMemberList(event->staff,file_name);
    }
    fclose(fp);
} */