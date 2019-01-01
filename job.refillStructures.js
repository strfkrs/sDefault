var l = require("logger");


module.exports = {
    name: "refillStructures",
    getActions: function(creep) {
        return [ACTION_HARVEST, ACTION_TRANSFER_TO_STRUCTURES];
    }
}