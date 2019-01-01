module.exports = {
    name: "refillStructures",
    getId: function() { return JOB_REFILL_STRUCTURES },
    getActions: function(creep) { return [ACTION_HARVEST, ACTION_TRANSFER_TO_STRUCTURES] }
}