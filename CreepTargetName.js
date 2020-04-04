Object.defineProperty(Creep.prototype, 'targetName', {
   get: function() {
       if (this._targetName == undefined) {
           if (!this.memory.targetName == undefined) {
               this.memory.targetName = "";
           }
           this._targetName = this.memory.targetName;
       }
       return this._targetName;
   },
   set: function(v) {
       this.memory.targetName = v;
       this._targetName = v;
   },
   enumerable: false,
   configurable: true
});