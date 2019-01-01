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
        
        ret = true;
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
        default: return {bodyParts:[[MOVE,CARRY,WORK]], minEnergy: 200, maxEnergy: 800};
    }
}

var getRoleData = function (role) {
    return {memory:{role:role}}
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
                const name = utils.createCreepName(ROLES[role].name);
                const data = getRoleData(role);
    

                const energy = (room.energyAvailable > getSpawnData(role).maxEnergy) ? getSpawnData(role).maxEnergy : room.energyAvailable;
                const bodyParts = getSpawnData(role).bodyParts;

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
                    creep.room.creepsAdd(creep);
                    
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
