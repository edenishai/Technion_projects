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

/*******************************************************************************************/

struct EventManager_t{
    PriorityQueue events_list;
    PriorityQueue main_members_list;
    Date present;
};

/*******************************************************************************************/

EventManager createEventManager(Date date){
    if(!date){
        return NULL;
    }
    EventManager em=malloc(sizeof(*em));
    if(!em){
        return NULL;
    }
    em->events_list=pqCreate(copyEvent,freeEvent,compareEvents,dateCopy,dateDestroy,negativeDateCompare);
    em->main_members_list=pqCreate(copyMember,freeMember,compareMember,copyMemberPriority,freeMemberPriority,compareMemberPriority);
    em->present=dateCreate(getDay(date),getMonthNum(date),getYear(date));
    return em;
}

/********************************************************************************************/

void destroyEventManager(EventManager em){
    if(!em){
        return;
    }
    pqDestroy(em->main_members_list);
    pqDestroy(em->events_list);
    dateDestroy(em->present);
    free(em);
}

/*******************************************************************************************/

EventManagerResult emAddEventByDate(EventManager em, char* event_name, Date date, int event_id){
    if(!em||!event_name||!date){
        return EM_NULL_ARGUMENT;
    }
    if((dateCompare(em->present,date))>0){
        return EM_INVALID_DATE;
    }
    if(event_id<0){
        return EM_INVALID_EVENT_ID;
    }
    Event iterator=pqGetFirst(em->events_list);
    while(iterator!=NULL){
        if(strcmp(getEventName(iterator),event_name)==0&&dateCompare(date,getEventDate(iterator))==0){
            return EM_EVENT_ALREADY_EXISTS;
        }
        iterator=pqGetNext(em->events_list);
    }
    iterator=pqGetFirst(em->events_list);
    while(iterator){
        if (getEventID(iterator)==event_id)
        {
            return EM_EVENT_ID_ALREADY_EXISTS;
        }
        iterator=pqGetNext(em->events_list);
    }
    Event event=createEvent(event_name,event_id,date);
    if(!event){
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }
    PriorityQueueResult result=pqInsert(em->events_list,event,date);
    freeEvent(event);
    if(result!=PQ_OUT_OF_MEMORY){
        return EM_SUCCESS;
    }
    destroyEventManager(em);
    return EM_OUT_OF_MEMORY;
}

/*******************************************************************************************/

EventManagerResult emAddEventByDiff(EventManager em, char* event_name, int days, int event_id){
    if(!em||!event_name){
        return EM_NULL_ARGUMENT;
    }
    if(days<0){
        return EM_INVALID_DATE;
    }
    if(event_id<0){
        return EM_INVALID_EVENT_ID;
    }
    Date present_date=dateCopy(em->present);
    if(!present_date){
        return EM_OUT_OF_MEMORY;
    }
    for(int i=0;i<days;i++){
        dateTick(present_date);
    }
    EventManagerResult result=emAddEventByDate(em,event_name,present_date,event_id);
    dateDestroy(present_date);
    return result;
}

/*******************************************************************************************/

EventManagerResult emRemoveEvent(EventManager em, int event_id){
    if(!em){
        return EM_NULL_ARGUMENT;
    }
    if(event_id<0){
        return EM_INVALID_EVENT_ID;
    }
    Event the_event=getEvent(em->events_list,event_id);
    if(!the_event){
        return EM_EVENT_NOT_EXISTS;
    }
    subAllEventMembers(em,the_event);
    PriorityQueueResult result=pqRemoveElement(em->events_list,the_event);
    if(result==PQ_OUT_OF_MEMORY){
            return EM_OUT_OF_MEMORY;
    }
    return EM_SUCCESS;
}

/*******************************************************************************************/

/*    Event iterator=pqGetFirst(em->events_list);
    if (getEventID(iterator)==event_id)
    {
        subAllEventMembers(em,iterator);
        pqRemoveElement(em->events_list,iterator);
        return EM_SUCCESS;
    }
    while(iterator){
        iterator=pqGetNext(em->events_list);
        if (getEventID(iterator)==event_id)
        {
            subAllEventMembers(em,iterator);
            pqRemoveElement(em->events_list,iterator);
            return EM_SUCCESS;
        }
    }*/

/*******************************************************************************************/

