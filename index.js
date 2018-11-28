'use strict'

const { tests } = require('./spec/comparator.spec')
let testNum = 0
if (process.argv.length > 2) {
  testNum = process.argv[2].trim()
}

(async () => {
  console.log(tests[testNum]())
})()
