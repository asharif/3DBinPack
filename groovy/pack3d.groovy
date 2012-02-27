if(args.length < 3) {

        println"3 arguments required: bin size (eg. 5x5x5), box size (eg. 1x1x1) and tol+kerf (eg 1.25)"
        return;
}


def bin =  [  w: args[0].split('x')[0] as float, h: args[0].split('x')[1] as float, l: args[0].split('x')[2] as float, d: null, r:null, b: null ]
def box =  [  w: args[1].split('x')[0] as float , h: args[1].split('x')[1] as float, l: args[1].split('x')[2] as float]

fitCount =0
tolKerf = args[2] as float

def startTime = System.currentTimeMillis()

packIt(bin, box)

def stopTime = System.currentTimeMillis()

def calcTime = stopTime - startTime
println "found $fitCount fits in $calcTime ms"


def packIt(bin, box) {
			

	//sort both bin and box
	if ( bin.w < bin.h) {
		
		def tmpw = bin.w
		bin.w = bin.h
		bin.h = tmpw
	}

	if ( bin.w < bin.l ) {

		def tmpw = bin.w
		bin.w = bin.l
		bin.l = tmpw

	}

	if ( bin.h < bin.l ) {

		def tmph = bin.h
		bin.h = bin.l
		bin.l = tmph
	}



	if ( box.w < box.h) {

               	def tmpw = box.w
     		box.w = box.h
      		box.h = tmpw
       	}


	if ( box.w < box.l ) {
		
		def tmpw = box.w
		box.w = box.l
		box.l = tmpw

	}

	if ( box.h < box.l ) {

		def tmph = box.h
		box.h = box.l
		box.l = tmph

	}
		

	if( box.w <= bin.w && box.h <= bin.h && box.l <= bin.l ) {
			
		fitCount++

		//if it fits split box and recurse
		splitBin(bin, box)
		
		
		if ( bin.d != null )
			packIt(bin.d, box)
		if( bin.r != null )
			packIt(bin.r, box)
		if ( bin.b != null )
			packIt(bin.b, box)		
			
	}
	

}


def splitBin(bin, box) {

	def dW = bin.w
	def dH = bin.h - box.h - tolKerf
	def dL = bin.l

	if ( dH == 0 )
		bin.d = null
	else
		bin.d = [ w: dW, h: dH , l: dL]
	
	def rW = bin.w - box.w - tolKerf
	def rH = box.h
	def rL = bin.l

	if ( rW == 0)
		bin.r = null
	else
		bin.r = [ w: rW, h: rH, l: rL]


	def bW = box.w
	def bH = box.h
	def bL = bin.l - box.l - tolKerf

	if ( bL == 0 )
		bin.b = null
	else
		bin.b = [ w: bW, h: bH, l: bL]



}


