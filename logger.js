
const info = function(msg) {
    console.log(msg);
}

module.exports = function( msg, object = undefined, verbosity = 0 ) {
    switch (verbosity) {
        case 0: info(msg); break;
        default: info(msg);
    }
}