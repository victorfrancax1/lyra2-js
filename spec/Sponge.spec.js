const { expect } = require('chai')
const { COMPARATOR_TEST, getValidOutputFromTest, runTest } = require('./utils.spec')
const { getLongStr, getLongsStr } = require('../utils')
const {
  BLAKE2B_IV,
  initState,
  rotr64,
  blake2bG
} = require('../Sponge')
describe('Sponge', () => {
  it('#initState: Should work fine', async () => {
    const cResult = await runTest(COMPARATOR_TEST.InitState)
    const cOutput = getValidOutputFromTest(cResult)
    const spongeOutput = getLongsStr(initState())
    expect(cOutput).to.be.equal(spongeOutput)
  })

  it('#rotr64: Should work fine', async () => {
    const cResult = await runTest(COMPARATOR_TEST.Rotr64)
    const cOutput = getValidOutputFromTest(cResult)
    const spongeOutput = getLongStr(rotr64(BLAKE2B_IV[0], 5))
    expect(cOutput).to.be.equal(spongeOutput)
  })

  it('#blake2bG: Should work fine', async () => {
    const cResult = await runTest(COMPARATOR_TEST.blake2bG)
    const cOutput = getValidOutputFromTest(cResult)
    const state = initState()
    const spongeOutput = getLongsStr(blake2bG(state, 10, 11, 12, 13))
    expect(cOutput).to.be.equal(spongeOutput)
  })
})
