
const Module = require('core-mod');
require("CreepRole");
require("CreepTargetName");
require("ResourceCoreTypeID");
require("StructureCoreTypeID");
require("SpawnCreep");

let coreIsInit = 0;

const opts = {
  ENVIRONMENT: 'SHELL', // This works, NODE does not
  print: console.log,//function(txt){ console.log(`${Game.cpu.getUsed()} ${txt}`); },
  printErr: function(text){ console.log(` [STDERR] ${text}`); },
  onAbort: function(){ console.log(`[ABORT] WASM Aborted!`); },
  onRuntimeInitialized: function(){ coreIsInit = 1; },
  noInitialRun: true,
  noExitRuntime: true,
  wasmBinary: require('core')
};

const mod = Module(opts);

module.exports.loop = function () {
   if ( !coreIsInit ) { return; }
   mod.loop();
}