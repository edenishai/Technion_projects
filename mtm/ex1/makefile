CC = gcc
OBJS = date.o event.o event_manager.o member.o
PQOBJS = priority_queue.o
EXEC1 = event_manager
EXEC2 = priority_queue
DEBUG_FLAG = # now empty, assign -g for debug
COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG

event_manager : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) tests/event_manager_example_tests.c $(OBJS) -L. -lpriority_queue -o $@

priority_queue: $(PQOBJS)
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) tests/pq_example_tests.c $(PQOBJS) -o $@

event_manager.o: event_manager.c date.h priority_queue.h event_manager.h event.h member.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
priority_queue.o: priority_queue.c priority_queue.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
date.o: date.c date.h priority_queue.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
event.o: event.c date.h priority_queue.h member.h event_manager.h event.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
member.o: member.c date.h priority_queue.h member.h event_manager.h event.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

clean:
	rm -f $(OBJS) $(PQOBJS) $(EXEC1) $(EXEC2)