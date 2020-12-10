
#include <stdio.h>
#include "admissions.h"

/*****************************/
/*** FUNCTION DECLARATIONS ***/
/*****************************/
void rankings( FILE *rankFile )
{

  char line[MAXLINE];
  char delimiter[5];
  char school[MAXCHAR];
  int i = 0, j = 0;

  if( rankFile == NULL )
  {
    printf( "Can not open journal file\n" );
    exit( 0 );
  }

  while( fgets( line, MAXLINE, rankFile ) != NULL )
  {
    sscanf( line, "%[^.]. %[^\n]", delimiter, school );
    strcpy( rank[i], school );
    i++;
  }

}

void journal( FILE *journalFile )
{

  char line[MAXLINE];
  char journal[MAXCHAR];
  char impact[MAXCHAR];
  int i = 0;

  if( journalFile == NULL )
  {
    printf( "Can not open journal file\n" );
    exit( 0 );
  }

  while( fgets( line, MAXLINE, journalFile ) != NULL)
  {
    sscanf( line, "%[^,], %[^\n]", journal, impact );
    strcpy( publication[i][0], journal );
    strcpy( publication[i][1], impact );
    i++;
  }

}

int school_rank(int index)
{
  int ranking = 0;
  while( strcmp(students[index][2], rank[ranking]) != 0)
  {
    if(ranking > 25)
    {
      return(ranking);
      break;
    }
    ranking++;
  }
  ranking++;
  return(ranking);
}

int school_score( int index )
{
  int j = 0;
  while( students[index][2][j] != '\0')
  {
    if( students[index][2][j] == '\n')
    {
      students[index][2][j] = '\0';
      break;
    }
    j++;
  }

  int result = 0, ranking = 0;
  while( (strcmp(students[index][2], rank[ranking]) != 0) && (ranking < 25))
  {
    ranking++;
  }
  if( ranking <= 9 )
  {
    result = 10;
    return(result) ;
  }
  if( (ranking >= 10) && (ranking <= 19) )
  {
    result = 5;
    return(result);
  }
  return(result);
}

float impact_score( int index, int pubs )
{
  float result = 0;
  int j = 0;
  if(pubs == 0)
  {
    return result;
  }

  if(pubs > 0)
  {
    while( students[index][3][j] != '\0')
    {
      if( students[index][3][j] == '\n')
      {
        students[index][3][j] = '\0';
        break;
      }
      j++;
    }
    j = 0;
    while( strcmp(students[index][3], publication[j][0]) != 0 )
    {
      j++;
      if(j > 256)
          break;
    }
    result += atof(publication[j][1])*10;
  }
  j = 0;

  if(pubs > 1)
  {
    while( students[index][4][j] != '\0')
    {
      if( students[index][4][j] == '\n')
      {
        students[index][4][j] = '\0';
        break;
      }
      j++;
    }
    j = 0;
    while( strcmp(students[index][4], publication[j][0]) != 0 )
    {
      j++;
      if(j > 256)
          break;
    }
    result += atof(publication[j][1])*10;
  }
  return result;
}

float compute_score( int index, float gpa, int gre_v, int gre_q, int pubs )
{

  float baseline_score = 0;
  baseline_score = ( ( (gpa/4.0) + (gre_v/800.0) + (gre_q/800.0) ) / 3.0) * 100.0;
  baseline_score += school_score( index );
  baseline_score += impact_score( index, pubs );

  return(baseline_score);

}
