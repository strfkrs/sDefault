Object.defineProperty(Creep.prototype, 'focus', {
    get: function() {
        
        if (!this._focus) {
            
            if (!this.memory.focus) {
                
                this.memory.focus = undefined;
                this._focus = undefined;
            } else {

                this._focus = Game.getObjectById(this.memory.focus);
            }
            
        }
        return this._focus;
    },
    set: function(newValue) {
        if (newValue) {
            this.memory.focus = newValue.id;
            this._focus = newValue;
        } else {
            this.memory.focus = undefined;
            this._focus = undefined;
        }
    },
    enumerable: false,
    configurable: true
});