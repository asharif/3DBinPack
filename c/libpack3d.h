struct PACK3D_side
{

	float size;
	char origSide;
	float tk; //tolerance + kerf

};

struct PACK3D_shape
{
        struct PACK3D_side *w;
        struct PACK3D_side *h;
        struct PACK3D_side *l;
        struct PACK3D_shape *r;
        struct PACK3D_shape *d;
        struct PACK3D_shape *b;
};


extern int PACK3D_fitCount;


void PACK3D_splitBin(struct PACK3D_shape *bin, struct PACK3D_shape *box);
void PACK3D_packIt( struct PACK3D_shape *bin, struct PACK3D_shape *box);
int PACK3D_getCount(float binsize1, float binsize2, float binsize3, float boxsize1, float boxsize2, float boxsize3, 
		    float tkw, float tkh, float tkl);
