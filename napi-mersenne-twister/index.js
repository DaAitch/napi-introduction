const fs = require('fs');
const os = require('os');
const si = require('systeminformation');
const {MersenneTwisterChatty: MersenneTwisterChattyNapi, MersenneTwister: MersenneTwisterNapi} = require('bindings')('mersenne_twister');
const {MersenneTwister: MersenneTwisterJS} = require('./src/js/mersenne-twister');

const ITERATIONS = [1000, 10000, 100000, 1000000, 10000000, 100000000];
const REPETITIONS = 10;

// arrays of duration millis
const measurements = {};

const hrtProfile = work => {
  const startNanos = process.hrtime.bigint();
  work();
  const endNanos = process.hrtime.bigint();

  const millisTimesHundred = (endNanos - startNanos) / 10000n;
  return Number(millisTimesHundred) / 100;
};

const addMeasurement = (iterations, name, millis) => {
  if (!(name in measurements)) {
    measurements[name] = {};
  }

  if (!(iterations in measurements[name])) {
    measurements[name][iterations] = [];
  }

  measurements[name][iterations].push(millis);
};

const run = iterations => {
  // MersenneTwisterChattyNapi
  {
    const millis = hrtProfile(() => {
      const mt = new MersenneTwisterChattyNapi();
      for (let i = 0; i < iterations; i++) {
        mt.next();
      }
    });

    addMeasurement(iterations, 'napiChatty', millis);
  }

  // MersenneTwisterJS
  {
    const millis = hrtProfile(() => {
      const mt = new MersenneTwisterJS();
      for (let i = 0; i < iterations; i++) {
        mt.next();
      }
    });

    addMeasurement(iterations, 'js', millis);
  }

  // MersenneTwisterNapi
  {
    const millis = hrtProfile(() => {
      const mt = new MersenneTwisterNapi();
      const values = new Uint32Array(iterations);
      mt.load(values);
    });

    addMeasurement(iterations, 'napiBuffered', millis);
  }
};

ITERATIONS.forEach(iterations => {
  for (let r = 1; r <= REPETITIONS; r++) {
    console.log(`${iterations} iterations ${r}/${REPETITIONS}`);
    run(iterations);
  }
});

(async () => {
  const cpu = await si.cpu();

  fs.writeFileSync(
    __dirname + `/measurements/measurement-${new Date().toISOString()}.json`,
    JSON.stringify({
      environment: `${process.release.name}@${process.version}  |  ${cpu.manufacturer} ${cpu.brand} ${cpu.speed}GHz  |  ${os.arch} ${os.platform()} ${os.release}`,
      measurements
    }, undefined, '  ')
  );
})();

