Object.defineProperty(Room.prototype, 'structures', {
    get: function() {
        
        if (!this._structures) {
            if (!this.memory.structures) {
                
                this.towers = undefined;

                this.memory.structures = this.find(FIND_MY_STRUCTURES)
                                        .map(structure => structure.id);
            }
            
            this._structures = this.memory.structures.map(id => Game.getObjectById(id));
        }
        
        return this._structures;
    },
    set: function(newValue) {
        if (newValue == undefined) {
            this.memory.structures = undefined;
            this._structures = undefined;
        } else {
            this.memory.structures = newValue.map(structure => structure.id);
            this._structures = newValue;
        }
    },
    enumerable: false,
    configurable: true
});