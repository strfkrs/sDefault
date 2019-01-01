var l = require("logger");

module.exports = {
    createCreepBody: function(energy, bodyParts) {
        var body = [];
        let energyAmount = energy;

        l.debug("util.createCreepBody","START energy: "+ energy+" bodyParts: "+JSON.stringify(bodyParts));

        for (var c = 0; ; c++) {
    
            const currentParts = bodyParts[c];
            const cost = this.getArrayCost(currentParts);


            l.debug("util.createCreepBody","round "+c+" currentParts "+JSON.stringify(currentParts)+" cost "+cost);


            if (energyAmount - cost >= 0) {
                energyAmount -= cost;
                body = body.concat(currentParts);
            } else break; // no more energy for the part
    
            if (c == bodyParts.length-1) {
                c = -1;
            }
        }

    
        body.sort();
    
        l.debug("util.createCreepBody","END body: "+JSON.stringify(body));

        return body;
    },
    getArrayCost(parts) {
        let energy = 0;
        for (var p in parts) {
            const part = parts[p];
            const cost = BODYPART_COST[part];
            l.debug("util.getArrayCost","cost:"+cost);
            energy += cost;
        }
        return energy;
    },
    createCreepName: function(name) {

        var c = 0;
        while(Game.creeps[name+c] != undefined) c++;
        return name+c;
    },
    getLeastUsedJob: function(creeps, jobArray) {
        let c = 0;
        let amount = 1;
        while (true) {

            const job = jobArray[c];
            const others = _.filter(creeps, (creep) => creep.job == job);

            l.debug("util.getLeastUsedJob:","creeps length "+creeps.length+", "+job+", job: "+amount+">"+others.length+" "+(amount > others.length));

            if (amount > others.length) {
                return job;
            }

            c++;
            if (c == jobArray.length) {
                c = 0;
                amount++;
            }
        }
    },
    getJobAmounts(creeps, jobs) {
        let sortData = {};

        for (var c = 0; c < creeps.length; c++) {
            const creep = creeps[c];
            if (sortData[creep.job] == undefined) {
                sortData[creep.job] = 1;
            } else {
                sortData[creep.job]++;
            }
        }

        for (var j = 0; j < jobs.length; j++) {
            const job = jobs[j];
            if (sortData[job] == undefined) {
                sortData[job] = 0;
            }
        }

        return sortData;
    },
    sortJobsByWorkers(workers, jobs) {
        let jobAmounts = this.getJobAmounts(workers, jobs);

        return jobs.sort((a,b) => jobAmounts[a] - jobAmounts[b]);

    },
    randChoice: function(array) {
        return [Math.round(Math.random()*this._messages.length)];
    },
    aggressivePlayer(creep) {

        if (!Memory.aggressivePlayers) {
            Memory.aggressivePlayers = [];
        }
        if (!Memory.alliedPlayers) {
            Memory.alliedPlayers = [];
        }
        
        
        return Memory.aggressivePlayers.includes(creep.owner.username) && !Memory.alliedPlayers.includes(creep.owner.username);
    },
    amountInArray(obj, array) {
        var count = 0;
        for(let i=0; i<array.length; i++)
            if (array[i]==obj)
                count++;
        return count;
    }

}