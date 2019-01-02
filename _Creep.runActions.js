
const l = require("logger");

const ACTIONPADDING = "                              ";
const JOBPADDING = "                              ";

Creep.prototype.runActions = function () {

    let actions = this.actions;
    
    while (actions.length) {


        l.og("",this,"",
            "JOB: "+JOBS[this.job].name.padding(JOBPADDING,false) +
            " ACTIONS: "+this.actions.map(a => ACTIONS[a].name).join(", ")
        );
        
        const action = ACTIONS[actions[0]];

        if (action.run(this)) {
            l.debug("Creep.runActions","action "+action.name+" -> returned true");
            return true;

        }
        else {
            l.debug("Creep.runActions","action "+action.name+" -> returned false");
            actions.shift();
            this.actions = actions;
            this.focus = undefined;
        }
    }
    return false;
}