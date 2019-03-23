// This will return an ArrayBuffer with `addTwo.wasm` binary contents

const core = require("core_api");
const log = require("logger");

log(undefined, "reset");
core.init();

module.exports.loop = function () {
    core.init();
}