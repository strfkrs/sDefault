var l = require("logger");

Object.defineProperty(Creep.prototype, 'home', {
    get: function() {
        if (!this._home) {
            if (!this.memory.home) {
                l.og("",this, "-->", "setting home");
                this.memory.home = this.room.name;
            }

            this._home = Game.rooms[this.memory.home];
        }
        return this._home;
    },
    set: function(v) {
        this.memory.home = v.name;
        this._home = v;
    },
    enumerable: false,
    configurable: true
});