Object.defineProperty(Room.prototype, 'creeps', {
   get: function() {
       if (this._creeps == undefined) {
           
           if (this.memory.creepNames == undefined) {
               this.memory.creepNames = this.find( FIND_CREEPS ).map( f => f.name );
           }
           this._creeps = this.memory.creepNames.map(name => Game.creeps[name]);
       }
       return this._creeps;
   },
   set: function(newValue)
   {
       
       this.memory.creepNames = newValue.map(f => f.name);
       this._creeps = newValue;
   },
   enumerable: false,
   configurable: true
});

Object.defineProperty(Room.prototype, 'spawns', {
   get: function() {
      if ( this._spawns == undefined ) {

         /*if ( this.memory.spawnIds == undefined ) {
            this.memory.spawnIds = this.find( FIND_MY_SPAWNS ).map( s => s.id );
         }

         this._spawns = this.memory.spawnIds.map( id => Game.getObjectById[id] );*/
         this._spawns = this.find( FIND_MY_SPAWNS );
      }
      return this._spawns;
   },
   set: function( newValue )
   {
      //this.memory.spawnIds = newValue.map( s => s.id );
      this._spawns = newValue;
   },
   enumerable: false,
   configurable: true
});