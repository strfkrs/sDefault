Flag.prototype.surrounds = function(creep) {
    let pCreep = creep.pos;
    let pFlag = this.pos;

    return (pCreep.x >= pFlag.x -1 && pCreep.x <= pFlag.x +1 && pCreep.y >= pFlag.y -1 && pCreep.y <= pFlag.y +1)
}