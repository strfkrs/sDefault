module.exports = {
    name: "idle",
    getId: function() { return JOB_IDLE },
    getActions: function(creep) { return [ACTION_IDLE] }
}