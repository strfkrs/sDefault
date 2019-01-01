var l = require("logger");


module.exports = {
    name: "build",
    getActions: function(creep) {
        return [ACTION_HARVEST, ACTION_BUILD];
    }
}