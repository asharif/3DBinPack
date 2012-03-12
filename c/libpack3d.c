#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"libpack3d.h"

int PACK3D_fitCount;
float PACK3D_tolKerf;


void PACK3D_splitBin(struct PACK3D_shape *bin, struct PACK3D_shape *box) {

        float dW = bin->w;
        float dH = bin->h - box->h - PACK3D_tolKerf;
	float dL = bin->l;

	if ( dH <= 0 )
                bin->d = NULL;
        else
	{
		struct PACK3D_shape *binD;
		binD = ( struct PACK3D_shape *) malloc(sizeof( struct PACK3D_shape ) );
		binD->w = dW;
		binD->h = dH;
		binD->l = dL;
		bin->d = binD;

	}


        float rW = bin->w - box->w - PACK3D_tolKerf;
        float rH = box->h;
	float rL = bin->l;

        if ( rW <= 0 )
                bin->r = NULL;
        else
	{

		struct PACK3D_shape *binR;
		binR = ( struct PACK3D_shape *) malloc( sizeof ( struct PACK3D_shape ) );
		binR->w = rW;
		binR->h = rH;
		binR->l = rL;
		bin->r = binR;
	}


	float bW = box->w;
        float bH = box->h;
        float bL = bin->l - box->l - PACK3D_tolKerf;

        if ( bL <= 0 )
                bin->b = NULL;
        else
        {

                struct PACK3D_shape *binB;
                binB = ( struct PACK3D_shape *) malloc( sizeof ( struct PACK3D_shape ) );
                binB->w = bW;
                binB->h = bH;
                binB->l = bL;
                bin->b = binB;
        }



}


void PACK3D_packIt( struct PACK3D_shape *bin, struct PACK3D_shape *box)
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

                PACK3D_fitCount++;

                //if it fits split box and recurse
                PACK3D_splitBin( bin, box );
		
		if ( bin->d != NULL )
		{
                        PACK3D_packIt( bin->d, box );
                	free( bin->d );
		}

		if( bin->r != NULL )
                { 

		       PACK3D_packIt( bin->r, box );
		       free ( bin->r );
	
		}
		if( bin->b != NULL )
		{

			PACK3D_packIt( bin->b, box );
        		free ( bin->b );
		}
	}


}


//this is what should be called at end of day!
int PACK3D_getCount(float binsize1, float binsize2, float binsize3, float boxsize1, float boxsize2, float boxsize3, float tk)
{

	
	PACK3D_fitCount = 0;

	struct PACK3D_shape *bin;
        struct PACK3D_shape *box;
        bin = ( struct PACK3D_shape * ) malloc(sizeof( struct PACK3D_shape ));
        box = ( struct PACK3D_shape *) malloc(sizeof( struct PACK3D_shape ) );



        bin->w = binsize1;
        bin->h = binsize2;
        bin->l = binsize3;
        bin->d = NULL;
        bin->r = NULL;
        bin->b = NULL;
        box->w = boxsize1;
        box->h = boxsize2;
        box->l = boxsize3;

	PACK3D_tolKerf = tk;

	PACK3D_packIt(bin, box);

	free ( bin );
	free ( box );


	return PACK3D_fitCount;

}

