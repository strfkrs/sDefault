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

                necessary.push(JOB_REFILL_STRUCTURES);
            }

            if (this._needsBuildJob(room)) {
                
                necessary.push(JOB_BUILD);
            }
        }

        return utils.getLeastUsedJob(room.creeps, necessary);
    },
    run: function(creep) {
        if (!creep.spawning) {

            let gotAssignedActions = false;
        
            /*
            *      get jobs
            */
            if (creep.job == JOB_UNDEFINED) {
                creep.job = this._getJob(creep);
            }
        
            /*
            *      get actions from job
            */
            if (!creep.actions.length) {
                creep.actions = JOBS[creep.job].getActions(creep);
                gotAssignedActions = true;
            }
        
            /*
            *      run action
            */
            let actions = creep.actions;
        
            //let actionMsg = creep.actions.map(a => ACTIONS[a].name.padding(ACTIONPADDING,false)).join(", ");
            let actionMsg = creep.actions.map(a => ACTIONS[a].name).join(", ")
        
            l.og("",creep, ((gotAssignedActions) ? " assigned > " : ""),
                "JOB: "+JOBS[creep.job].name.padding(JOBPADDING,false) +
                " ACTIONS: "+actionMsg );
        
        
            while (actions.length) {
            
                if (ACTIONS[actions[0]].run(creep)) {
                    l.debug("Creep.run","action "+actions[0]+" -> returned true");
                    break;
                }
                else {
                    l.debug("Creep.run","action "+actions[0]+" -> returned false");
                    actions.shift();
                    creep.actions = actions;
                    creep.focus = undefined;
                }
            }
        
            if (!actions.length) {
                creep.job = JOB_UNDEFINED;
                creep.focus = undefined;
            }
        }
    }
}