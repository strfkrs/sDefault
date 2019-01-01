Object.defineProperty(Room.prototype, 'towers', {
    get: function() {
        
        if (!this._towers) {
            
            if (!this.memory.towers) {             
                this.memory.towers = 
                    _.filter(this.structures, (f) => f.structureType == STRUCTURE_TOWER)
                    .map(s => s.id);
            }
            
            this._towers = this.memory.towers.map(id => Game.getObjectById(id));
        }
        
        return this._towers;
    },
    set: function(newValue) {
        if (newValue == undefined) {

            this.memory.towers = undefined;
            this._towers = undefined;
        } else {
            this.memory.towers = newValue.map(t => t.id);
            this._towers = newValue;

        }
    },
    enumerable: false,
    configurable: true
});