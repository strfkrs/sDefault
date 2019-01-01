
const l = require("logger");
Creep.prototype.runActions = function () {

    let actions = this.actions;

    l.og("",this, "",
        "Job.runActions(): JOB: "+JOBS[this.job].name.padding(JOBPADDING,false) +
        " ACTIONS: "+this.actions.map(a => ACTIONS[a].name).join(", ")
    );

    while (actions.length) {

        l.og("",this, ((gotAssignedActions) ? " assigned > " : ""),
            "JOB: "+JOBS[this.job].name.padding(JOBPADDING,false) +
            " ACTIONS: "+this.actions.map(a => ACTIONS[a].name).join(", ")
        );

        if (ACTIONS[actions[0]].run(this)) {
            l.debug("Creep.runActions","action "+actions[0]+" -> returned true");
            return true;

        }
        else {
            l.debug("Creep.runActions","action "+actions[0]+" -> returned false");
            actions.shift();
            this.actions = actions;
            this.focus = undefined;
        }
    }
    return false;
}