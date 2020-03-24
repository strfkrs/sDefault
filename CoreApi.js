
class CoreApi
{
	constructor(coreName)
	{
	   if( this._core == undefined )
      {
	      const bytecode = require('core');

	      const wasmModule = new WebAssembly.Module(bytecode);

	      const imports = {};

	      const memory = new WebAssembly.Memory({ initial: 512 });
         this.heap = new Int8Array(memory.buffer);

	      imports.env = {
	            __memory_base: 0,
               __table_base: 0,
               __set_err_no: console.log,
	            memory: memory,
	            table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
	         };

	      const wasmInstance = new WebAssembly.Instance(wasmModule, imports);

	      //const arrayBuffer = memory.buffer;
	      //const buffer = new Uint8Array(arrayBuffer);

         this._core = wasmInstance.exports;

         console.log( `core created memory size ${ this.heap.length }` );
      }
   }

   init()
   {
      return this._core.ccall("init");
   }

}
module.exports = CoreApi;