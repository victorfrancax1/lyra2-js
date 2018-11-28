function pad (num, size) {
  var s = num + '';
  while (s.length < size) s = '0' + s
  return s
}

// receives long array (blake2b's state) and returns a binary string array with 64bit padding
function long64Pad (arr) {
  var padded = arr.map((x) => pad(x.toString(2), 64))
  return padded
}

function stateStr (arr) {
	let str = 'Estado\n'
	for (let i = 0; i < arr.length; i++) {
		str += `Hex[${pad(i, 2)}]: ${pad(arr[i].toString(16).toUpperCase(), 16)}\n`
	}
	console.log(str)
}
// receives long array (blake2b's state) and returns 1024bit binary string
function longStringify (arr) {
  var result = long64Pad(arr).reduce((x, y) => x + y)
  return result
}

module.exports = {
  long64Pad,
  longStringify,
  stateStr
}
