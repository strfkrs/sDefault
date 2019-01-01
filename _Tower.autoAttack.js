var l = require("logger");
StructureTower.prototype.autoAttack = function() {
    

    let nearest = this.pos.findClosestByRange(FIND_HOSTILE_CREEPS, {filter: function(obj) {return Memory.aggressivePlayers.includes(obj.owner.username)}});
    
    l.debug("tower.autoAttack","nearest: "+nearest);

    if (nearest) {
        this.attack(nearest);
        return true;
    }
    return false;

}