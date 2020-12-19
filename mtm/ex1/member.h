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


#endif