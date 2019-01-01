module.exports = {
    timestamp: 0,
    paddings: {
        cpu:"      ",
        pre:"          ",
        name:"..........",
        action:"....................",
        debug:"_______________________________"
    },
    init: function() {
        this.timestamp = Game.cpu.getUsed();
    },
    getBucket: function() {
        return Game.cpu.bucket;
    },
    getCpuDifference: function() {/*
        if (Memory.logTimestamp === undefined) {
            Memory.logTimestamp = this.getCpu();
            return Memory.logTimestamp;
        } else {
            let old = Memory.logTimestamp;
            Memory.logTimestamp = this.getCpu();
            return Memory.logTimestamp - old;
        }*/
        return this.getCpu() - Memory.logTimestamp;
    },
    getCpu: function() {
        return (Game.cpu.getUsed() - this.timestamp).toFixed(3);
    },
    createCpu: function() {
        return this.getCpu().padding(this.paddings.cpu, false);
    },
    createPre: function(pre) {
        return pre.padding(this.paddings.pre, false);
    },
    createObjName: function(obj) {
        return ` ${obj.name} `.padding(this.paddings.name, false);
    },
    createAction: function(action) {
        return ` ${action} `.padding(this.paddings.action, true);
    },
    createMessage: function(msg) {
        return msg;
    },
    create: function(pre, object, action, msg) {

        return this.createCpu()
            + this.createPre(pre)
            + this.createObjName(object)
            + this.createAction(action)
            + this.createMessage(msg);
    },
    og: function(pre, object, action, msg) {
        let _object = (object) ? object : {name:""}
        console.log(this.create(pre, _object, action, msg));
    },
    log: function(msg) {
        console.log(this.create("",{name:""},"",msg));
    },
    header: function(msg) {
        console.log(this.create("",{name:""},"",msg));
    },
    debug: function(location, msg) {

        let _msg = (msg) ? msg : location;
        let _location = (msg) ? location : "";

        if (DEBUG) {
            console.log(this.createCpu()+"DEBUG "+_location.padding(this.paddings.debug, true),_msg);
        }
    },
    warn: function(msg) {
        console.log(this.create("WARNING ",{name:""},"",msg));
    },
    status: function() {
        let msg = this.create("",{name:""},"",`CPU sum: ${this.getCpu()} `+
        `(${Math.round(this.getCpu() / Game.cpu.limit*100)}%): `+
        `tick limit: ${Math.round(this.getCpu() / Game.cpu.tickLimit*100)}%, `+
        `bucket: ${Math.round(Game.cpu.bucket / 100)}%, `+
        `GCL progress: ${ Math.round(Game.gcl.progress / Game.gcl.progressTotal * 100)}%`);


        console.log("#".repeat(msg.length));
        console.log(msg);
        console.log("#".repeat(msg.length));
    }


}