Object.defineProperty(Creep.prototype, 'role', {
   get: function() {
       if (this._role == undefined) {
           if (!this.memory.role == undefined) {
               this.memory.role = ROLE_UNDEFINED;
           }
           this._role = this.memory.role;
       }
       return this._role;
   },
   set: function(v) {
       this.memory.role = v;
       this._role = v;
   },
   enumerable: false,
   configurable: true
});