Object.defineProperty(Creep.prototype, 'processStatus', {
   get: function() {
       if (this._processStatus == undefined) {
           if (this.memory.processStatus == undefined) {
               this.memory.processStatus = 0;
           }
           this._processStatus = this.memory.processStatus;
       }
       return this._processStatus;
   },
   set: function(v) {
       this.memory.processStatus = v;
       this._processStatus = v;
   },
   enumerable: false,
   configurable: true
});