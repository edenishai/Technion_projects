#include "date.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MONTH_STRING_LENGTH 4
#define MINIMAL_DAY 1
#define MAXIMAL_DAY 30
#define MINIMAL_MONTH 1
#define MAXIMAL_MONTH 12
#define INVALID_MONTH 0
#define SUCCESS 1
#define DAYS_IN_YEAR 365
#define ERROR -1

/*******************************************************************************************/

static const char* const months[] = {
	"JAN", "FEB", "MAR", "APR", "MAY", "JUN",
    "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };

struct Date_t{
    int day;
    char month[MONTH_STRING_LENGTH];
    int year;
};

/*******************************************************************************************/

static bool isDayValid(int day){
    return ((day>=MINIMAL_DAY)&&(day<=MAXIMAL_DAY));
}

/*******************************************************************************************/

static bool isMonthValid(int month){
    return ((month>=MINIMAL_MONTH)&&(month<=MAXIMAL_MONTH));
}

/*******************************************************************************************/

Date dateCreate(int day, int month, int year)
{
    if(!isDayValid(day)||!isMonthValid(month)){
        return NULL;
    }
    Date new_date=malloc(sizeof(*new_date));
    if(!new_date){
        return NULL;
    }
    new_date->day=day;
    strcpy(new_date->month, months[month-1]);
    new_date->year=year;
    return new_date;
}

/*******************************************************************************************/

void dateDestroy(PQElementPriority date){
    free((Date)date);
}

/*******************************************************************************************/

int getDay(Date date){
    if (!date) {
        return ERROR;
    }
    return date->day;
}

/*******************************************************************************************/

static int findNumOfMonth(char* month){
    for(int i=0;i<MAXIMAL_MONTH;i++)
    {
        if(!strcmp(month,months[i])){
            return (i+1);
        }
    }
    return INVALID_MONTH;
}

/*******************************************************************************************/

int getMonthNum(Date date){
    if (!date) {
        return ERROR;
    }
    return findNumOfMonth(date->month);
}

/*******************************************************************************************/

int getYear(Date date){
    if (!date) {
        return ERROR;
    }
    return date->year;
}

/*******************************************************************************************/

PQElementPriority dateCopy(PQElementPriority date){
    if(!date){
        return NULL;
    }
    return dateCreate(((Date)date)->day,findNumOfMonth(((Date)date)->month),((Date)date)->year);
}

/*******************************************************************************************/

bool dateGet(Date date, int* day, int* month, int* year){
    if(!date||!day||!month||!year){
        return false;
    }
    *day=date->day;
    *month=findNumOfMonth(date->month);
    *year=date->year;
    return true;
}

/*******************************************************************************************/

static int dateToDays(Date date){
    int month=findNumOfMonth(date->month);
    return ((date->day)+(MAXIMAL_DAY*month)+(DAYS_IN_YEAR*(date->year)));
}

/*******************************************************************************************/

static bool dateIsValid(Date date){
    if(!date){
        return false;
    }
    if(isDayValid(date->day)&&isMonthValid(findNumOfMonth(date->month))){
        return true;
    }
    return false;
}

/*******************************************************************************************/
//negative-the first with greater priority
int dateCompare(PQElementPriority first_date, PQElementPriority second_date){
    if (!dateIsValid((Date)first_date) || !dateIsValid((Date)second_date)) {
        return 0;
    }
    int date1=dateToDays((Date)first_date);
    int date2=dateToDays((Date)second_date);
    return date1-date2;
}

/*******************************************************************************************/

void dateTick(Date date){
    if(!date){
        return;
    }
    if(isDayValid((date->day)+1))
    {
        (date->day)++;
        return;
    }
    if(isMonthValid((findNumOfMonth(date->month))+1)){
        date->day=MINIMAL_DAY;
        int next_month=findNumOfMonth((date->month))+1;
        strcpy(date->month, months[next_month-1]);
        return;
    }
    if (findNumOfMonth(date->month) == MAXIMAL_MONTH) {
        date->day=MINIMAL_DAY;
        strcpy(date->month, months[0]);
        ++(date->year);
    }
    return;
}

/*******************************************************************************************/

void printDate(Date date,FILE* outputFile){
    if(!date){
        return;
    }
    fprintf(outputFile,"%d.%d.%d",(date->day),(findNumOfMonth(date->month)),(date->year));
}

/*******************************************************************************************/