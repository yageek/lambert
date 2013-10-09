
#include "ntv2.h"
#include "config.h"

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include <string.h>

#define MAX_LINE_BUFFER 1024
#define MAX_PATH_SIZE 1024
#define DELTA_REALLOCATION 10

typedef struct {
    
	double lon;
	double lat;
	double tx;
	double ty;
	double tz;
	double precision;
} NTV2Reg;

static char currentNTVPath[OPEN_MAX];
static FILE * gridFD = NULL;
static char grd3dparams[4][MAX_LINE_BUFFER] = {{0}};

static NTV2Reg *regcache = NULL;
static int lastRegPos = 0;
static int regcacheSize = 0;

static int lastReadedLine;


NTV2Reg regFromLine(const char * line)
{
    char *sep = "   ";
    char *buffer = malloc(strlen(line)* sizeof(char));
    strcpy(buffer, line);
    
    NTV2Reg reg = {0};
    
    strtok(buffer, sep);
    
   reg.lon = strtod(strtok(NULL, sep), NULL);
   reg.lat = strtod(strtok(NULL, sep), NULL);
   reg.tx = strtod(strtok(NULL, sep), NULL);
   reg.ty = strtod(strtok(NULL, sep), NULL);
   reg.tz = strtod(strtok(NULL, sep), NULL);
   reg.precision = strtod(strtok(NULL, sep), NULL);
    
   return reg;
}

void addRegToCache(NTV2Reg reg)
{
    if(!regcache)
    {
        regcache = malloc(DELTA_REALLOCATION*sizeof(NTV2Reg));
        regcacheSize = DELTA_REALLOCATION;
        lastRegPos = 0;
    }
    
    if(lastRegPos > regcacheSize-1)
    {

        NTV2Reg * newLoc =realloc(regcache, (regcacheSize+DELTA_REALLOCATION)*sizeof(NTV2Reg));
       
        regcache = newLoc;
        regcacheSize+=DELTA_REALLOCATION;
    
    }
    
    regcache[lastRegPos] = reg;
    lastRegPos++;
}


int loadGrid()
{
    snprintf(currentNTVPath,50,"%s/%s",resource_file_path,"gr3df97a.txt");
    lastReadedLine = 0;
    
    gridFD = fopen(currentNTVPath,"r");
    
    if(!gridFD)
    {
        printf("Could not open grid file at path :%s\n", currentNTVPath);
        return -1;
    }
    
    char line[MAX_LINE_BUFFER];
    while(lastReadedLine < 4)
    {
        fgets(line, MAX_LINE_BUFFER, gridFD);
        ++lastReadedLine;
    }
    char line_buffer[MAX_LINE_BUFFER] = {0};
    
    while(NULL != fgets(line_buffer, MAX_LINE_BUFFER, gridFD))
    {
        NTV2Reg reg = regFromLine(line_buffer);
        addRegToCache(reg);
    }

    return 0;
}


void printParameters()
{
	printf("===== Parameters =====\n");
	printf("%s\n", grd3dparams[0]);
	printf("%s\n", grd3dparams[1]);
	printf("%s\n", grd3dparams[2]);
	printf("%s\n", grd3dparams[3]);
    
}

void printReg(NTV2Reg reg)
{
    printf("LON:%f - LAT:%f - TX:%f - TY:%f - TZ:%f - PRE:%f\n",reg.lon,reg.lat,reg.tx,reg.ty,reg.tz,reg.precision);
}
void unloadGrid()
{
    fclose(gridFD);
    free(regcache);
}

void rgf93_to_ntf(YGLambertPoint pt)
{
    if(!gridFD)
        loadGrid();
        
    int foundlat = 0, foundlon=0;
    
    NTV2Reg t1,t2,t3,t4;
    
    double minLat, maxLat;
    for(int i =0; i< lastRegPos;++i)
    {
        NTV2Reg a = regcache[i], b = regcache[i+1];
        if(pt.x >= a.lon && pt.x <=b.lon)
        {
            minLat = a.lon;
            maxLat = b.lon;
            break;
        }
        
    }
    
    
    unloadGrid();
}