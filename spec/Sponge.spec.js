const { expect } = require('chai')
const { COMPARATOR_TEST, getValidOutputFromTest, runTest } = require('./utils.spec')
const { tests } = require('./funcsTests.spec')

const assertTest = async (num) => {
  const cResult = await runTest(num)
  const cOutput = getValidOutputFromTest(cResult)
  expect(cOutput).to.be.equal(tests[num]())
}

describe('Sponge', () => {
  it('00: #initState: Should work fine', async () => {
    await assertTest(COMPARATOR_TEST.InitState)
  })

  it('01: #rotr64: Should work fine', async () => {
    await assertTest(COMPARATOR_TEST.Rotr64)
  })

  it('02: #blake2bG: Should work fine', async () => {
    await assertTest(COMPARATOR_TEST.blake2bG)
  })

  it('03: #roundLyra: Should work fine', async () => {
    await assertTest(COMPARATOR_TEST.roundLyra)
  })

  // it('04: #spongeLyra: Should work fine', async () => {
  //   const cResult = await runTest(COMPARATOR_TEST.spongeLyra)
  //   const cOutput = getValidOutputFromTest(cResult)
  //   const state = initState()
  //   const spongeOutput = getLongsStr(spongeLyra(state))
  //   expect(cOutput).to.be.equal(spongeOutput)
  // })
})
