const l = require("logger");
const utils = require("utils");

const ACTIONPADDING = "                              ";
const JOBPADDING = "                              ";


module.exports = {
    name: "worker",
    getId: function() { return ROLE_WORKER },
    _needsRefillStructuresJob: function(room) {
        return room.energyAvailable < room.energyCapacityAvailable;
    },
    _needsBuildJob: function(room) {
        const targets = room.find(FIND_MY_CONSTRUCTION_SITES);
        return targets.length > 0;
    },
    _getJob: function(creep) {

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

            if (this._needsRefillStructuresJob(room)) {

                // refill structures

                necessary.unshift(JOB_REFILL_STRUCTURES);
            }

            if (this._needsBuildJob(room)) {

                // build

                necessary.unshift(JOB_BUILD);
            }
        }

        return utils.sortJobsByWorkers(room.creeps, necessary)[0];
    },
    run: function(creep) {
        if (!creep.spawning) {

            /*
            *      get job
            */
            if (creep.job == JOB_UNDEFINED) {
                creep.job = this._getJob(creep);
                actions = JOBS[job].getActions(creep);
                gotAssignedActions = true;
            }

            /*
            *      run actions
            */

            if (!creep.runActions()) {
                creep.job = JOB_UNDEFINED;
            }
        }
    }
}