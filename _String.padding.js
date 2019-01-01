String.prototype.padding = function(pad, left=true) {
    if (left) {
        return (pad + this).slice( -pad.length);
    } else {
        return (this + pad).slice( 0,pad.length);
    }
}