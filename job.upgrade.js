module.exports = {
    name: "upgrade",
    getId: function() { return JOB_UPGRADE },
    getActions: function() { return [ACTION_HARVEST, ACTION_UPGRADE] }
}