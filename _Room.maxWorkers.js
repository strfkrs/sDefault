Object.defineProperty(Room.prototype, 'maxWorkers', {
    get: function() {
        
        if (!this._maxWorkers) {
            
            if (!this.memory.maxWorkers) {             
                this.memory.maxWorkers = _.sum(this.sources, (s) => s.maxWorkers)
            }
            
            this._maxWorkers = this.memory.maxWorkers;
        }
        
        return this._maxWorkers;
    },
    enumerable: false,
    configurable: true
});