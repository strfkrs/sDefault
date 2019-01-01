const l = require("logger");
const utils = require("utils");

var possibleRole = function(role, room) {
    switch (role) {
        default: return room.energyAvailable >= getSpawnData(role).minEnergy;
    }
}

var necessaryRole= function(role, room) {
    switch (role) {
        case ROLE_WORKER:
            return _.filter(room.creeps, (creep) => creep.role == ROLE_WORKER).length < 6 * room.sources.length;
        default: l.warn("Spawn.autospawn: necessaryRole switch default reached");
    }
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
        let msg = "Spawn.autoSpawn";
        let actionMsg = "";
        const room = this.room;
        const roles = [ ROLE_WORKER ];
        msg += " allroles: "+roles.length;

        const necessaryRoles = _.filter(roles, (role) => necessaryRole(role, room));
        msg += " necessaryRoles: "+necessaryRoles.length;
        
        if (necessaryRoles.length) {
            const possibleRoles = _.filter(necessaryRoles, (role) => necessaryRole(role, room) && possibleRole(role, room));
    
            msg += " possibleRoles: "+possibleRoles.length;
            if (possibleRoles.length) {
    
                msg += " - neededLen: "+possibleRoles.length;
                const role = possibleRoles[0];
                const name = utils.createCreepName(ROLES[role].name);
                const data = getRoleData(role);
    

                const energy = (room.energyAvailable > getSpawnData(role).maxEnergy) ? getSpawnData(role).maxEnergy : room.energyAvailable;
                const bodyParts = getSpawnData(role).bodyParts;

                msg += " - creating body: energy: "+energy+" bodyParts: "+bodyParts;

                const body = utils.createCreepBody(
                    energy,
                    bodyParts
                );
                
                const status = this.spawnCreep( body, name, data );


                if ( status == OK )
                {
                    const creep = Game.creeps[name];
                    msg += " -> spawned - setting home: "+creep.home.name;
                    actionMsg = "-->";
                    creep.room.creepsAdd(creep);
                    
                } else {
                    msg += " -> status "+status;

                    msg += " (args: "+body+", "+name+",  "+data+")"+status;
                }
            }
        }
        l.og("",this,actionMsg,msg);
    }
}
