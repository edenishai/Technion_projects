#ifndef MEMBER_H
#define MEMBER_H

#include "event_manager.h"
#include "event.h"


typedef struct Member_t* Member;

typedef struct Priority_Member_t* PriorityMember;


Member createMember(char* member_name,int member_id,int event_counter);

PQElement copyMember(PQElement member);

void freeMember(PQElement member);

bool compareMember(PQElement member1,PQElement member2);

char* getMemberName(Member member);

int getMemberID(Member member);

PQElementPriority getMemberIDPointer(Member member);

PQElementPriority copyMemberID(PQElementPriority member_id);

void freeMemberID(PQElementPriority member_id);

int compareMemberID(PQElementPriority first_member_id, PQElementPriority second_member_id);

Member getMember(PriorityQueue queue,int member_id);

int getInvolvedEvents(Member member);

void addToInvolvedEvents(Member member);

void subFromInvolvedEvents(Member member);

void printMemberName(Member member,FILE* outputFile);

PriorityMember createPriorityMember(int member_id,int event_counter);

PQElementPriority copyMemberPriority(PQElementPriority member_priority);

void freeMemberPriority(PQElementPriority member_priority);

int compareMemberPriority(PQElementPriority first_member_priority, PQElementPriority second_member_priority);



/*
typedef struct Member_List_t* MemberList;

typedef enum MemberListResult_t {
    ML_NULL_ARGUMENT,
    MEMBER_LIST_SUCCESS,
    ML_OUT_OF_MEMORY,
    MEMBER_ID_ALREADY_EXISTS,
    MEMBER_ID_NOT_EXISTS
} MemberListResult;

MemberList createMemberList();

MemberListResult insertMember(MemberList member_list, char* member_name, int member_id);

MemberListResult removeMember(MemberList member_list, int member_id);

MemberListResult isMemberAlreadyExists(MemberList member_list,int member_id);

void destroyMemberList(MemberList member_list);

char* getMemberName(MemberList member_list,int member_id);

void addToCounter(MemberList member_list,int member_id);

void reduceFromCounter(MemberList member_list,int member_id);

//EventListResult linkMemberToEventByID(EventList event_list,MemberList member_list,int event_id,int member_id);

void printMemberList(MemberList member_list,const char* file_name);

void printMainMemberList(MemberList member_list,const char* file_name);
*/
#endif