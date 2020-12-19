#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "date.h"
#include "priority_queue.h"
#include "member.h"
#include "event_manager.h"

#define ERROR -1

/*******************************************************************************************/

struct Member_t{
    char* member_name;
    int member_id;
    int event_counter;
};

struct Priority_Member_t{
    int member_id;
    int event_counter;
};

/*******************************************************************************************/

Member createMember(char* member_name,int member_id,int event_counter){
    if(!member_name){
        return NULL;
    }
    Member member=malloc(sizeof(*member));
    if(!member){
        return NULL;
    }
    member->member_name=malloc(strlen(member_name)+1);
    if(!member_name){
        freeMember(member);
        return NULL;
    }
    strcpy(member->member_name,member_name);
    member->member_id=member_id;
    member->event_counter=event_counter;
    return member;
}

/*******************************************************************************************/

PQElement copyMember(PQElement member){
    if (member == NULL) {
        return NULL;
    }
    Member new_member = malloc(sizeof(*new_member));
    if (new_member == NULL) {
        return NULL;
    }
    new_member->member_name=malloc(sizeof(char)*(strlen(((Member)member)->member_name)+1));
    if(!(new_member->member_name)){
        freeMember(new_member);
        return NULL;
    }
    strcpy(new_member->member_name, ((Member)member)->member_name);
    new_member->member_id = ((Member)member)->member_id;
    new_member->event_counter=((Member)member)->event_counter;
    return new_member;
}

/*******************************************************************************************/

void freeMember(PQElement member){
    if(!member){
        return;
    }
    free(((Member)member)->member_name);
    free(member);
}

/*******************************************************************************************/

bool compareMember(PQElement member1,PQElement member2){
    if(!member1||!member2){
        return false;
    }
    if(((Member)member1)->member_id==((Member)member2)->member_id){
        return true;
    }
    return false;
}

/*******************************************************************************************/

char* getMemberName(Member member){
    if (!member)
    {
        return NULL;
    }
    return member->member_name;
}

/*******************************************************************************************/

int getMemberID(Member member){
    if(!member){
        return ERROR;
    }
    return member->member_id;
}

/*******************************************************************************************/

PQElementPriority copyMemberID(PQElementPriority member_id){
    int *new_member_id=malloc(sizeof(*new_member_id));
    *new_member_id=*(int*)member_id;
    return new_member_id;
}

/*******************************************************************************************/

void freeMemberID(PQElementPriority member_id){
    free(member_id);
}

/*******************************************************************************************/

int compareMemberID(PQElementPriority first_member_id, PQElementPriority second_member_id){
    return (*(int*)second_member_id - *(int*)first_member_id);
}

/*******************************************************************************************/

Member getMember(PriorityQueue queue,int member_id){
    if(!queue){
        return NULL;
    }
    Member iterator=pqGetFirst(queue);
    if(!iterator){
        return NULL;
    }
    while(iterator){
        if (getMemberID(iterator)==member_id)
        {
            return iterator;
        }
        iterator=pqGetNext(queue);
    }
    return NULL;
}

/*******************************************************************************************/

int getInvolvedEvents(Member member){
    if(!member){
        return ERROR;
    }
    return member->event_counter;
}

/*******************************************************************************************/

void addToInvolvedEvents(Member member){
    if(!member){
        return;
    }
    ++(member->event_counter);
}

/*******************************************************************************************/

void subFromInvolvedEvents(Member member){
    if(!member){
        return;
    }
    --(member->event_counter);
}

/*******************************************************************************************/

void printMemberName(Member member,FILE* outputFile){
    if(!member){
        return;
    }
    fprintf(outputFile,",%s",member->member_name);
}

/*******************************************************************************************/

PriorityMember createPriorityMember(int member_id,int event_counter){
    PriorityMember priority_member=malloc(sizeof(*priority_member));
    if(!priority_member){
        return NULL;
    }
    priority_member->member_id=member_id;
    priority_member->event_counter=event_counter;
    return priority_member;
}

/*******************************************************************************************/

PQElementPriority copyMemberPriority(PQElementPriority member_priority) 
{
    if (member_priority == NULL) {
        return NULL;
    }
    PriorityMember new_member_priority = malloc(sizeof(*new_member_priority));
    if (new_member_priority == NULL) {
        return NULL;
    }
    new_member_priority->event_counter = ((PriorityMember)member_priority)->event_counter;
    new_member_priority->member_id=((PriorityMember)member_priority)->member_id;

    return (PriorityMember)new_member_priority;
}

/*******************************************************************************************/

void freeMemberPriority(PQElementPriority member_priority)  
{
    if(!member_priority){
        return;
    }
    free((PriorityMember)member_priority);
}

/*******************************************************************************************/

int compareMemberPriority(PQElementPriority first_member_priority, PQElementPriority second_member_priority) 
{
    if(!first_member_priority||!second_member_priority){
        return 0;
    }
    if ((((PriorityMember)first_member_priority)->event_counter) != (((PriorityMember)second_member_priority)->event_counter)) {
        return (((PriorityMember)first_member_priority)->event_counter) - (((PriorityMember)second_member_priority)->event_counter);
    }
    return (((PriorityMember)second_member_priority)->member_id)-(((PriorityMember)first_member_priority)->member_id);
}

/**************************************/