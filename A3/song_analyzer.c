/** @file song_analyzer.c
 *  @brief A small program to analyze songs data.
 *  @author Mike Z.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Juan G.
 *  @author Soyun Lee
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_LINE_LEN 80

/**
 * @brief Serves as an incremental counter for navigating the list.
 *
 * @param p The pointer of the node to print.
 * @param arg The pointer of the index.
 *
 */
void inccounter(node_t *p, void *arg)
{
    int *ip = (int *)arg;
    (*ip)++;
}

/**
 * @brief Allows to print out the content of a node.
 *
 * @param p The pointer of the node to print.
 * @param arg The format of the string.
 *
 */
void print_node(node_t *p, void *arg) {
    char *fmt = (char *)arg;
    printf(fmt, p->artist, p->song, p->year, p->sortby);
}

/**
 * @brief Allows to print each node in the list.
 *
 * @param l The first node in the list
 *
 */
void analysis(node_t *l) {

    apply(l, print_node, "%s,%s,%d,%s\n");
}

/**
 * @brief Extracts the desired column and converts to int
 *
 * @param sortby string of the category
 * @return int n^th column equivalent to the category
 *
 */
int extract_sortby(char* sortby) {
    int category = 0;
    if (strcmp(sortby,"popularity")==0) {
        category = 5;
    } else if (strcmp(sortby,"danceability")==0) {
        category = 6;
    } else if (strcmp(sortby,"energy")==0) {
        category = 7;
    }
    return category;
}

/**
 * @brief Converts a line of top_songs_YEAR.csv into a song node
 *
 * @param artisted_passed Artist of the song
 * @param line Name of the song
 * @param category Number of the "sortBy" column
 * @param sortedby String of the "sortBy" column
 *
 */
void song_node(char* artist_passed, char* line, int category, char* sortedby) {
    int title_col = 1;
    char artist[MAX_LINE_LEN];
    char title[MAX_LINE_LEN];
    char sorted[MAX_LINE_LEN];
    char *value;
    int count = 1;

    // first column == artist
    value = strtok(line,",");
    strcpy(artist,value);
    while (count<=category) {
        value = strtok(NULL,",");
        // next column to artist == title
        if (count==title_col) {
            strcpy(title,value);
        // iterates the loop until count==category
        } else if (count==category) {
            strcpy(sorted,value);
        }
        count++;
    }
    // terminates strings with '\0'
    artist[sizeof(artist)-1] = '\0';
    title[sizeof(title)-1] = '\0';
    sorted[sizeof(sorted)-1] = '\0';
    memcpy(artist_passed,artist,sizeof(artist));
    memcpy(line,title,sizeof(title));
    memcpy(sortedby,sorted,sizeof(sorted));
}

/**
 * @brief Exports the final linked list to csv file
 *
 * @param list Final sorted linked list
 * @param sortby String of the category
 * @param display Number of lines that will display the linked list
 *
 */
void export_csv(node_t *list, char* sortby, int display) {
    
    FILE *output = fopen("output.csv", "w+"); // opens a file in write mode
    // grabs the first (head) node of the final linked list
    node_t *curr;
    curr = peek_front(list);
    int count = 0; // counter for comparing with display variable
    fprintf(output, "artist,song,year,%s\n",sortby); // prints the head row (name of columns)
    
    while (count<display) {
        fprintf(output,"%s,%s,%d,%s\n",curr->artist,curr->song,curr->year,curr->sortby);
        curr = curr->next; // let curr node becomes the next node
        count++;
    }
    
    // releases the allocated space for the list
    node_t *temp_n = NULL;
    for ( ; list != NULL; list = temp_n ) {
        temp_n = list->next;
        free(list->artist);
        free(list->song);
        free(list->sortby);
        free(list);
    }
    fclose(output);
}

/**
 * @brief Reads a file and adds song info to a node of linked list
 *
 * @param sortby String of the category
 * @param filename Name of a file that is being used
 * @param list Linked list that contains song info
 * @returns node_t Linked list after songs from filename have been added
 *
 */
node_t *read_file(char *sortby, char *filename, node_t *list) {
    
    FILE *fp = fopen(filename, "r");

    int file_size = 500; // max size for a line of top_songs_YEAR.csv
    char line[file_size];
    char artist[MAX_LINE_LEN];
    char sortedby[MAX_LINE_LEN];
    int row = 0; // initialized for skipping head row (name of columns) later
    int category;
    int year;

    sscanf(filename, "top_songs_%d.csv",&year); // extracts the year from filename
    
    while (fgets(line,file_size,fp)!=NULL) {
        // head row (name of columns) is skipped
        row++;
        if (row==1) {
            continue;
        }
        category = extract_sortby(sortby); // extracts the column number
        song_node(artist,line,category,sortedby); // pointer address of arguments are updated with needed info
        list = add_inorder(list, new_node(artist,line,year,sortedby)); // adds to linked_list in-order
    }
    fclose(fp);

    return list;
}


/**
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[]) {

    // if input isn't correct(i.e. not enough arguments), 1 is returned
    if (argc<4) {
        exit(1);

    } else {
        char filename1[MAX_LINE_LEN];
        char sortby[MAX_LINE_LEN];
        int display;
        node_t *list = NULL;

        sscanf(argv[1], "--sortBy=%s",sortby);
        sscanf(argv[2], "--display=%d",&display);

        // if input has one file:
        if (strlen(argv[3])==26) {
            sscanf(argv[3], "--files=%s",filename1);
            list = read_file(sortby,filename1,list);
        
        // if input has two files:
        } else if (strlen(argv[3])==45) {
            char filename2[MAX_LINE_LEN];
            sscanf(argv[3], "--files=%19[^,],%19[^,]",filename1,filename2);
            list = read_file(sortby,filename1,list);
            list = read_file(sortby,filename2,list);

        // if input has three files:
        } else {
            char filename2[MAX_LINE_LEN];
            char filename3[MAX_LINE_LEN];
            sscanf(argv[3], "--files=%19[^,],%19[^,],%19[^,]",filename1,filename2,filename3);
            list = read_file(sortby,filename1,list);
            list = read_file(sortby,filename2,list);
            list = read_file(sortby,filename3,list);
        }

        // takes the final node_t *list and converts into output.csv
        export_csv(list,sortby,display);

        exit(0);
    }
}
