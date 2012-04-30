#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#include<time.h>
#include"libpack3d.h"


void getSizeVector(char size[], float sizeV[], char *del )
{


        char * pchar;
        pchar = strtok ( size,  del );

        
        int i = 0;

        while ( pchar != NULL)
        {
                sizeV[i] = atof(pchar);
                i++;
                pchar = strtok ( NULL, del );

        }



}



main(int argc, char * argv[])
{

	if ( argc < 4 )
        {
                printf("3 arguments required: bin size (eg. 5x5x5), box size (eg. 1x1x1) and tol+kerf for each side(eg 0.25,0.25,0.25)\n");
                exit(1);

        }


	float binSizeV[3];
	float boxSizeV[3];
	float tolKerfV[3];
	
	getSizeVector(argv[1], binSizeV, "x");
	getSizeVector(argv[2], boxSizeV, "x");	
	getSizeVector(argv[3], tolKerfV, ",");
	

	struct PACK3D_shape *bin;
	struct PACK3D_shape *box;
	bin = ( struct PACK3D_shape * ) malloc(sizeof( struct PACK3D_shape ));
	box = ( struct PACK3D_shape *) malloc(sizeof( struct PACK3D_shape ) );



	bin->w = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side ));
	bin->w->size = binSizeV[0];
	bin->w->tk = tolKerfV[0];
	bin->h = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side ));
	bin->h->size = binSizeV[1];
	bin->h->tk = tolKerfV[1];
	bin->l = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side ));
	bin->l->size = binSizeV[2];
	bin->l->tk = tolKerfV[2];
	bin->d = NULL;
	bin->r = NULL;
	bin->b = NULL;
	box->w = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side ));
	box->w->size = boxSizeV[0];
	box->h = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side ));
	box->h->size = boxSizeV[1];
	box->l = ( struct PACK3D_side * ) malloc(sizeof( struct PACK3D_side ));
	box->l->size = boxSizeV[2];

	//struct timeval start;
	//struct timeval end;
	
	//gettimeofday(&start);
	
	PACK3D_packIt(bin, box);

	//free them!
	free(bin->w);
	free(bin->h);
	free(bin->l);
	free(bin);
	free(box->w);
	free(box->h);
	free(box->l);
	free(box);

	//gettimeofday(&end);
	
	//long execTimeS = end.tv_sec - start.tv_sec;
	//long execTimeMicS = end.tv_usec  - start.tv_usec ;

	//float fexecTime = (execTimeS*1000) + ((float)execTimeMicS)/1000;
	

	//printf("found %d fits in %f ms\n", PACK3D_fitCount, fexecTime);
	printf("found %d fits\n", PACK3D_fitCount);

}
	