EventManagerResult emChangeEventDate(EventManager em, int event_id, Date new_date){
    if(!em||!new_date){
        return EM_NULL_ARGUMENT;
    }
    if(dateCompare(new_date,em->present)<0){
        return EM_INVALID_DATE;
    }
    if(event_id<0){
        return EM_INVALID_EVENT_ID;
    }
    Event event=getEvent(em->events_list,event_id);
    if(!event){
        return EM_EVENT_ID_NOT_EXISTS;
    }
    Event iterator=pqGetFirst(em->events_list);
    while(iterator){
        if((strcmp(getEventName(iterator),getEventName(event))==0)&&
                    (dateCompare(getEventDate(iterator),new_date)==0)){
            return EM_EVENT_ALREADY_EXISTS;
        }
        iterator=pqGetNext(em->events_list);
    }
    Date copy_date=dateCopy(getEventDate(event));
    changeDate(event,new_date);
    if(pqChangePriority(em->events_list,event,copy_date,new_date)==PQ_OUT_OF_MEMORY){
        changeDate(event,copy_date);
        dateDestroy(copy_date);
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }
    dateDestroy(copy_date);
    return EM_SUCCESS;
}

/*******************************************************************************************/

EventManagerResult emAddMember(EventManager em, char* member_name, int member_id){
    if(!em||!member_name){
        return EM_NULL_ARGUMENT;
    }
    if(member_id<0){
        return EM_INVALID_MEMBER_ID;
    }
    Member iterator=pqGetFirst(em->main_members_list);
    while(iterator){
        if (getMemberID(iterator)==member_id)
        {
            return EM_MEMBER_ID_ALREADY_EXISTS;
        }
        iterator=pqGetNext(em->main_members_list);
    }
    Member member=createMember(member_name,member_id,0);
    PriorityMember priority_member=createPriorityMember(member_id,0);
    PriorityQueueResult result=pqInsert(em->main_members_list,member,priority_member);
    freeMemberPriority(priority_member);
    freeMember(member);
    if(result==PQ_OUT_OF_MEMORY){
        return EM_OUT_OF_MEMORY;
    }
    return EM_SUCCESS;
}

/*******************************************************************************************/

EventManagerResult emAddMemberToEvent(EventManager em, int member_id, int event_id){
    if (!em){
        return EM_NULL_ARGUMENT;
    }
    if(event_id<0){
        return EM_INVALID_EVENT_ID;
    }
    if(member_id<0){
        return EM_INVALID_MEMBER_ID;
    }
    Event event=getEvent(em->events_list,event_id);
    if(!event){
        return EM_EVENT_ID_NOT_EXISTS;
    }
    Member member=getMember(em->main_members_list,member_id);
    if(!member){
        return EM_MEMBER_ID_NOT_EXISTS;
    }
//    ;
    EventManagerResult result=addMemberToEvent(event,getMemberName(member),0,getMemberID(member));
    if(result==EM_SUCCESS){//////////////////
        addToInvolvedEvents(member);
        Member copy_member=copyMember(member);
        if(!copy_member){
            destroyEventManager(em);
            return EM_OUT_OF_MEMORY;
        }
 //       int event_counter=getInvolvedEvents(copy_member);//////////////////////
/*        pqRemoveElement(em->main_members_list,member);
        
        if(!new_priority){
            freeMember(copy_member);
            destroyEventManager(em);
            return EM_OUT_OF_MEMORY;
        }
        pqInsert(em->main_members_list,copy_member,new_priority);*/
        int event_counter=getInvolvedEvents(member);
        PriorityMember old_priority=createPriorityMember(member_id,event_counter);
        PriorityMember new_priority=createPriorityMember(member_id,event_counter+1);
        pqChangePriority(em->main_members_list,member,old_priority,new_priority);
        freeMemberPriority(old_priority);//////////////
        freeMember(copy_member);
        freeMemberPriority(new_priority);//////////////
    }
    return result;
}

/*******************************************************************************************/

