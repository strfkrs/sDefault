Object.defineProperty(Creep.prototype, 'actions', {
    get: function() {
        if (!this._actions) {
            if (!this.memory.actions) {
                this.memory.actions = [];
            }
            this._actions = this.memory.actions;
        }
        return this._actions;
    },
    set: function(v) {
        this.memory.actions = v;
        this._actions = v;
    },
    enumerable: false,
    configurable: true
});