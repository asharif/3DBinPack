#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "Pack3DJNI.h"

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


        if ( bin->w < bin->l ) 
	{

                float tmpw = bin->w;
                bin->w = bin->l;
                bin->l = tmpw;
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
		       free ( bin->r );
			
		}
		if( bin->b != NULL )
		{

			packIt( bin->b, box );
        		free ( bin->b );
		}
	}


}


//this is what should be called at end of day!
JNIEXPORT jint JNICALL Java_Pack3DJNI_getCount
(JNIEnv *env, jobject obj, jfloat binsize1, jfloat binsize2, jfloat binsize3, jfloat boxsize1, jfloat boxsize2, jfloat boxsize3, jfloat tk)
{

	struct shape *bin;
        struct shape *box;
        bin = ( struct shape * ) malloc(sizeof( struct shape ));
        box = ( struct shape *) malloc(sizeof( struct shape ) );



        bin->w = binsize1;
        bin->h = binsize2;
        bin->l = binsize3;
        bin->d = NULL;
        bin->r = NULL;
        bin->b = NULL;
        box->w = boxsize1;
        box->h = boxsize2;
        box->l = boxsize3;

	tolKerf = tk;

	packIt(bin, box);

	free ( bin );
	free ( box );
	
	return fitCount;

}

