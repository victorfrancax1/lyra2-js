const { expect } = require('chai')
const { getValidOutputFromTest, runTest } = require('./utils.spec')
const { tests, COMPARATOR_TEST } = require('./comparator.spec')

const assertTest = async (num) => {
  const cResult = await runTest(num)
  const cOutput = getValidOutputFromTest(cResult)
  expect(cOutput).to.be.equal(tests[num]())
}

const getTests = () => {
  const tests = []
  let i = 0
  for (const key in COMPARATOR_TEST) {
    const padded = i < 10 ? '0' + i : i
    tests.push({
      name: `${padded}: #${key}: Should work fine`,
      func: async () => { await assertTest(COMPARATOR_TEST[key]) }
    })
    i++
  }
  return tests
}

describe('Sponge', () => {
  getTests().map(t => {
    it(t.name, t.func)
  })
})
