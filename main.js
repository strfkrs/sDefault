// This will return an ArrayBuffer with `addTwo.wasm` binary contents
const bytecode = require('core');

const wasmModule = new WebAssembly.Module(bytecode);

const imports = {};

const memory = new WebAssembly.Memory({ initial: 256 });

// Some predefined environment for Emscripten. See here:
// https://github.com/WebAssembly/tool-conventions/blob/master/DynamicLinking.md
imports.env = {
    __memory_base: 0,
    __table_base: 0,
    memory: memory,
    table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })    
};

const wasmInstance = new WebAssembly.Instance(wasmModule, imports);

const arrayBuffer = memory.buffer;
const buffer = new Uint8Array(arrayBuffer);
const core = wasmInstance.exports;
let c = 0;


      console.log("reset");

module.exports.loop = function () {
    
      core._set(c++);
      console.log(core._get(c), Game.cpu.getUsed());
}