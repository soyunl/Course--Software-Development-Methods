/** @file event_manager.c
 *  @brief A pipes & filters program that uses conditionals, loops, and string processing tools in C to process iCalendar
 *  events and printing them in a user-friendly format.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Juan G.
 *  @author Soyun Lee
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief The maximum line length.
 *
 */
#define MAX_LINE_LEN 132

/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */

struct calLine {
    char * property;
    char * info;
};

char * filter_command(char *argv[]) {
    // char * start = strtok(argv[1],"-=start");
    // char * end = strtok(argv[2],"-=end");
    char param3[MAX_LINE_LEN];
    strcpy(param3,argv[3]);
    const char ch = '=';
    char *filtered_file;
    filtered_file = strchr(param3,ch);
    char * filename = strtok(filtered_file,"=");
    return strdup(filename);
}

struct calLine store_struct(char *line) {
    char s[2] = ":";
    char linecpy[MAX_LINE_LEN];
    const char ch = ':';
    struct calLine vcal;
    char *temp_info;

    strcpy(linecpy,line);
    vcal.property = strtok(linecpy,s);
    temp_info = strchr(linecpy,ch);
    vcal.info = strtok(temp_info,":");
    return vcal;

}

void change_month(char *dtstart) {
    char new_month[3];
    int c = 0; //index for new_month
    int i = 4; //index for 4th and 5th character of dtstart

    while (c<2) {
        new_month[c] = dtstart[i];
        c++;
        i++;
    }
    memcpy(dtstart,new_month,sizeof(new_month));
}

void month_conversion(char *month) {
    char month_eng[14];
    if (strcmp(month,"01")==0) {
        strcpy(month_eng,"January");
    }
    else if (strcmp(month,"02")==0) {
        strcpy(month_eng,"February");
    }
    else if (strcmp(month,"03")==0) {
        strcpy(month_eng,"March");
    }
    else if (strcmp(month,"04")==0) {
        strcpy(month_eng,"April");
    }
    else if (strcmp(month,"05")==0) {
        strcpy(month_eng,"May");
    }
    else if (strcmp(month,"06")==0) {
        strcpy(month_eng,"June");
    }
    else if (strcmp(month,"07")==0) {
        strcpy(month_eng,"July");
    }
    else if (strcmp(month,"08")==0) {
        strcpy(month_eng,"August");
    }
    else if (strcmp(month,"09")==0) {
        strcpy(month_eng,"September");
    }
    else if (strcmp(month,"10")==0) {
        strcpy(month_eng,"October");
    }
    else if (strcmp(month,"11")==0) {
        strcpy(month_eng,"November");
    }
    else if (strcmp(month,"12")==0) {
        strcpy(month_eng,"December");
    }
    memcpy(month,month_eng,sizeof(month_eng));
}

void day_conversion(char *day) {
    char day_filtered[3];
    int c = 0;
    int i = 6;

    while (c<2) {
        day_filtered[c] = day[i];
        c++;
        i++;
    }
    memcpy(day,day_filtered,sizeof(day_filtered));
}

void year_conversion(char *year) {
    char year_filtered[5];
    int c=0;
    int i=0;

    while (c<4) {
        year_filtered[c] = year[i];
        c++;
        i++;
    }
    memcpy(year,year_filtered,sizeof(year_filtered));
}

void change_time(char *time) {
    char timecpy[MAX_LINE_LEN];
    strcpy(timecpy,time);
    char new_hour[3];
    int c = 0;
    int i = 9; 

    while (c<2) {
        new_hour[c] = timecpy[i];
        c++;
        i++;
    }
    char new_min[3];
    c = 0;
    i = 11;
    while (c<2) {
        new_min[c] = timecpy[i];
        c++;
        i++;
    }
    int hour;
    hour = atoi(new_hour);
    if (hour<12) {
        if (hour<10) {
            printf(" %d:%s AM",hour,new_min);
        } else {
            printf("%s:%s AM",new_hour,new_min);
        }
    } else if (hour==12) {
        printf("%s:%s PM",new_hour,new_min);
    } else {
        hour = hour-12;
        if (hour<10) {
            printf(" %d:%s PM",hour,new_min);
        } else {
            printf("%d:%s PM",hour,new_min);
        }
        
    }

}
void modify_line2(int dash) {
    for (int i=0; i<dash; i++){
        printf("-");
    }
}

void modify_line1(char *dtstartcpy) {
    char line1[MAX_LINE_LEN];

    char month[MAX_LINE_LEN];
    strcpy(month,dtstartcpy);

    char day[MAX_LINE_LEN];
    strcpy(day,dtstartcpy);

    char year[MAX_LINE_LEN];
    strcpy(year,dtstartcpy);

    char sttime[MAX_LINE_LEN];
    strcpy(sttime,dtstartcpy);

    change_month(month);
    month_conversion(month);
    day_conversion(day);
    year_conversion(year);

    sprintf(line1, "%s %s, %s\n",month,day,year);
    printf("%s",line1);

    int dash;
    dash = strlen(month)+strlen(day)+strlen(year)+3;
    modify_line2(dash);

    printf("\n");
    change_time(sttime);
    printf(" to ");

}

void modify_end(char *dtendcpy) {
    char endtime[MAX_LINE_LEN];
    strcpy(endtime,dtendcpy);
    change_time(endtime);
}


int main(int argc, char *argv[]) {
    // TODO: your code.
    char *filename = filter_command(argv);
    char line[MAX_LINE_LEN];

    FILE *fp = fopen(filename,"r");
    struct calLine cal;
    struct calLine calarr[MAX_LINE_LEN];
    char loc_info[MAX_LINE_LEN];
    char sum_info[MAX_LINE_LEN];
    const char n[2] = "\n";
    char line3[MAX_LINE_LEN];
    char loc_temp[MAX_LINE_LEN];
    char *newsum;
    char *newloc;

    int i = 0;
    int count = 0;

    if (fp==NULL) {
        return -1;
    }

    while (fgets(line,MAX_LINE_LEN,fp)!=NULL) {
        cal = store_struct(line);
        calarr[i].property = cal.property;
        calarr[i].info = cal.info;

        if ((strcmp(calarr[i].property,"BEGIN")==0) && i>2)  {
            count++;
            printf("\n\n");
            
        }
        if (strcmp(calarr[i].property,"DTSTART")==0) {
            char dtstartcpy[MAX_LINE_LEN];
            strcpy(dtstartcpy, calarr[i].info);
            modify_line1(dtstartcpy);
            

        } if (strcmp(calarr[i].property,"DTEND")==0) {
            char dtendcpy[MAX_LINE_LEN];
            strcpy(dtendcpy, calarr[i].info);
            modify_end(dtendcpy);
            
        } if (strcmp(calarr[i].property,"LOCATION")==0) {
            strcpy(loc_info,calarr[i].info);
            newloc = strtok(loc_info,n);
            sprintf(loc_temp,"{{%s}}",newloc);
        } if (strcmp(calarr[i].property,"SUMMARY")==0) {
            strcpy(sum_info,calarr[i].info);
            newsum = strtok(sum_info,n);
            sprintf(line3,": %s %s",newsum,loc_temp);
            printf("%s",line3);
            line3[0] = '\0';
        }
        i++;
    }
    fclose(fp);

exit(0);

}

