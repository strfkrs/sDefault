var l = require("logger");
var freeNeighborSpace = function(source) {
    let sPos = source.pos;
    let tests = [[-1,0],[-1,-1],[-1,1],[1,0],[1,-1],[1,1],[0,-1],[0,1]];
    let amount = 0;
    for (var t in tests) {
        let test = tests[t];
        let testPos = new RoomPosition(sPos.x+test[0],sPos.y+test[1],sPos.roomName);

        let objects = testPos.look();

        for (var o in objects) {
            let object = objects[o];
            if (object.type == "terrain" && object.terrain == "plain") {
                amount++;
            }
        }
    }
    return amount;
}

Object.defineProperty(Source.prototype, 'maxWorkers', {
    get: function() {
        if (this._maxWorkers == undefined) {
            
            if (this.memory.maxWorkers == undefined) {
                this.memory.maxWorkers = freeNeighborSpace(this) * 2;
            }
            
            this._maxWorkers = this.memory.maxWorkers;
        }
        return this._maxWorkers;
    },
    enumerable: false,
    configurable: true
});