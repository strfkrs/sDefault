
if (!StructureTower.prototype._attack) {
    StructureTower.prototype._attack = StructureTower.prototype.attack;
    StructureTower.prototype.attack = function() {
    

        let nearest = this.pos.findClosestByRange(FIND_HOSTILE_CREEPS, {filter: function(obj) {return Memory.aggressivePlayers.includes(obj.owner.username)}});
    
        if (nearest) {
            this._attack(nearest);
            return true;
        }
        return false;
    
    }
}