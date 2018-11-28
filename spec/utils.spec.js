'use strict'

const path = require('path')
const mainPath = require.main.filename.includes('node_modules') ? path.join(path.dirname(require.main.filename), '../../..') : path.dirname(require.main.filename)
const { exec } = require('child_process')

/**
 * @typedef {Object} ExecCmdReturn
 * @property {String} stout raw output from stdout
 * @property {String} stderr raw output from stderr
 */

/**
 * Exec command and returns a promise with the stdout, stderr.
 * @param {String} cmd
 * @returns {Promise<ExecCmdReturn>}
 */
const execCmd = async (cmd) => {
  return new Promise((resolve, reject) => {
    exec(cmd, (error, stdout, stderr) => {
      if (error) {
        reject(error)
      }
      // console.log(stdout)
      resolve({ stdout, stderr })
    })
  })
}

/**
 * Compiles comparator.c file
 */
const compileC = async () => {
  return execCmd(`gcc -Wall -o ${mainPath}/lyra2c/comparator ${mainPath}/lyra2c/comparator.c`)
}

/**
 * Returns test result from C code
 * @param {Number} testNum
 */
const runTest = async (testNum) => {
  await compileC()
  return execCmd(`${mainPath}/lyra2c/comparator ${testNum}`)
}

/**
 * Pega a string comparável para o teste
 * @param {ExecCmdReturn} cmdReturn
 * @returns {String}
 */
const getValidOutputFromTest = (cmdReturn) => {
  return cmdReturn.stdout.split('\n').slice(2, -3).join('\n')
}

module.exports = {
  runTest,
  getValidOutputFromTest
}
