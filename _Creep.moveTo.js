if (!Creep.prototype._moveTo) {
    Creep.prototype._moveTo = Creep.prototype.moveTo;

    Creep.prototype.moveTo = function(arg1, arg2, arg3) {

        if (CONTROLS.allowWorkerAutoConstruct()) {
            if (arg1 instanceof RoomObject) {
                const found = this.pos.lookFor(LOOK_STRUCTURES);
                if(!found.length) {
                    this.pos.createConstructionSite(STRUCTURE_ROAD);
                }
            }
        }
        return this._moveTo(arg1, arg2, arg3);
    }
}