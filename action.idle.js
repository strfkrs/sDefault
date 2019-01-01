var l = require("logger");
module.exports = {
    name: "idle",
    _focusFlag(creep) {
        creep.focus = undefined;
        let flag = _.filter(creep.room.flags, (f) => f.name.includes("Idle") && !f.surrounds(creep))[0];
        if (flag) {
            l.debug("aIdle","focussing on "+flag);
            creep.focus = flag;
        }
    },
    run: function(creep) {

        if (!creep.focus) {
            this._focusFlag(creep);
        }
        l.debug("aIdle","Creep focus "+creep.focus);

        if (creep.focus) {
            creep.moveTo(creep.focus, {visualizePathStyle: {stroke: '#8888ff'}});
            if (creep.focus.surrounds(creep)) {
                return false;
            }
            return true;
        }
        return false;
    }
}