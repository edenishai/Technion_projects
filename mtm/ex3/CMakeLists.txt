cmake_minimum_required(VERSION 3.0.0)
project(Ex3 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Ex3 partA/date_wrap.cpp partA/date_wrap.h partA/date.h partA/date.c
                partA/exceptions.cpp partA/exceptions.h
                partB/base_event.cpp partB/base_event.h
                partB/closed_event.cpp partB/closed_event.h
                partB/open_event.cpp partB/open_event.h
                partB/event_container.cpp partB/event_container.h
                partB/linked_list.h partB/node.h partB/iterator.h
                partB/custom_event.h partB/recurring_event.h
                partB/festival.cpp partB/festival.h
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
