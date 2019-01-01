var l = require("logger");


module.exports = {
    name: "refillTowers",
    getActions: function(creep) {
        return [ACTION_HARVEST, ACTION_TRANSFER_TO_TOWERS];
    }
}