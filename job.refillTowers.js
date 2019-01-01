module.exports = {
    name: "refillTowers",
    getId: function() { return JOB_REFILL_TOWERS },
    getActions: function() { return [ACTION_HARVEST, ACTION_TRANSFER_TO_TOWERS] }
}