if( StructureSpawn.prototype._spawnCreepOrig == undefined )
{
   StructureSpawn.prototype._spawnCreepOrig = StructureSpawn.prototype.spawnCreep;

   StructureSpawn.prototype.spawnCreep = function( a, b, c )
   {
      console.log(this.name, JSON.stringify(a),JSON.stringify(b),JSON.stringify(c));
      return this._spawnCreepOrig( a.split(";"), b, { memory: { role: c }} );
   }
}