#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct shape
{
	float w;
	float h;
	float l;
	struct shape *r;
	struct shape *d;
	struct shape *b;
};

int fitCount = 0;
float tolKerf;



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

void splitBin(struct shape *bin, struct shape *box) {

        float dW = bin->w;
        float dH = bin->h - box->h - tolKerf;
	float dL = bin->l;

	if ( dH == 0 )
                bin->d = NULL;
        else
	{
		struct shape *binD;
		binD = ( struct shape *) malloc(sizeof( struct shape ) );
		binD->w = dW;
		binD->h = dH;
		binD->l = dL;
		bin->d = binD;

	}


        float rW = bin->w - box->w - tolKerf;
        float rH = box->h;
	float rL = bin->l;

        if ( rW == 0 )
                bin->r = NULL;
        else
	{

		struct shape *binR;
		binR = ( struct shape *) malloc( sizeof ( struct shape ) );
		binR->w = rW;
		binR->h = rH;
		binR->l = rL;
		bin->r = binR;
	}


	float bW = box->w;
        float bH = box->h;
        float bL = bin->l - box->l - tolKerf;

        if ( bL == 0 )
                bin->b = NULL;
        else
        {

                struct shape *binB;
                binB = ( struct shape *) malloc( sizeof ( struct shape ) );
                binB->w = bW;
                binB->h = bH;
                binB->l = bL;
                bin->b = binB;
        }



}


void packIt( struct shape *bin, struct shape *box)
{
	//sort both bin and box
        if ( bin->w < bin->h ) 
	{

                float tmpw = bin->w;
                bin->w = bin->h;
                bin->h = tmpw;
        }


        if ( box->w < box->h ) 
	{

                float tmpw = box->w;
                box->w = box->h;
                box->h = tmpw;
        }

	if ( bin->h < bin->l )
	 {

                float tmph = bin->h;
                bin->h = bin->l;
                bin->l = tmph;
        }



        if ( box->w < box->h) 
	{

                float tmpw = box->w;
                box->w = box->h;
                box->h = tmpw;
        }


        if ( box->w < box->l )
	 {

                float tmpw = box->w;
                box->w = box->l;
                box->l = tmpw;

        }

        if ( box->h < box->l ) 
	{

                float tmph = box->h;
                box->h = box->l;
                box->l = tmph;

        }


        if( box->w <= bin->w && box->h <= bin->h && box->l <= bin->l ) 
	{

                fitCount++;

                //if it fits split box and recurse
                splitBin( bin, box );
		
		if ( bin->d != NULL )
		{
                        packIt( bin->d, box );
                	free( bin->d );
		}
		
		if( bin->r != NULL )
		{
                        packIt( bin->r, box );
			free( bin->r );
		}
		
		if( bin->b != NULL )
		{
			packIt( bin->b, box );
			free( bin->b );
		}
        }


}



main(int argc, char * argv[])
{

	if ( argc < 4 )
        {
                printf("3 arguments required: bin size (eg. 5x5x5), box size (eg. 1x1x1) and tol+kerf (eg 1.25)\n");
                exit(1);

        }


	float binSizeV[3];
	float boxSizeV[3];
	
	getSizeVector(argv[1], binSizeV, "x");
	getSizeVector(argv[2], boxSizeV, "x");	

	tolKerf = atof(argv[3]);
	

	struct shape *bin;
	struct shape *box;
	bin = ( struct shape * ) malloc(sizeof( struct shape ));
	box = ( struct shape *) malloc(sizeof( struct shape ) );



	bin->w = binSizeV[0];
	bin->h = binSizeV[1];
	bin->l = binSizeV[2];
	bin->d = NULL;
	bin->r = NULL;
	bin->b = NULL;
	box->w = boxSizeV[0];
	box->h = boxSizeV[1];
	box->l = boxSizeV[2];

	struct timeval start;
	struct timeval end;
	
	gettimeofday(&start);
	
	packIt(bin, box);

	//free them!
	free(bin);
	free(box);

	gettimeofday(&end);
	
	long execTimeS = end.tv_sec - start.tv_sec;
	long execTimeMicS = end.tv_usec  - start.tv_usec ;

	float fexecTime = (execTimeS*1000) + ((float)execTimeMicS)/1000;
	

	printf("found %d fits in %f ms\n", fitCount, fexecTime);
}
	