EventManagerResult emRemoveMemberFromEvent (EventManager em, int member_id, int event_id){
    if (!em){
        return EM_NULL_ARGUMENT;
    }
    if(event_id<0){
        return EM_INVALID_EVENT_ID;
    }
    if(member_id<0){
        return EM_INVALID_MEMBER_ID;
    }
    Event event=getEvent(em->events_list,event_id);
    if(!event){
        return EM_EVENT_ID_NOT_EXISTS;
    }
    Member member=getMember(em->main_members_list,member_id);
    if(!member){
        return EM_MEMBER_ID_NOT_EXISTS;
    }
//    int event_counter=getInvolvedEvents(member);
    EventManagerResult result=removeMemberFromEvent(event,getMemberID(member));
    if(result==EM_SUCCESS){///////////////////
        subFromInvolvedEvents(member);
        Member copy_member=copyMember(member);
        if(!copy_member){
            destroyEventManager(em);
            return EM_OUT_OF_MEMORY;
        }
/*        int event_counter=getInvolvedEvents(copy_member);/////////////////////////
        pqRemoveElement(em->main_members_list,member);
        PriorityMember new_priority=createPriorityMember(member_id,event_counter);
        if(!new_priority){
            freeMember(copy_member);
            destroyEventManager(em);
            return EM_OUT_OF_MEMORY;
        }
        pqInsert(em->main_members_list,copy_member,new_priority);*/
        int event_counter=getInvolvedEvents(member);
        PriorityMember old_priority=createPriorityMember(member_id,event_counter);
        PriorityMember new_priority=createPriorityMember(member_id,event_counter-1);
        pqChangePriority(em->main_members_list,member,old_priority,new_priority);
        freeMemberPriority(old_priority);//////////////*/
        freeMember(copy_member);
        freeMemberPriority(new_priority);//////////////
    }
    return result;
}

/*******************************************************************************************/

EventManagerResult emTick(EventManager em, int days){/////////////
    if(!em){
        return EM_NULL_ARGUMENT;
    }
    if(days<=0){
        return EM_INVALID_DATE;
    }
    for(int i=0;i<days;i++){
        dateTick(em->present);
        while(dateCompare(getEventDate(pqGetFirst(em->events_list)),em->present)<0){
            emRemoveEvent(em,getEventID(pqGetFirst(em->events_list)));
        }
    }
    return EM_SUCCESS;
}

/*******************************************************************************************/

int emGetEventsAmount(EventManager em){
    if(!em){
        return ERROR;
    }
    return pqGetSize(em->events_list);
}

/*******************************************************************************************/

char* emGetNextEvent(EventManager em){
    if(!em){
        return NULL;
    }
    Event iterator=pqGetFirst(em->events_list);
/*    char* event_name=malloc(sizeof(*getEventName(iterator)));
    strcpy(event_name,getEventName(iterator));*/
    if(!iterator/*||!event_name*/){
        return NULL;
    }
    return getEventName(iterator);
}

/*******************************************************************************************/

void emPrintAllEvents(EventManager em, const char* file_name){
    if(!em){
        return;
    }
    FILE *fp=fopen(file_name,"w");
    Event iterator=pqGetFirst(em->events_list);
    while(iterator){
        printEventMembersList(iterator,fp);
        iterator=pqGetNext(em->events_list);
    }
    fclose(fp);
}

/*******************************************************************************************/

void emPrintAllResponsibleMembers(EventManager em, const char* file_name){
    Member iterator=pqGetFirst(em->main_members_list);
    FILE *fp=fopen(file_name,"w");
    while(iterator){
        if(getInvolvedEvents(iterator)>0){
            fprintf(fp,"%s,%d\n",getMemberName(iterator),getInvolvedEvents(iterator));
        }
        iterator=pqGetNext(em->main_members_list);
    }
    fclose(fp);
}

/*******************************************************************************************/


