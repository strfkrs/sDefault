Object.defineProperty(Room.prototype, 'autoConstruct', {
    get: function() {
        
        if (!this._autoConstruct) {
            
            if (!this.memory.autoConstruct) {             
                this.memory.autoConstruct = false;
            }
            
            this._autoConstruct = this.memory.autoConstruct;
        }
        
        return this._autoConstruct;
    },
    set: function(newValue) {
        
        this.memory.autoConstruct = !(!newValue);
        this._autoConstruct = !(!newValue);
    },
    enumerable: false,
    configurable: true
});