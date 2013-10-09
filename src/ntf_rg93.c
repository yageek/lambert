#ifndef __LAMBERT_CONFIG_H
#define __LAMBERT_CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "ntf_rg93.h"
#include "config.h"


#define MAX_LINE_BUFFER 1024
#define MAX_PATH_BUFFER 1024


typedef struct {

	double lon;
	double lat;
	double tx;
	double ty;
	double tz;
	double precision;
} NTV2Reg;

static char grd3dparams[4][MAX_LINE_BUFFER] = {{0}};

/**
* From : http://geodesie.ign.fr/contenu/fichiers/documentation/algorithmes/notice/NT111_V1_HARMEL_TransfoNTF-RGF93_FormatGrilleNTV2.pdf
*/

YGLambertPoint intpol_gsb(YGLambertPoint ntf_point)
{

	YGLambertPoint dest = {0,0,0};

	double longdd_NTF = ntf_point.x;
	double latdd_NTF = ntf_point.y;

	double lonw = -longdd_NTF*3600;
	double latn = latdd_NTF*3600;

	return dest;

}

void rgf93_to_ntf(YGLambertPoint rgf_point)
{	
	char grid_file_path[MAX_PATH_BUFFER];
	char line_buffer[MAX_LINE_BUFFER];
    
	snprintf(grid_file_path,50,"%s/%s",resource_file_path,"gr3df97a.txt");

	memset(grd3dparams,0,4*MAX_LINE_BUFFER);
	
	FILE *fd = fopen(grid_file_path,"r");
		
	if(!fd)
	{
		printf("Error could not open grid file at file:%s",resource_file_path);
		exit(EXIT_FAILURE);
	}
    
    
	fclose(fd);
}

void printParameters()
{
	printf("===== Parameters =====\n");
	printf("%s\n", grd3dparams[0]);
	printf("%s\n", grd3dparams[1]);
	printf("%s\n", grd3dparams[2]);
	printf("%s\n", grd3dparams[3]);

}

#endif