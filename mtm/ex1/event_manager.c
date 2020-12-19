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
    int day,month,year;
    dateGet(date,&day,&month,&year);
    em->events_list=pqCreate(copyEvent,freeEvent,compareEvents,dateCopy,dateDestroy,negativeDateCompare);
    em->main_members_list=pqCreate(copyMember,freeMember,compareMember,copyMemberPriority,freeMemberPriority,compareMemberPriority);
    em->present=dateCreate(day,month,year);
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
    EventManagerResult result=addMemberToEvent(event,getMemberName(member),0,getMemberID(member));
    if(result==EM_SUCCESS){
        Member copy_member=copyMember(member);
        if(!copy_member){
            destroyEventManager(em);
            return EM_OUT_OF_MEMORY;
        }
        addToInvolvedEvents(copy_member);
        int event_counter=getInvolvedEvents(copy_member);
        pqRemoveElement(em->main_members_list,member);
        PriorityMember new_priority=createPriorityMember(member_id,event_counter);
        if(!new_priority){
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
    EventManagerResult result=removeMemberFromEvent(event,getMemberID(member));
    if(result==EM_SUCCESS){
        Member copy_member=copyMember(member);
        if(!copy_member){
            destroyEventManager(em);
            return EM_OUT_OF_MEMORY;
        }
        subFromInvolvedEvents(copy_member);
        int event_counter=getInvolvedEvents(copy_member);
        pqRemoveElement(em->main_members_list,member);
        PriorityMember new_priority=createPriorityMember(member_id,event_counter);
        if(!new_priority){
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

/*******************************************************************************************/

void subAllEventMembers(EventManager em,Event event){
    if(!em||!event){
        return;
    }
    Member iterator=((Member)getFirstPQStaff(event));
    while(iterator){
        int member_id=getMemberID(iterator);
        emRemoveMemberFromEvent(em,member_id,getEventID(event));
        iterator=((Member)getFirstPQStaff(event));
    }
}

/*******************************************************************************************/

EventManagerResult emTick(EventManager em, int days){
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
    if(!iterator){
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