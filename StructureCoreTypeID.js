
const tmap = {
   "spawn":0,
   "extension":1,
   "road":2,
   "constructedWall":3,
   "rampart":4,
   "keeperLair":5,
   "portal":6,
   "controller":7,
   "link":8,
   "storage":9,
   "tower":10,
   "observer":11,
   "powerBank":12,
   "powerSpawn":13,
   "extractor":14,
   "lab":15,
   "terminal":16,
   "container":17,
   "nuker":18,
   "factory":19,
   "invaderCore":20
};
Object.defineProperty(Structure.prototype, 'coreTypeID', {
    get: function() {
        if (this._coreTypeID == undefined)
        {
            this._coreTypeID = tmap[ this.structureType ];
        }
        return this._coreTypeID;
    },
    enumerable: false,
    configurable: true
});