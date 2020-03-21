const Job = require("Job");

Object.defineProperty(Creep.prototype, 'job', {
   get: function() {
      if ( this._job == undefined )
      {
         if ( this.memory.job == undefined )
         {
            this._job = Job.IDLE;
            this.memory.job = this._job;
         }
         else
         {
            this._job = this.memory.job;
         }
      }
      return this._job;
   },
   set: function( value )
   {
      if( this.job != value )
      {
         this._job = value;
         this.memory.job = this._job;
      }
   },
   enumerable: false,
   configurable: true
});