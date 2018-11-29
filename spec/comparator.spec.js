'use strict'
const { getLongStr, getLongsStr, byteFormat } = require('../utils')
const Long = require('long')
const {
  BLAKE2B_IV,
  initState,
  rotr64,
  blake2bG,
  roundLyra,
  spongeLyra,
  absorbColumn,
  absorbBlockBlake2bSafe,
  squeeze
} = require('../Sponge')
const COMPARATOR_TEST = {
  InitState: 0,
  Rotr64: 1,
  blake2bG: 2,
  roundLyra: 3,
  spongeLyra: 4,
  absorbColumn: 5,
  absorbBlockBlake2bSafe: 6,
  squeeze: 7
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
  },
  '5': () => {
    const state = initState()
    const arr = []
    for (let i = 0; i < 12; i++) {
      arr.push(new Long(0xDbAAbd6b, 0x1f83d9aC, true))
    }
    return getLongsStr(absorbColumn(state, arr))
  },
  '6': () => {
    const state = initState()
    const arr = []
    for (let i = 0; i < 12; i++) {
      arr.push(new Long(0xDbAAbd6b, 0x1f83d9aC, true))
    }
    return getLongsStr(absorbBlockBlake2bSafe(state, arr))
  },
  '7': () => {
    let state = initState()
    state = spongeLyra(state)
    const sqResult = squeeze(state, 10)
    console.log(sqResult[0].map(d => byteFormat(d)))
  }
}

module.exports = {
  tests,
  COMPARATOR_TEST
}
