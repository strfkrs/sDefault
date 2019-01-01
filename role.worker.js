var l = require("logger");
var utils = require("utils");
module.exports = {
    name: "worker",
    getId: function() { return ROLE_WORKER },
    getJob: function(creep) {

        let necessary = [];
        let room = creep.home;
        
        if ( room.creeps.length < 3 ) {

            /*
             *      early jobs
             */

            necessary = [ JOB_REFILL_STRUCTURES, JOB_REFILL_TOWERS ];

        } else {

            /*
             *      normal jobs
             */

            necessary = [ JOB_REFILL_STRUCTURES, JOB_REFILL_TOWERS, JOB_UPGRADE ];

            if (this._needBuildJob(room)) {
                
                necessary.push(JOB_BUILD);
            }
        }

        return utils.getLeastUsedJob(room.creeps, necessary);
    },
    _needBuildJob: function(room) {
        var targets = room.find(FIND_MY_CONSTRUCTION_SITES);
        return (_.filter(room.creeps, (creep) => /*creep.room == room && creep.job == JOB_BUILD).length < 2 &&*/ targets.length));
    }
}