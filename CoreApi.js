const Loggable = require("Loggable");
const Order = require("Order");

class CoreApi extends Loggable
{
	constructor(coreName)
	{
      super( "coreApi" )
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
	            memory: memory,
	            table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
	         };

	      const wasmInstance = new WebAssembly.Instance(wasmModule, imports);

	      //const arrayBuffer = memory.buffer;
	      //const buffer = new Uint8Array(arrayBuffer);

         this._core = wasmInstance.exports;

         this.log( `created memory size ${ this.heap.length }` );
      }
   }
   _logParseStatusCode( answer, msg )
   {
      switch ( answer )
      {
         case 0: this.log( msg, 1 ); break;
         default: this.log( msg, 0 ); break;
      }
      return answer;
   }
   init()
   {
      return this._logParseStatusCode( this._core._init(),  `init` );
   }
   isInitialized()
   {
      return this.log( `isInitialized`, this._core._is_initialized() );
   }
   initRoom( idx )
   {
      return this._logParseStatusCode( this._core._init_room( idx ), `initRoom idx: ${ idx } ` );
   }
   initCreep( idx, roomIdx, role, job )
   {
      return this._logParseStatusCode( this._core._init_creep( idx, roomIdx, role, job ),
                                       `init Creep idx: ${idx} roomIdx: ${roomIdx} role: ${role} job: ${job}` );
   }
   initSpawn( idx, roomIdx, isSpawning )
   {
      return this._logParseStatusCode( this._core._init_creep( idx, roomIdx, isSpawning ),
                                       `init Spawn idx: ${idx} roomIdx: ${roomIdx} isSpawning: ${isSpawning}`);
   }
   createOrders()
   {
      const numCreated = this._core._create_orders();
      this.log(`created orders: ${numCreated}`, true);
      return numCreated;
   }
   getWaitingOrdersCount()
   {
      const numWaiting = this._core._get_waiting_orders_count();
      this.log(`waiting orders: ${numWaiting}`, true);
      return numWaiting;
   }
   getNextOrderByteIdx()
   {
      const idx = this._core._get_next_order_byte_idx();
      this.log( `getting order index: ${idx}`, idx > 0 );
      return idx;
   }
}
module.exports = CoreApi;