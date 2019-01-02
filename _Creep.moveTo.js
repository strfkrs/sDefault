if (!Creep.prototype._moveTo) {
    Creep.prototype._moveTo = Creep.prototype.moveTo;

    Creep.prototype.moveTo = function(arg1, arg2, arg3) {

        if (this.room.autoConstruct) {
            if (arg1 instanceof RoomObject) {
                const found = this.pos.lookFor(LOOK_STRUCTURES);
                if(!found.length) {
                    this.pos.createConstructionSite(STRUCTURE_ROAD);
                }
            }
        }

        //save old pos
        const oldPos = this.pos;

        //move
        const status = this._moveTo(arg1, arg2, arg3);

        if (status == OK) {
            const newPos = this.pos;

            if (oldPos.room != newPos.room) {

                // if moved into another room
                // un/register creep in room.creeps
                oldPos.room.creepsRemoveByName(this.name, this.role);
                newPos.room.creepsAdd(this);
            }
        }

        return status;
    }
}