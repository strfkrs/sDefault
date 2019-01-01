Object.defineProperty(Room.prototype, 'flags', {
    get: function() {
        
        if (!this._flags) {
            
            if (!this.memory.flags) {
                
                this.memory.flags = this.find(FIND_FLAGS).map(f => f.name);
            }
            
            this._flags = this.memory.flags.map(f => Game.flags[f]);
        }
        
        return this._flags;
    },
    set: function(newValue) {
        
        this.memory.flags = newValue.map(f => f.name);
        this._flags = newValue;
    },
    enumerable: false,
    configurable: true
});