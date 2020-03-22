class Order
{
   constructor()
   {

   }
   static parseCreateFromCoreBytes( length )
   {
      return new Order();
   }
}

module.exports = Order;