// library used for uint_64 numbers
var Long  = require('long');

//Blake2b IV array
var BLAKE2B_IV = [
	new Long(0x6a09e667f3bcc908),
	new Long(0xbb67ae8584caa73b),
	new Long(0x3c6ef372fe94f82b),
	new Long(0xa54ff53a5f1d36f1),
	new Long(0x510e527fade682d1),
	new Long(0x9b05688c2b3e6c1f),
	new Long(0x1f83d9abfb41bd6b),
	new Long(0x5be0cd19137e2179),
]
