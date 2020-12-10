/*
    Project 2
    ENEE150 Fall 2020
    Joseph M Krzyzek
*/

#include "admissions.h"

char students[MAXSTUDENTS][5][MAXCHAR];
char rank[25][MAXCHAR];
char publication[MAXCHAR][2][MAXCHAR];

int main(int argc, char **argv)
{
  char line[MAXLINE];
  char last_name[MAXCHAR], first_name[MAXCHAR];
  char school[MAXCHAR];
  char pub1[MAXCHAR], pub2[MAXCHAR];
  float gpa = 0, score = 0;
  int index = 0, stringLength = 0, rank = 0, pubs = 0, gre_v = 0, gre_q = 0;

  if(argc != 5)
  {
    printf("Incorrect number of txt files.\n");
    exit(-1);
  }

  FILE *appFile = fopen( argv[1], "r" );
  FILE *rankFile = fopen( argv[2], "r" );
  FILE *journalFile = fopen(argv[3], "r");
  FILE *outFile = fopen(argv[4], "w");

  // Read in rankings and journal to char arrays for reference, later.
  rankings( rankFile );
  journal( journalFile );

  if(appFile == NULL)
  {
    printf("Can not open the applicant file\n");
    exit(0);
  }

  /*
  This is the main loop that simulanously reads in appFile line by line
  Computes the score
  And prints it to the output file.
  */
  while( fgets(line, MAXLINE, appFile) != NULL )
  {
    // Scan the line and grab the number of pubs
    // From there grab the rest of the info.
    // Also compute and print to the output file
    sscanf(line, "%[^,], %[^,], %f, %d, %d, %d, %[^,]," ,last_name, first_name, &gpa, &gre_v, &gre_q, &pubs, school);
    if(pubs == 1)
    {
      sscanf(line, "%[^,], %[^,], %f, %d, %d, %d, %[^,], %[^\n]",last_name, first_name, &gpa, &gre_v, &gre_q, &pubs, school, pub1);
      strcpy( students[index][0], last_name );
      strcpy( students[index][1], first_name );
      strcpy( students[index][2], school );
      strcpy( students[index][3], pub1 );
      students[index][4][1] = '\0';

      stringLength = strlen(last_name);
      fputs(last_name, outFile);
      while(stringLength < 15)
      {
        fputs(" ", outFile);
        stringLength++;
      }
      stringLength = strlen(first_name);
      fputs(first_name, outFile);
      while(stringLength < 15)
      {
        fputs(" ", outFile);
        stringLength++;
      }
      score = compute_score( index, gpa, gre_v, gre_q, pubs );
      fprintf(outFile, "%.2f", score);
      fputs("\t", outFile);
      rank = school_rank( index );
      fprintf(outFile, "%d", rank);
      fputs("\n", outFile);

    }
    else if(pubs == 2)
    {
      sscanf(line, "%[^,], %[^,], %f, %d, %d, %d, %[^,], %[^,], %[^\n]",last_name, first_name, &gpa, &gre_v, &gre_q, &pubs, school, pub1, pub2);
      strcpy( students[index][0], last_name );
      strcpy( students[index][1], first_name );
      strcpy( students[index][2], school );
      strcpy( students[index][3], pub1 );
      strcpy( students[index][4], pub2 );

      stringLength = strlen(last_name);
      fputs(last_name, outFile);
      while(stringLength < 15)
      {
        fputs(" ", outFile);
        stringLength++;
      }
      stringLength = strlen(first_name);
      fputs(first_name, outFile);
      while(stringLength < 15)
      {
        fputs(" ", outFile);
        stringLength++;
      }
      score = compute_score( index, gpa, gre_v, gre_q, pubs );
      fprintf(outFile, "%.2f", score);
      fputs("\t", outFile);
      rank = school_rank( index );
      fprintf(outFile, "%d", rank);
      fputs("\n", outFile);
    }
    else
    {
      strcpy( students[index][0], last_name );
      strcpy( students[index][1], first_name );
      strcpy( students[index][2], school );
      students[index][3][1] = '\0';
      students[index][4][1] = '\0';

      stringLength = strlen(last_name);
      fputs(last_name, outFile);
      while(stringLength < 15)
      {
        fputs(" ", outFile);
        stringLength++;
      }
      stringLength = strlen(first_name);
      fputs(first_name, outFile);
      while(stringLength < 15)
      {
        fputs(" ", outFile);
        stringLength++;
      }
      score = compute_score( index, gpa, gre_v, gre_q, pubs );
      fprintf(outFile, "%.2f", score);
      fputs("\t", outFile);
      rank = school_rank( index );
      fprintf(outFile, "%d", rank);
      fputs("\n", outFile);
    }
    index++;
  }

  fclose(appFile);
  fclose(rankFile);
  fclose(journalFile);
  fclose(outFile);

  return(0);

}
