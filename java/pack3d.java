public class  pack3d {

	
	public static class shape {
		
		side w;
		side h;
		side l;
		shape d;
		shape r;
		shape b;
	}

	public static class side {

		float size;
		char origSide;
		float tk;

	}

	private static int fitCount = 0;

	public static void main(String[] args) {


		if ( args.length < 3 ) {
                        System.out.println("3 arguments required: bin size (eg. 5x5x5), box size (eg. 1x1x1) and tol+kerf (eg 0.25,0.25,0.25)");
                        System.exit(1);
                }


		shape bin = new shape();
		shape box = new shape();
		
		bin.w = new side();
		bin.w.size = Float.parseFloat(args[0].split("x")[0]);
		bin.w.origSide = 'w';
		bin.w.tk = Float.parseFloat(args[2].split(",")[0]);

		bin.h = new side();
		bin.h.size = Float.parseFloat(args[0].split("x")[1]);
		bin.h.origSide = 'h';
		bin.h.tk = Float.parseFloat(args[2].split(",")[1]);

		bin.l = new side();
		bin.l.size = Float.parseFloat(args[0].split("x")[2]);
		bin.l.origSide = 'l';
		bin.l.tk = Float.parseFloat(args[2].split(",")[2]);

		box.w = new side();
		box.w.size = Float.parseFloat(args[1].split("x")[0]);
		box.w.origSide = 'w';

		box.h = new side();
		box.h.size = Float.parseFloat(args[1].split("x")[1]);
		box.h.origSide = 'h';

		box.l = new side();
		box.l.size = Float.parseFloat(args[1].split("x")[2]);		
		box.l.origSide = 'l';

		long start = System.currentTimeMillis();
		
		packIt(bin, box);

		long end = System.currentTimeMillis();
		long execTime = end - start;	
		System.out.println("found " + fitCount + " fits in " + execTime + " ms");
	}



	private static void packIt(shape bin, shape box) {


		//sort both bin and box
		if ( bin.w.size < bin.h.size) {

		        side tmpw = bin.w;
		        bin.w = bin.h;
		        bin.h = tmpw;
		}


		if ( bin.w.size < bin.l.size) {

		        side tmpw = bin.w;
		        bin.w = bin.l;
		        bin.l = tmpw;
		}


		if ( bin.h.size < bin.l.size ) {

                	side tmph = bin.h;
                	bin.h = bin.l;
                	bin.l = tmph;
        	}



        	if ( box.w.size < box.h.size ) {

                	side tmpw = box.w;
                	box.w = box.h;
                	box.h = tmpw;
        	}


        	if ( box.w.size < box.l.size ) {

                	side tmpw = box.w;
                	box.w = box.l;
                	box.l = tmpw;

        	}

        	if ( box.h.size < box.l.size ) {

               		side tmph = box.h;
                	box.h = box.l;
        	        box.l = tmph;
	
	        }



		if(box.w.size <= bin.w.size && box.h.size <= bin.h.size && box.l.size <= bin.l.size ) {

		        fitCount++;

		        //if it fits split box and recurse
		        splitBin(bin, box);
		        if ( bin.d != null )
		                packIt(bin.d, box);
		        if( bin.r != null )
		                packIt(bin.r, box);
			if ( bin.b != null )
                        	packIt(bin.b, box);

		}

	
	}
	
	private static void splitBin(shape bin, shape box) {

		float dW = bin.w.size;
		float dH = bin.h.size - box.h.size - bin.h.tk;
		float dL = bin.l.size;

		if ( dH <= 0 )
		        bin.d = null;
		else {

			bin.d = new shape();
			
			bin.d.w = new side();
			bin.d.h = new side();
			bin.d.l = new side();

			bin.d.w.size = dW;
			bin.d.w.origSide = bin.w.origSide;
			bin.d.w.tk = bin.w.tk;

			bin.d.h.size = dH;
			bin.d.h.origSide = bin.h.origSide;
			bin.d.h.tk = bin.h.tk;

			bin.d.l.size = dL;
			bin.d.l.origSide = bin.l.origSide;
			bin.d.l.tk = bin.l.tk;
		}

		
		float rW = bin.w.size - box.w.size - bin.w.tk;
		float rH = box.h.size;
		float rL = bin.l.size;

		if ( rW <= 0 )
		        bin.r = null;
		else {

			bin.r = new shape();

			bin.r.w = new side();
			bin.r.h = new side();
			bin.r.l = new side();

			bin.r.w.size = rW;
			bin.r.w.origSide = bin.w.origSide;
			bin.r.w.tk = bin.w.tk;

			bin.r.h.size = rH;
			bin.r.h.origSide = bin.h.origSide;
			bin.r.h.tk = bin.h.tk;

			bin.r.l.size = rL;
			bin.r.l.origSide = bin.l.origSide;
			bin.r.l.tk = bin.l.tk;
		}


		float bW = box.w.size;
                float bH = box.h.size;
                float bL = bin.l.size - box.l.size - bin.l.tk;

                if ( bL <= 0 )
                        bin.b = null;
                else {

                        bin.b = new shape();

			bin.b.w = new side();
			bin.b.h = new side();
			bin.b.l = new side();

			bin.b.w.size = bW;
			bin.b.w.origSide = bin.w.origSide;
			bin.b.w.tk = bin.w.tk;

			bin.b.h.size = bH;
			bin.b.h.origSide = bin.h.origSide;
			bin.b.h.tk = bin.h.tk;

			bin.b.l.size = bL;
			bin.b.l.origSide = bin.l.origSide;
			bin.b.l.tk = bin.l.tk;
                }




	}


}
