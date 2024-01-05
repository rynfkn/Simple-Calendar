#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include "ColorText.h"

#define CLEAR printf("\x1b[2J\x1b[H");

int calculateday(int day, int month, int year){
    //formula
    //F = day + [ (13 * month -  1) / 5] + D + [D/4] + [C/4] - 2*C
    month -= 2;

    if(month < 1){
        month = 12 + month;
        year--;
    }

    int k  = day;
    int m = month;
    int d = year % 100;
    int c = floor(year/100);

    // printf("%d %d %d %d\n", k, m, d, c);

    int f = k + ((13*m) - 1)/5 + d + (d/4) + (c/4) - 2*c;

    if(f < 0){
        int cek = -7;
        while(cek>=f){
            cek -= 7;
        }
        f = f - cek;
    }

    return f % 7;
}

void displaydate(int day, int month, int year){
    //motnh conversion
    char MonthName[12][10] = {"JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", 
    "JULY", "AUGUST", "SEPTEMBER","OCTOBER","NOVEMBER","DECEMBER"};

    printf("%s, %d\n\n", MonthName[month - 1], year);

    int cek = ((year % 4 == 0) ? 1 : 0);

    int index = calculateday(1, month, year);

    int daysinmonth;
    if(month == 2){
        daysinmonth = cek ? 29 : 28;
    }
    else if((month <= 7 && month % 2== 1) || (month >= 8 && month % 2 == 0)){
        daysinmonth = 31;
    }
    else{
        daysinmonth = 30;
    }
    
    int date = 1;
    printf("\x1b[031mSUN\x1b[0m  MON  TUE  WED  THU  FRI  SAT\n\n");

    for(int i = 1 ; i <= 6 ; i++){
        for(int j = 0 ; j < 7 ; j++){
            if(i == 1 && j < index){
                printf("     ");
            }
            else if(date <= daysinmonth){
                if(date == day){
                    if(date > 9){
                        //if monday --> printf red color
                        if(j == 0){
                            setcolors(fgRED, bgBLACK, caNORMAL);
                            printf("[%2d] ", date);
                            resetcolors();
                        }
                        else{
                            printf("[%2d] ", date);
                        }
                    }
                    else{
                        if(j == 0){
                            setcolors(fgRED, bgBLACK, caNORMAL);
                            printf(" [%d] ", date);
                            resetcolors();    
                        }
                        else{
                            printf(" [%d] ", date);
                        }
                    }
                }
                else{
                    if(date > 9){
                        if(j == 0){
                            setcolors(fgRED, bgBLACK, caNORMAL);
                            printf(" %2d  ", date);
                            resetcolors();
                        }
                        else{
                            printf(" %2d  ", date);
                        }
                    }
                    else{
                        if(j == 0){
                            setcolors(fgRED, bgBLACK, caNORMAL);
                            printf("  %d  ", date);
                            resetcolors();
                        }
                        else{
                            printf("  %d  ", date);
                        }
                    }
                }
                date++;
            }
        }
        printf("\n");
    }
}

int main(){
    int day, month, year;
    printf("ENTER THE DATE : ");
    scanf("%d %d %d", &day, &month, &year);

    //checker for input
    if((day >= 1 && day <= 31) && (month >= 1 && month <= 12) && year >= 1){
        if(month == 2){
            if(year % 4 != 0 && day >= 29){
                printf("INVALID INPUT\n");
                return 0;
            }
            else if(year % 4 == 0 && day > 29){
                printf("INVALID INPUT\n");
                return 0;
            }
        }
    }
    else{
        printf("INVALID INPUT\n");
        return 0;
    }

    displaydate(day, month, year);


    int arrow;
    while(1){
        arrow = _getch();

        switch (arrow)
        {
        case 72:
            day -= 7;
            if(month <= 7 && month % 2 == 1 && day < 1){
                if(month == 1){
                    day = (31 + day);
                }
                else if(month == 3){
                    if(year % 4 == 0){
                        day = (29 + day);
                    }
                    else{
                        day = (28 + day);
                    }
                }
                else{
                    day = (30 + day);
                }

                month--;
                if(month < 1){
                    month = 12;
                    year--;
                }
            }
            else if(month <= 7 && month % 2 == 0 && day < 1){
                day = (31 + day);

                month--;
            }
            else if(month >= 8 && month % 2 == 0 && day < 1){
                if(month == 8){
                    day = (31 + day);
                }
                else{
                    day = (30 + day);
                }

                month--;
            }
            else if(month >= 8 && month % 2 == 1 && day < 1){
                day = (31 + day);

                month--;
            }

            CLEAR;
            displaydate(day, month, year);
            break;
        case 80:
            day += 7;
            if(month <= 7 && month % 2 == 1 && day > 31){
                day -= 31;
                month++;
            }
            else if(month <= 7 && month % 2 == 0 && day >30){
                if(month == 2){
                    if(year % 4 == 0){
                        day -= 29;
                    }
                    else{
                        day -= 28;
                    }
                }
                else{
                    day -= 30;
                }

                month++;
            }
            else if(month >= 8 && month % 2== 0 && day > 31){
                day -= 31;
                month++;

                if(month > 12){
                    month = 1;
                    year++;
                }
            }
            else if(month >= 8 && month % 2 == 1 && day > 30){
                day -= 30;
                month++;
            }

            CLEAR;
            displaydate(day, month, year);
            break;
        case 75:
            day--;
            if(month <= 7 && month % 2 == 1 && day < 1){
                if(month == 1){
                    day = 31;
                }
                else if(month == 3 && year % 4 == 0){
                    day = 29;
                }
                else if(month == 3 && year % 4 == 1){
                    day = 28;
                }

                month--;
                if(month < 1){
                    month = 12;
                    year--;
                }
            }
            else if(month <= 7 && month % 2 == 0 && day < 1){
                day = 31;
                month--;
            }
            else if(month >= 8 && day < 1){
                if(month == 8 || month % 2 == 1){
                    day = 31;
                }
                else if(month % 2 == 0){
                    day = 30;
                }
                month--;
            }

            CLEAR;
            displaydate(day, month, year);
            break;
        case 77:
            day++;
            if(month <= 7 && month % 2 == 1 && day > 31){
                day = 1;
                month++;
                if(month > 12){
                    month = 1;
                    year++;
                }
            }
            else if(month <= 7 && month % 2 == 0){
                if(month == 2 && year % 4 == 0){
                    if(day > 29){
                        day = 1;
                        month++;
                    }
                }
                else if(month == 2 && year % 4 ==1){
                    if(day > 28){
                        day = 1;
                        month++;
                    }
                }
                else{
                    if(day > 30){
                        day = 1;
                        month++;
                    }
                }
            }
            else if(month >= 8 && month % 2 == 1 && day > 30){
                day = 1;
                month++;
            }
            else if(month >= 8 && month % 2 == 0 && day > 31){
                day = 1;
                month++;
                if(month > 12){
                    month = 1;
                    year++;
                }
            }
            CLEAR;
            displaydate(day, month, year);
            break;
        case 27:
            printf("DONE\n");
            CLEAR;
            return 0;
            break;
        }
    }
    return 0;
}