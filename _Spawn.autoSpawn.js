const l = require("logger");
const utils = require("utils");

var isPossibleRole = function(role, room) {
    let ret = false;

    switch (role) {
        default: ret = room.energyAvailable >= getSpawnData(role).minEnergy;
    }


    l.debug("Spawn.autoSpawn","role "+ROLES[role].name+" isPossible: "+ret);

    return ret;
}

var isNecessaryRole = function(role, room) {

    let ret = false;

    switch (role) {
        case ROLE_WORKER:
            l.debug("Spawn.autoSpawn","role "+ROLES[role].name+" "+room.workers.length+" < "+room.maxWorkers);
            ret = room.workers.length < room.maxWorkers;
        break;
    }

    l.debug("Spawn.autoSpawn","role "+ROLES[role].name+" isNecessary: "+ret);

    return ret;
}

var getPossibleRoles = function(room) {
    let possibleRoles = _.filter(
        [ ROLE_WORKER ],
        (role) => isNecessaryRole(role, room) && isPossibleRole(role, room));
    
    return possibleRoles;
}

var getSpawnData = function(role) {

    switch(role) {
        case ROLE_WORKER: return {bodyParts:[[MOVE,CARRY,WORK]], minEnergy: 200, maxEnergy: 800, data:{memory:{role:role}}};
    }
}
Spawn.prototype.autoSpawn = function() {
    if (!this.spawning) {
        let actionMsg = "";

        const room = this.room;
        const possibleRoles = getPossibleRoles(room);

        if (possibleRoles.length) {
    
            let msg = "autoSpawn: possible roles: "+possibleRoles.length;
            if (possibleRoles.length) {
                let msg2 = "";
    
                const role = possibleRoles[0];
                const spawnData = getSpawnData(role);
                const name = utils.createCreepName(ROLES[role].name);
                const data = spawnData.data;
    

                const energy = (room.energyAvailable > spawnData.maxEnergy) ? spawnData.maxEnergy : room.energyAvailable;
                const bodyParts = spawnData.bodyParts;

                msg2 += " - creating body: energy: "+energy+" bodyParts: "+bodyParts;

                const body = utils.createCreepBody(
                    energy,
                    bodyParts
                );
                
                const status = this.spawnCreep( body, name, data );


                if ( status == OK )
                {
                    const creep = Game.creeps[name];
                    msg2 += " -> spawned - setting home: "+creep.home.name;
                    actionMsg = "-->";
                    creep.room.addCreep(creep);
                    
                } else {
                    msg2 += " -> status "+status;

                    msg2 += " (args: "+body+", "+name+",  "+data+")"+status;
                }
                l.og("",this,actionMsg,msg2);
            }
            l.og("",this,actionMsg,msg);
        }
    }
}
