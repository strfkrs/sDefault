const Loggable = require("Loggable");

module.exports =
class extends Loggable
{
   constructor()
   {
      super("Job");
      self.log("created");
   }

   static get IDLE() { return 1; }
}