const log = require("logger");
module.exports = {
    init : function() {
        if ( this._core == undefined ) {
            const bytecode = require('core');

            const wasmModule = new WebAssembly.Module(bytecode);

            const imports = {};

            const memory = new WebAssembly.Memory({ initial: 256 });

            imports.env = {
                __memory_base: 0,
                __table_base: 0,
                memory: memory,
                table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })    
            };

            const wasmInstance = new WebAssembly.Instance(wasmModule, imports);

            const arrayBuffer = memory.buffer;
            const buffer = new Uint8Array(arrayBuffer);
            this._core = wasmInstance.exports;
        }
    }

}