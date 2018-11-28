const { getLongStr, getLongsStr } = require('../utils')
const {
  BLAKE2B_IV,
  initState,
  rotr64,
  blake2bG,
  roundLyra,
  spongeLyra
} = require('../Sponge')

const tests = {
  '0': () => getLongsStr(initState()),
  '1': () => getLongStr(rotr64(BLAKE2B_IV[0], 5)),
  '2': () => {
    const state = initState()
    return getLongsStr(blake2bG(state, 10, 11, 12, 13))
  },
  '3': () => {
    const state = initState()
    return getLongsStr(roundLyra(state))
  }
}

module.exports = {
  tests
}
