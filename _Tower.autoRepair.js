StructureTower.prototype.autoRepair = function() {
    if (this.energy >= this.energyCapacity * 0.9) {

        const targets = this.room.find(FIND_STRUCTURES, {
            filter: object => object.hits < object.hitsMax * 0.8
        });
        
        targets.sort((a,b) => a.hits - b.hits);
    
        let nearest = targets[0];
    
        if (nearest) {
            this.repair(nearest);
            return true;
        }
        return false;
    }

}