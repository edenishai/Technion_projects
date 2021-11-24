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

/**
 * Defining month values
 */

static const char* const months[] = {
	"JAN", "FEB", "MAR", "APR", "MAY", "JUN",
    "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };

/**
 * Defining a date
 */

struct Date_t
{
    int day;
    char month[MONTH_STRING_LENGTH];
    int year;
};

/**
 * isDayValid: Checking if the day parameter is a valid day for date
 * 
 * @param day - The parameter we want to check
 * Returns true if valid, and false otherwise
 */

static bool isDayValid(int day)
{
    return ((day>=MINIMAL_DAY)&&(day<=MAXIMAL_DAY));
}

/**
 * isMonthValid: Checking if the month parameter is a valid month for date
 * 
 * @param month - The parameter we want to check
 * Returns true if valid, and false otherwise
 */

static bool isMonthValid(int month)
{
    return ((month>=MINIMAL_MONTH)&&(month<=MAXIMAL_MONTH));
}

/**
 * findNumOfMonth: Finds the numeric value of the number which the month argument represent
 * 
 * @param month - String with the name of the month
 * Returns an int value between 1 to 12 which represent the month
 */

static int findNumOfMonth(char* month)
{
    for(int i=0;i<MAXIMAL_MONTH;i++)
    {
        if(!strcmp(month,months[i])){
            return (i+1);
        }
    }
    return INVALID_MONTH;
}

/**
 * convertDateToDays: Converts the date to days in order to compare between dates
 * 
 * @param date - Target date
 * Returns a numeric value which represent the date in days
 */

static int convertDateToDays(Date date)
{
    int month=findNumOfMonth(date->month);
    return ((date->day)+(MAXIMAL_DAY*month)+(DAYS_IN_YEAR*(date->year)));
}

/**
 * dateIsValid: Checks if the date is valid
 * 
 * @param date - Target date
 * Return false if the date is NULL or the date is not valid, and true if the date is valid
 */

static bool dateIsValid(Date date)
{
    if(!date)
    {
        return false;
    }
    if(isDayValid(date->day)&&isMonthValid(findNumOfMonth(date->month)))
    {
        return true;
    }
    return false;
}

/**
 * dateCreate: Allocates a new date
 * 
 * @param day - The day of the date
 * @param month - The month of the date
 * @param year - The year of the date
 * Returns NULL if one of the parameters is not valid, or date in case of success
 */

Date dateCreate(int day, int month, int year)
{
    if(!isDayValid(day)||!isMonthValid(month))
    {
        return NULL;
    }
    Date new_date=malloc(sizeof(*new_date));
    if(!new_date)
    {
        return NULL;
    }
    new_date->day=day;
    strcpy(new_date->month, months[month-1]);
    new_date->year=year;
    return new_date;
}

/**
 * dateDestroy: Deallocates the date
 * 
 * @param date - The date we want to deallocate
 * If date is NULL, so nothing will be done
 */

void dateDestroy(Date date)
{
    free(date);
}

/**
* dateCopy: Creates a copy of target Date.
*
* @param date - Target Date.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A Date containing the same elements as date otherwise.
*/

Date dateCopy(Date date)
{
    if(!date)
    {
        return NULL;
    }
    return dateCreate(date->day,findNumOfMonth(date->month),date->year);
}

/**
* dateGet: Returns the day, month and year of a date
*
* @param date - Target Date
* @param day - the pointer to assign to day of the date into.
* @param month - the pointer to assign to month of the date into.
* @param year - the pointer to assign to year of the date into.
*
* @return
* 	false if one of pointers is NULL.
* 	Otherwise true and the date is assigned to the pointers.
*/

bool dateGet(Date date, int* day, int* month, int* year)
{
    if(!date||!day||!month||!year)
    {
        return false;
    }
    *day=date->day;
    *month=findNumOfMonth(date->month);
    *year=date->year;
    return true;
}

/**
* dateCompare: compares to dates and return which comes first
* 
* @param first_date - The first date we need for the comparison
* @param second_date - The second date we need for the comparison
* @return
* 		A negative integer if date1 occurs first;
* 		0 if they're equal or one of the given dates is NULL;
*		A positive integer if date1 arrives after date2.
*/

int dateCompare(Date first_date, Date second_date)
{
    if (!dateIsValid(first_date) || !dateIsValid(second_date))
    {
        return 0;
    }
    int date1=convertDateToDays(first_date);
    int date2=convertDateToDays(second_date);
    return date1-date2;
}

/**
* dateTick: increases the date by one day, if date is NULL should do nothing.
*
* @param date - Target Date
*
*/

void dateTick(Date date){
    if(!date)
    {
        return;
    }
    if(isDayValid((date->day)+1))
    {
        (date->day)++;
        return;
    }
    if(isMonthValid((findNumOfMonth(date->month))+1))
    {
        date->day=MINIMAL_DAY;
        int next_month=findNumOfMonth((date->month))+1;
        strcpy(date->month, months[next_month-1]);
        return;
    }
    if (findNumOfMonth(date->month) == MAXIMAL_MONTH)
    {
        date->day=MINIMAL_DAY;
        strcpy(date->month, months[0]);
        ++(date->year);
    }
    return;
}

/*******************************************************************************************/