#include "schedule.h"

using std::cout;
using std::string;
using std::vector;
using std::endl;

namespace mtm{

    bool Schedule::checkIfExist(const EventContainer& container){
        int list_size=events_list.size();
        for(int i=0;i<list_size;i++){
            EventContainer::EventIterator iteratorContainer(container.begin());
            while(iteratorContainer!=nullptr){
                if(*events_list[i]==*iteratorContainer){
                    throw EventAlreadyExists();
                }
                ++iteratorContainer;
            }
        }
        return false;
    }
    void Schedule::addEvents(const EventContainer& container){
        checkIfExist(container);
        EventContainer::EventIterator iteratorContainer(container.begin());
        while(iteratorContainer!=NULL){
            BaseEvent* event=(*iteratorContainer).clone();
            pointers_vector.add(event);
            events_list.push_back(event);
            ++iteratorContainer;
        }
        sortVector();
    }

    void Schedule::sortVector(){
        vector<BaseEvent*>::iterator iter=events_list.begin();
        int list_size=events_list.size();
        for(int i=list_size-1;i>0;i--){
            for(int j=0;j<i;j++){
                if(*(events_list[j])>*(events_list[j+1])){
                    swapVector(j,j+1);
                }            
            }
        }
    }

    void Schedule::swapVector(int index1,int index2){
        BaseEvent* temp=events_list[index1];
        events_list[index1]=events_list[index2];
        events_list[index2]=temp;
    }
    
    void Schedule::registerToEvent(const DateWrap& date,string name, int student_id){
        int list_size=events_list.size();
        for(int i=0;i<list_size;i++){
            if((*events_list[i]).getDate()==date&&(*events_list[i]).getName()==name){
                (*events_list[i]).registerParticipant(student_id);
                return;
            }
        }
        throw EventDoesNotExist();
    }

    void Schedule::unregisterFromEvent(const DateWrap& date,string name, int student_id){
        int list_size=events_list.size();
        for(int i=0;i<list_size;i++) {
            if((*events_list[i]).getDate()==date&&(*events_list[i]).getName()==name){
                (*events_list[i]).unregisterParticipant(student_id);
                return;
            }
            
        }
        throw EventDoesNotExist();
    }
    void Schedule::printAllEvents() const{
        int list_size=events_list.size();
        for(int i=0;i<list_size;i++) {
            (*events_list[i]).printShort(cout)<<endl;
            
        }
    }
    void Schedule::printMonthEvents(int month,int year) const{
        int list_size=events_list.size();
        for(int i=0;i<list_size;i++) {
            if((*events_list[i]).getDate().month()==month&&(*events_list[i]).getDate().year()==year){
                (*events_list[i]).printShort(cout)<< endl;
            }
            
        }
    }

    void Schedule::printEventDetails(const DateWrap& date,string name) const{
        int list_size=events_list.size();
        for(int i=0;i<list_size;i++) {
            if((*events_list[i]).getDate()==date){
                (*events_list[i]).printLong(cout)<<endl;
                return;
            }
            
        }
        throw EventDoesNotExist();
    }
}