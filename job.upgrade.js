var l = require("logger");


module.exports = {
    name: "upgrade",
    getActions: function(creep) {
        return [ACTION_HARVEST, ACTION_UPGRADE];
    }
}