
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
   console.log( mod.tick() );
   console.log( mod.ROLE_WORKER );
   console.log( (mod.role) ? mod.role.ROLE_WORKER : "" );

   //mod.ccall('main');
}