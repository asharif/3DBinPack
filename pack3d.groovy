


def bin =  [ x:0, y:0, z: 0,  w: args[0].split(',')[0] as int, h: args[0].split(',')[1] as int, l: args[0].split(',')[2] as int, sbind: null, sbinr:null, sbinb: null, t: 'root', used: false ]

def box =  [ x:0, y:0, z: 0,  w: args[1].split(',')[0] as int , h: args[1].split(',')[1] as int, l: args[1].split(',')[2] as int]

fitCount =0


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
		//set this bin as used
		bin.used = true

		//if it fits split box and recurse
		splitBin(bin, box)
		if ( bin.sbind != null )
			packIt(bin.sbind, box)
		if( bin.sbinr != null )
			packIt(bin.sbinr, box)
		if ( bin.sbinb != null )
			packIt(bin.sbinb, box)		
			
	}
	

}


def splitBin(bin, box) {

	def sbindW = bin.w
	def sbindH = bin.h - box.h
	def sbindL = bin.l

	if ( sbindH == 0 )
		bin.sbind = null
	else
		bin.sbind = [ x: bin.x, y: bin.y + box.h, w: sbindW, h: sbindH , l: sbindL,  t: 'd']
	
	def sbinrW = bin.w - box.w
	def sbinrH = box.h
	def sbinrL = bin.l

	if ( sbinrW == 0)
		bin.sbinr = null
	else
		bin.sbinr = [ x: bin.x + box.w, y: bin.y, w: sbinrW, h: sbinrH, l: sbinrL, t: 'r']


	def sbinbW = box.w
	def sbinbH = box.h
	def sbinbL = bin.l - box.l

	if ( sbinbL == 0 )
		bin.sbinb = null
	else
		bin.sbinb = [ x: bin.x + box.w, y: bin.y, w: sbinbW, h: sbinbH, l: sbinbL, t: 'b']



}


