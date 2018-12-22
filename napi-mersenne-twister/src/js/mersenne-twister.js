const MersenneTwisterJS = require('mersenne-twister');
const DEFAULT_SEED = 5489;

class MersenneTwister {
  constructor() {
    this._mt = new MersenneTwisterJS(DEFAULT_SEED);
  }

  next() {
    return this._mt.random_int();
  }
}

module.exports = {
  MersenneTwister
};