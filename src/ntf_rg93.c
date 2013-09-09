#ifndef __LAMBERT_CONFIG_H
#define __LAMBERT_CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ntf_rg93.h"
#include "config.h"
#include <zlog.h>

#define MAX_LINE_BUFFER 100
#define MAX_PATH_BUFFER 100
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

void test_file()
{	
	char grid_file_path[MAX_PATH_BUFFER];
	char line_buffer[MAX_LINE_BUFFER];

	snprintf(grid_file_path,50,"%s/%s",resource_file_path,"gr3df97a.txt");
	
	FILE *fd = fopen(grid_file_path,"r");
		
	if(!fd)
	{
		printf("Error could not open grid file");
		exit(EXIT_FAILURE);
	}

	int c = 0,index = 0;
	do
	{
		c = fgetc(fd);
		++index;

		if(index > MAX_LINE_BUFFER || c == '\n')
		{
			printf("%s\n",line_buffer);
			index = 0;
			memset(line_buffer,0,MAX_LINE_BUFFER);
		}

		line_buffer[index] = c;
	}
	while(c != EOF);

	fclose(fd);
}

#endif