class Loggable
{
   constructor( moduleName )
   {
      this._moduleName = moduleName;
      Loggable.enabled = ( Loggable.enabled ) ? Loggable.enabled : 1;
   }
   log( msg )
   {
      if ( Loggable.enabled )
      {
         console.log(`${msg} ${ (msg.length < Loggable.messageMinLength) ? " ".repeat( Loggable.messageMinLength - msg.length ) : "" }`+
                     `[ ${ Game.cpu.getUsed().toFixed(2) } ]`+
                     `[ ${this._moduleName} ]`
                     );
      }
   }
   static log( msg )
   {
      console.log( msg );
   }
   static get enabled()
   {
      return Loggable._enabled;
   }
   static set enabled( value )
   {
      Loggable._enabled = value;
   }
   static get messageMinLength()
   {
      Loggable._messageMinLength = ( Loggable._messageMinLength ) ? Loggable._messageMinLength : 50;
      return Loggable._messageMinLength;
   }
   static set messageMinLength( value )
   {
      Loggable._messageMinLength = value;
   }
}




module.exports = Loggable;
