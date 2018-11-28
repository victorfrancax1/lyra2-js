const { getLongStr, getLongsStr } = require('../utils')
const {
  BLAKE2B_IV,
  initState,
  rotr64,
  blake2bG,
  roundLyra,
  spongeLyra
} = require('../Sponge')

const COMPARATOR_TEST = {
  InitState: 0,
  Rotr64: 1,
  blake2bG: 2,
  roundLyra: 3,
  spongeLyra: 4
}

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
  },
  '4': () => {
    const state = initState()
    return getLongsStr(spongeLyra(state))
  }
}

module.exports = {
  tests,
  COMPARATOR_TEST
}
