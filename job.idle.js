var l = require("logger");


module.exports = {
    name: "idle",
    getActions: function(creep) {
        return [ACTION_IDLE];
    }
}