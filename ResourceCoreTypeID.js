Object.defineProperty(Resource.prototype, 'coreTypeID', {
    get: function() {
        if (this._coreTypeID == undefined)
        {
            const type = this.id;
            let c = 0;
            for( const t in Game.RESOURCES_ALL )
            {
                  if( Game.RESOURCES_ALL[t] == type )
                  {
                     break;
                  }
                  c++;
            }
            this._coreTypeID = c;
        }
        return this._coreTypeID;
    },
    enumerable: false,
    configurable: true
});