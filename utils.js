'use strict'

function pad (num, size) {
  var s = num + ''
  while (s.length < size) s = '0' + s
  return s
}

// receives long array (blake2b's state) and returns a binary string array with 64bit padding
function long64Pad (arr) {
  return arr.map((x) => pad(x.toString(2), 64))
}

/**
 * Retorna uma string para print de um array de longs
 * @param {import('long')[]} arr
 */
function getLongsStr (arr, name = 'Estado') {
  let str = `${name}\n`
  for (let i = 0; i < arr.length; i++) {
    str += `Hex[${pad(i, 2)}]: ${pad(arr[i].toString(16).toUpperCase(), 16)}\n`
  }
  return str
}

/**
 * Returns long str print for comparison
 * @param {import('long')} long
 */
const getLongStr = (long) => {
  return `Dec: ${long.toString()}\n` + `Hex: ${pad(long.toString(16).toUpperCase(), 16)}\n` + `Bin: ${pad(long.toString(2), 64)}\n`
}
// receives long array (blake2b's state) and returns 1024bit binary string
function longStringify (arr) {
  var result = long64Pad(arr).reduce((x, y) => x + y)
  return result
}

module.exports = {
  long64Pad,
  longStringify,
  getLongsStr,
  getLongStr
}
