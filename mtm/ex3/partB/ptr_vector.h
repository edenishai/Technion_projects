#ifndef PTR_VECTOR_H
#define PTR_VECTOR_H

#include "base_event.h"

namespace mtm
{
    
    const int START=1;

    /**
     * A vector which stores all the events we allocate and frees them in the end
     */
    class PtrVector
    {

        BaseEvent** events;
        int length;
        int counter;

    public:

        PtrVector(int length=START): length(length),counter(0)
        {
            events=new BaseEvent*[length];
        }

        ~PtrVector()
        {
            delete[] events;
        }

        /**
         * Adds a new pointer to the vector, so we can delete it in the end
         */
        void add(BaseEvent* new_event)
        {
            if(counter==length)
            {
                BaseEvent** new_events_array=new BaseEvent*[++length];
                for(int i=0;i<counter;i++)
                {
                    new_events_array[i]=events[i];
                }
                delete[] events;
                events=new_events_array;
            }
            events[counter++]=new_event;
        }

        /**
         * The classes that use in the vector for deleting the pointers of the events
         */
        friend class EventContainer;
        friend class Schedule;

    };

}

#endif