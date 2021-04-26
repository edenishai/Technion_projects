#ifndef SCHEDULE_H_
#define SCHEDULE_H_


#include <iostream>
#include <vector>
#include <string>
#include "../partB/event_container.h"
#include "../partB/linked_list.h"
#include "../partA/exceptions.h"
#include "../partB/ptr_vector.h"

namespace mtm
{
    
    using std::cout;
    using std::string;
    using std::endl;
    using std::vector;

    class Schedule
    {
        vector<BaseEvent*> events_list;
        PtrVector pointers_vector;
    
    public:
    
        Schedule():pointers_vector(){}

        /**
         * Removes the pointers to events that the clone functions allocated
         */
        ~Schedule(){
            for(int i=0;i<pointers_vector.counter;i++)
            {
                delete pointers_vector.events[i];
            }
        }
        void addEvents(const EventContainer& container);

        /**
         * An helping function for checking if one of the events of the container exists in the schedule
         */
        bool checkIfExist(const EventContainer& container);
        void registerToEvent(const DateWrap& date,string name, int student_id);
        void unregisterFromEvent(const DateWrap& date,string name, int student_id);
        void printAllEvents() const;
        void printMonthEvents(int month,int year) const;
        void printEventDetails(const DateWrap& date,string name) const;

        /**
         * Sorts the vector of the events according to which event comes first
         * Using bubble sort
         */
        void sortVector();

        /**
         * Swaps two arguments of the vector.
         * An helping function for the sort function
         */
        void swapVector(int index1,int index2);

        template <typename Predicate>
        void printSomeEvents(Predicate pred,bool verbose) const{
            for(int i=0;i<events_list.size();i++) {
                if(pred(*events_list[i])){
                    if(verbose){
                        (*events_list[i]).printLong(cout) << endl;
                    }else{
                        (*events_list[i]).printShort(cout) << endl;
                    }
                }
            }
        }
    };
}
#endif

