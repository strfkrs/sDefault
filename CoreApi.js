const Loggable = require("Loggable");
module.exports =
class extends Loggable
{
	constructor(coreName)
	{
      super( "coreApi" )
	   if( this._core == undefined )
      {
	      const bytecode = require('core');

	      const wasmModule = new WebAssembly.Module(bytecode);

	      const imports = {};

	      //const memory = new WebAssembly.Memory({ initial: 1024 });

	      imports.env = {
	            __memory_base: 0,
	            __table_base: 0,
	            memory: new WebAssembly.Memory({ initial: 1024 }),
	            table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
	         };

	      const wasmInstance = new WebAssembly.Instance(wasmModule, imports);

	      //const arrayBuffer = memory.buffer;
	      //const buffer = new Uint8Array(arrayBuffer);

         this._core = wasmInstance.exports;

         this.log( "created" );
      }
   }
   init()
   {
      return this._core._init();
   }
   initRoom( idx )
   {
      return this._core._initRoom( idx, numCreeps, numSpawns );
   }
   initCreep( idx )
   {
      return this._core._initCreep( idx, numCreeps, numSpawns );
   }
}