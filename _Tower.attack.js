var l = require("logger");
if (!StructureTower.prototype._attack) {
    StructureTower.prototype._attack = StructureTower.prototype.attack;
    StructureTower.prototype.attack = function() {
    

        let nearest = this.pos.findClosestByRange(FIND_HOSTILE_CREEPS, {filter: function(obj) {return Memory.aggressivePlayers.includes(obj.owner.username)}});

        if (nearest) {
            let status = this._attack(nearest);

            if (status == OK) {
                l.og("",{name:this.id},"attacking",nearest.name);
                return true;
            } else {
                l.og("",{name:this.id},"attacking","returned error status: "+status);
            }
        } else {
            l.debug("Tower.attack: no target.");
        }
        return false;
    
    }
}