/*
EventManager createEventManager(Date date){
    EventManager em=malloc(sizeof(*em));
    if(!em||!date){
        return NULL;
    }
    em->events_list=createEventList(date);
    em->main_members_list=createMemberList();
    return em;
}

void destroyEventManager(EventManager em){
    if(!em){
        return;
    }
    destroyMemberList(em->main_members_list);
    destroyEventList(em->events_list);
    free(em);
}

EventManagerResult emAddEventByDate(EventManager em, char* event_name, Date date,
int event_id){
    if(em==NULL||event_name==NULL||date==NULL){
        return EM_NULL_ARGUMENT;
    }
    if(dateCompare(date,returnPresentDate(em->events_list))<0){
        return EM_INVALID_DATE;
    }
    if(isEventNameExistInDate(em->events_list,event_name,date)==EVENT_ALREADY_EXISTS){
        return EM_EVENT_ALREADY_EXISTS;
    }
    if(isEventIDExist(em->events_list,event_id)==EVENT_ID_ALREADY_EXISTS){
        return EM_EVENT_ID_ALREADY_EXISTS;
    }
    EventListResult result=insertEvent(em->events_list,createEvent(event_name,event_id,date));
    if(result==EL_OUT_OF_MEMORY){
        return result;
    }
    if(result==EVENT_LIST_SUCCESS){
        return EM_SUCCESS;
    }
    return EM_SUCCESS;
}

EventManagerResult emAddEventByDiff(EventManager em, char* event_name, int days,
int event_id){
    if(!em||!event_name||!event_id){
        return EM_NULL_ARGUMENT;
    }
    if(days<0){
        return EM_INVALID_DATE;
    }
    if(event_id<0){
        return EM_INVALID_EVENT_ID;
    }
    Date date=returnPresentDate(em->events_list);
    for(int i=0;i<days;i++){
        dateTick(date);
    }
    if(isEventNameExistInDate(em->events_list,event_name,date)==EVENT_ALREADY_EXISTS){
        return EM_EVENT_ALREADY_EXISTS;
    }
    if(isEventIDExist(em->events_list,event_id)==EVENT_ID_ALREADY_EXISTS){
        return EM_EVENT_ID_ALREADY_EXISTS;
    }
    EventListResult result=insertEvent(em->events_list,createEvent(event_name,event_id,date));
    if(result==EL_OUT_OF_MEMORY){
        return result;
    }
    if(result==EVENT_LIST_SUCCESS){
        return EM_SUCCESS;
    }
    return EM_SUCCESS;
}

EventManagerResult emRemoveEvent(EventManager em, int event_id){
    if(!em){
        return EM_NULL_ARGUMENT;
    }
    if(event_id<0){
        return EM_INVALID_EVENT_ID;
    }
    if(removeEventByID(em->events_list,event_id)==EVENT_LIST_SUCCESS){
        return EM_SUCCESS;
    }
    return EM_EVENT_ID_NOT_EXISTS;
}

EventManagerResult emChangeEventDate(EventManager em, int event_id, Date new_date){
    if(!em||!new_date){
        return EM_NULL_ARGUMENT;
    }
    if(dateCompare(new_date,returnPresentDate(em->events_list))<0){
        return EM_INVALID_DATE;
    }
    if(event_id<0){
        return EM_INVALID_EVENT_ID;
    }
    EventListResult result=changeEventDate(em->events_list,event_id,new_date);
    if(result==EVENT_ID_NOT_EXISTS){
        return EM_EVENT_ID_NOT_EXISTS;
    }
    if(result==EVENT_ALREADY_EXISTS){
        return EM_EVENT_ALREADY_EXISTS;
    }
    if(result==EVENT_LIST_SUCCESS){
        return EM_SUCCESS;
    }
    return EM_SUCCESS;
}

EventManagerResult emTick(EventManager em, int days){
    if(!em){
        return EM_NULL_ARGUMENT;
    }
    if(days<=0){
        return EM_INVALID_DATE;
    }
    if(eventListTick(em->events_list,days)==EVENT_LIST_SUCCESS){
        return EM_SUCCESS;
    }
    return EM_SUCCESS;
}

int emGetEventsAmount(EventManager em){
    if(!em){
        return -1;
    }
    return eventsAmount(em->events_list);
}

char* emGetNextEvent(EventManager em){
    if(!em){
        return NULL;
    }
    return getNextEvent(em->events_list);
}

EventManagerResult emAddMember(EventManager em, char* member_name, int member_id){
    if(!em||!member_name){
        return EM_NULL_ARGUMENT;
    }
    if(member_id<0){
        return EM_INVALID_MEMBER_ID;
    }
    if(isMemberAlreadyExists(em->main_members_list,member_id)){
        return EM_MEMBER_ID_ALREADY_EXISTS;
    }
    if(insertMember(em->main_members_list,member_name,member_id)==MEMBER_LIST_SUCCESS){
        return EM_SUCCESS;
    }
    return EM_SUCCESS;
}

EventManagerResult emAddMemberToEvent(EventManager em, int member_id, int
event_id){
    if(!em){
        return EM_NULL_ARGUMENT;
    }
    if(event_id<0){
        return EM_INVALID_EVENT_ID;
    }
    if(member_id<0){
        return EM_INVALID_MEMBER_ID;
    }
    if(isEventIDExist(em->events_list,event_id)==EVENT_ID_NOT_EXISTS){
        return EM_EVENT_ID_NOT_EXISTS;
    }
    if(isMemberAlreadyExists(em->main_members_list,member_id)==MEMBER_ID_NOT_EXISTS){
        return EM_MEMBER_ID_NOT_EXISTS;
    }
//    Event event=returnEventByID(em->events_list,event_id);
    EventListResult result=linkMemberToEventByID(em->events_list ,em->main_members_list  ,event_id,member_id,getMemberName(em->main_members_list,member_id));
    if(result==EVENT_AND_MEMBER_ALREADY_LINKED){
        return EM_EVENT_AND_MEMBER_ALREADY_LINKED;
    }
    if(result==EVENT_LIST_SUCCESS){
        addToCounter(em->main_members_list,member_id);
        return EM_SUCCESS;
    }
    return EM_SUCCESS;
}

EventManagerResult emRemoveMemberFromEvent (EventManager em, int member_id, int
event_id){
    if(!em){
        return EM_NULL_ARGUMENT;
    }
    if(event_id<0){
        return EM_INVALID_EVENT_ID;
    }
    if(member_id<0){
        return EM_INVALID_MEMBER_ID;
    }
    if(isEventIDExist(em->events_list,event_id)==EVENT_ID_NOT_EXISTS){
        return EM_EVENT_ID_NOT_EXISTS;
    }
    if(isMemberAlreadyExists(em->main_members_list,member_id)==MEMBER_ID_NOT_EXISTS){
        return EM_MEMBER_ID_NOT_EXISTS;
    }
//    Event event=returnEventByID(em->events_list,event_id);
    EventListResult result=removeMemberFromEventByID(em->events_list ,em->main_members_list  ,event_id,member_id);
    if(result==EVENT_AND_MEMBER_ALREADY_LINKED){
        return EM_EVENT_AND_MEMBER_ALREADY_LINKED;
    }
    if(result==EVENT_LIST_SUCCESS){
        reduceFromCounter(em->main_members_list,member_id);
        return EM_SUCCESS;
    }
    return EM_SUCCESS;
}

void emPrintAllEvents(EventManager em, const char* file_name){
    printEvents(em->events_list,file_name);
}

void emPrintAllResponsibleMembers(EventManager em, const char* file_name){
    printMainMemberList(em->main_members_list,file_name);
}


 typedef struct member{
    char* member_name;
    int member_id;
} *Member;

typedef struct event {
    char* event_name;
    int event_id;
    PriorityQueue members;
} *Event;

EventManager createEventManager(Date date){
    if(!date){
        return NULL;
    }



    EventManager em = malloc(sizeof(*em));
    em->members_list=pqCreate(copyMember,freeMember,compareMember,
                                            getNumOfEvents,removeNumOfEvents,compareNumOfEvents);
    em->events_list=pqCreate(copyEvent,emRemoveEvent,compareEvent,
                                            dateCopy,dateDestroy,dateCompare);
    return em;
}

void destroyEventManager(EventManager em){
    if(em==NULL){
        return;
    }
    pqDestroy(em->members_list);//כנראה תייוצר כאן בעיה
    eventsListDestroy(em->events_list);
    free(em);
}

static void eventsListDestroy(PriorityQueue events_list){
    while(events_list){
        
    }
}

EventManagerResult emAddEventByDate(EventManager em, char* event_name, Date date,
int event_id){
    if(em==NULL||event_name==NULL||date==NULL){
        return EM_NULL_ARGUMENT;
    }
    if(dateCompare(dateCopy(pqGetFirst(em->events_list)),date)>0){
        return EM_INVALID_DATE;
    }
    if(event_id<0){
        return EM_INVALID_EVENT_ID;
    }
    if(){
        return EM_EVENT_ALREADY_EXISTS;
    }
    if(){
        return EM_EVENT_ID_ALREADY_EXISTS;
    }
    if(){
        return EM_OUT_OF_MEMORY;
    }
    Event event=createEvent(event_id,event_name);
    if(isDateValid(em,date)){
        pqInsert(em,event,date);
    }
    return EM_SUCCESS;
}

static char* getEventName(Event event){
    return 
}

static int getNumOfEvents(int num){
    return num;
}

static int compareNumOfEvents(int num1,int num2){
    return num2-num1;
}

static void removeNumOfEvents(int num){
    return;
}

static Member copyMember(Member member){
    if(!member){
        return NULL;
    }
    return createMember(member->member_name,member->member_id);
}

static Member createMember(char* member_name,int member_id){
    if(!isMemberIDValid(member_id)||!isMemberNameValid(member_name)){
        return NULL;
    }
    Member member;
    strcpy(member->member_name,member_name);
    member->member_id=member_id;
    return member;
}

static bool isMemberIDValid(int member_id){
    if(pqContains(members_list,member_id)||member_id<0){
        return false;
    }
    return true;
}

static bool isMemberNameValid(char* member_name){

}

static void freeMember(Member member){
    free(member);
}

static bool compareMember(Member member1,Member member2){
    if(member1->member_id==member2->member_id&&!strcmp(member1->member_name,member2->member_name)){
        return true;
    }
    return false;
}

static Event copyEvent(Event event){
    if(!event){
        return NULL;
    }
    return createEvent(event->event_id,event->event_name);
}

static Event createEvent(int event_id,char* event_name){
    if(!isEventIDValid(event_id)||!isEventNameValid(event_name)){
        return NULL;
    }
    Event new_event=malloc(sizeof(*new_event));
    strcpy(new_event->event_name,event_name);
    new_event->event_id=event_id;
    return new_event;
}

static bool compareEvent(Event event1,Event event2){
    if(!strcmp(event1->event_name,event2->event_name)&&event1->event_id==event2->event_id){
        return true;
    }
    return false;
}

typedef struct day{
    Date date;
    Event events_date;
    struct day* next;
} *Day;

struct EventManager_t{
    Day first;
    Date current_date;
    PriorityQueue total_members;
};


void free_members_list(Member member){ //שכפולי קוד-לטיפול
    while(member){
        Member toDelete=member;
        member=member->next;
        free(toDelete);
    }
}

void free_events_list(Event event){
    while(event){
        Event toDelete=event;
        event=event->next;
        free(toDelete);
    }
}






EventManagerResult emAddEventByDiff(EventManager em, char* event_name, int days,
int event_id){
    if(!em||!event_name){
        return EM_NULL_ARGUMENT;
    }
    Date date=em->current_date;
    for(int i=0;i<days;i++){
        dateTick(date);
    }
    return emAddEventByDate(em,event_name,date,event_id);
}

Event findBeforeEventById(EventManager em,int event_id){
    Day iterator=em->first;
    while(iterator){
        while(iterator->events_date){
            if(iterator->events_date->event_id){
                return iterator->events_date;
            }
            iterator->events_date=iterator->events_date->next;
        }
        iterator=iterator->next;
    }
}

EventManagerResult emRemoveEvent(EventManager em, int event_id){
    Event before_event=findBeforeEventById(em,event_id);
    Event event=before_event->next;
    before_event->next=event->next;
    free_members_list(event->event_members);
    free(event);
}

EventManagerResult emChangeEventDate(EventManager em, int event_id, Date new_date){
    Event privious_event=findBeforeEventById(em,event_id);
    Event event=privious_event->next;
    EventManagerResult result=emRemoveEvent(em,event_id);
    if(result!=EM_SUCCESS){
        return result;
    }
    return emAddEventByDate(em,event->event_name,new_date,event_id);
}

EventManagerResult emAddMember(EventManager em, char* member_name, int member_id){
    pq
}

EventManagerResult emAddMemberToEvent(EventManager em, int member_id, int
event_id){

}

EventManagerResult emRemoveMemberFromEvent (EventManager em, int member_id, int
event_id){
    
}

EventManagerResult emTick(EventManager em, int days){
    for(int i=0;i<days;i++)
    {
        Day iterator=em->current_date;
        while(iterator->events_date){
            while(iterator->events_date->event_members){
                free_members_list(iterator->events_date->event_members);
            }
            free_events_list(iterator->events_date);
        }
        dateTick(em->current_date);
    }
    return EM_SUCCESS;
}

int emGetEventsAmount(EventManager em){
    
}

char* emGetNextEvent(EventManager em){

}

void emPrintAllEvents(EventManager em, const char* file_name){

}

void emPrintAllResponsibleMembers(EventManager em, const char* file_name){

}  */