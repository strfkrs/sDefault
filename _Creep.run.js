var l = require("logger");

const ACTIONPADDING = "                              ";
const JOBPADDING = "                              ";


Creep.prototype.run = function () {

    if (!this.spawning) {

        let gotAssignedActions = false;
    
        /*
         *      get jobs from role
         */
        if (this.job == JOB_UNDEFINED) {
            this.job = ROLES[this.role].getJob(this);
        }
    
        /*
         *      get actions from job
         */
        if (!this.actions.length) {
            this.actions = JOBS[this.job].getActions(this);
            gotAssignedActions = true;
        }
    
    
    
        /*
         *      run action
         */
        let actions = this.actions;
    
        //let actionMsg = this.actions.map(a => ACTIONS[a].name.padding(ACTIONPADDING,false)).join(", ");
        let actionMsg = this.actions.map(a => ACTIONS[a].name).join(", ")
    
        l.og("",this, ((gotAssignedActions) ? " assigned > " : ""),
            "JOB: "+JOBS[this.job].name.padding(JOBPADDING,false) +
            " ACTIONS: "+actionMsg );
    
    
        while (actions.length) {
        
            if (ACTIONS[actions[0]].run(this)) {
                l.debug("Creep.run","action "+actions[0]+" -> returned true");
                break;
            }
            else {
                l.debug("Creep.run","action "+actions[0]+" -> returned false");
                actions.shift();
                this.actions = actions;
                this.focus = undefined;
            }
        }
    
        if (!actions.length) {
            this.job = JOB_UNDEFINED;
            this.focus = undefined;
        }
    }
}