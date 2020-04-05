Object.defineProperty(Creep.prototype, 'action', {
   get: function() {
       if (this._action == undefined) {
           if (this.memory.action == undefined) {
               this.memory.action = 0;
           }
           this._action = this.memory.action;
       }
       return this._action;
   },
   set: function(v) {
       this.memory.action = v;
       this._action = v;
   },
   enumerable: false,
   configurable: true
});