Object.defineProperty(Room.prototype, 'sources', {
    get: function() {
        
        if (!this._sources) {
            
            if (!this.memory.sources) {
                
                this.memory.sources = this.find(FIND_SOURCES).map(source => source.id);
            }
            
            this._sources = this.memory.sources.map(id => Game.getObjectById(id));
        }
        
        return this._sources;
    },
    set: function(newValue) {
        
        this.memory.sources = newValue.map(source => source.id);
        this._sources = newValue;
    },
    enumerable: false,
    configurable: true
});