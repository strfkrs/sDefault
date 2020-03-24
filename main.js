
const Module = require('core-mod');

let coreIsInit = 0;

const opts = {
  ENVIRONMENT: 'SHELL', // This works, NODE does not
  print: function(text){ console.log(`[STDOUT] ${text}`); },
  printErr: function(text){ console.log(`[STDERR] ${text}`); },
  onAbort: function(){ console.log(`[ABORT] WASM Aborted!`); },
  onRuntimeInitialized: function(){ coreIsInit = 1; },
  noInitialRun: true,
  noExitRuntime: true,
  wasmBinary: require('core')
};

const mod = Module(opts);


module.exports.loop = function () {
   if ( !coreIsInit ) { return; }

   console.log( mod.ccall("init") );
   console.log( mod.ccall("main") );
   //mod.ccall('main');
}