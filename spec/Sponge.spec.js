const { expect } = require('chai')
const { COMPARATOR_TEST, getValidOutputFromTest, runTest } = require('./utils.spec')
const { getLongStrForComparison, getLongsStr } = require('../utils')
const { initState, rotr64 } = require('../Sponge')
describe('Sponge', () => {
  it('#initState: Should work fine', async () => {
    const cResult = await runTest(COMPARATOR_TEST.InitState)
    const cOutput = getValidOutputFromTest(cResult)
    const spongeOutput = getLongsStr(initState())
    expect(cOutput).to.be.equal(spongeOutput)
  })
})
