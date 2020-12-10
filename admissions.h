/*
    Project 2
    ENEE150 Fall 2020
    Joseph M Krzyzek
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTUDENTS 1000
#define MAXLINE 2000
#define MAXCHAR 256

extern char students[MAXSTUDENTS][5][MAXCHAR];
extern char rank[25][MAXCHAR];
extern char publication[MAXCHAR][2][MAXCHAR];

/***************************/
/*** FUNCTION PROTOTYPES ***/
/***************************/
void rankings( FILE *rankFile );
void journal( FILE *journalFile );

int school_rank(int index);

int school_score( int index );
float impact_score( int index, int pubs );
float compute_score( int index, float gpa, int gre_v, int gre_q, int pubs );
