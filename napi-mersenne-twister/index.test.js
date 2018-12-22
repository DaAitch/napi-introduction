const {MersenneTwisterChatty: MersenneTwisterChattyNapi, MersenneTwister: MersenneTwisterNapi} = require('bindings')('mersenne_twister');
const {MersenneTwister: MersenneTwisterJS} = require('./src/js/mersenne-twister');

const assert = require('assert');

// for default seed 5489
const FIRST_VALUES = [
  3499211612,
   581869302,
  3890346734,
  3586334585,
   545404204,
  4161255391,
  3922919429,
   949333985,
  2715962298,
  1323567403
];

const mtcnapi = new MersenneTwisterChattyNapi();
const mtjs = new MersenneTwisterJS();
const mtnapi = new MersenneTwisterNapi();


// test chatty-NAPI and JS
for (const value of FIRST_VALUES) {
  assert.strictEqual(mtcnapi.next(), value);
  assert.strictEqual(mtjs.next(), value);
}

// test buffered-NAPI
const buf = new Uint32Array(FIRST_VALUES.length);
mtnapi.load(buf);
assert.deepEqual(buf, FIRST_VALUES);

console.log(`First ${FIRST_VALUES.length} values tested.`);