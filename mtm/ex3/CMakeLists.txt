cmake_minimum_required(VERSION 3.17)
project(Ex3)

set(CMAKE_CXX_STANDARD 11)

add_library(date partA/date.c partA/date.h partA/exceptions.h)

add_executable(Ex3_part2 partA/date_wrap.cpp partA/date_wrap.h partA/date.h partA/date.c
                partA/exceptions.cpp partA/exceptions.h
                partB/base_event.cpp partB/base_event.h
                partB/closed_event.cpp partB/closed_event.h
                partB/open_event.cpp partB/open_event.h
                partB/event_container.cpp partB/event_container.h
                partB/linked_list.h partB/node.h
                partB/custom_event.h partB/recurring_event.h
                partB/festival.cpp partB/festival.h
                provided/test_partB.cpp
)

target_link_libraries(Ex3_part2 date)

