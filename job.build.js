module.exports = {
    name: "build",
    getId: function() { return JOB_BUILD },
    getActions: function(creep) { return [ACTION_HARVEST, ACTION_BUILD] }
}