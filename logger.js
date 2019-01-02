module.exports = {
    timestamp: 0,
    paddings: {
        cpu:"      ",
        pre:"          ",
        name:"..........",
        action:"....................",
        debug:"_________________________________",
        controlsMessage:"_______________________"

    },
    _getCpuDifference: function() {
        return this._getCpu() - this.timestamp;
    },
    _getCpu: function() {
        return (Game.cpu.getUsed() - this.timestamp).toFixed(3);
    },
    _createCpu: function() {
        return this._getCpu().padding(this.paddings.cpu, false);
    },
    _createPre: function(pre) {
        return pre.padding(this.paddings.pre, false);
    },
    _createObjName: function(obj) {
        return obj.name.padding(this.paddings.name, false);
    },
    _createAction: function(action) {
        return action.padding(this.paddings.action, true);
    },
    _createMessage: function(msg) {
        return msg;
    },
    _create: function(pre, object, action, msg) {

        return `${this._createCpu()}${this._createPre(pre)}${this._createObjName(object)}${this._createAction(action)} ${this._createMessage(msg)}`;
    },
    /*
    **      l.init()
    */
    init: function() {
        this.timestamp = Game.cpu.getUsed();
    },
    /*
    **      l.status()
    */
    status: function() {
        const msg = this._create("",{name:""},"",`CPU sum: ${this._getCpu()} `+
        `(${Math.round(this._getCpu() / Game.cpu.limit*100)}%): `+
        `tick limit: ${Math.round(this._getCpu() / Game.cpu.tickLimit*100)}%, `+
        `bucket: ${Math.round(Game.cpu.bucket / 100)}%, `+
        `GCL progress: ${ Math.round(Game.gcl.progress / Game.gcl.progressTotal * 100)}%`);

        console.log(msg);
        console.log("#".repeat(msg.length));
    },
    /*
    **      l.og(pre, object, action, msg)
    */
    og: function(pre, object, action, msg) {
        const _object = (object) ? object : {name:""}
        console.log(this._create(pre, _object, action, msg));
    },
    /*
    **      l.controls(msg0, msg1)
    */
    controls: function(msg0, msg1) {
        
        const _p0 = (msg0 != "") ? ` ${msg0} ` : "";
        const _p1 = (msg1 != "") ? `${msg1} ` : "";

        console.log(    this._createCpu()+
                        this._createPre("CONTROLS")+
                        _p0.padding(this.paddings.controlsMessage, true)+
                        _p1
        );
    },
    /*
    **      l.debug(location, msg)
    */
    debug: function(location, msg) {

        if (Controls.debug()) {

            const _msg = (msg) ? msg : location;
            const _location = (msg) ? location : "";
            console.log(this._createCpu()
                + this._createPre("")
                + "DEBUG "
                +_location.padding(this.paddings.debug, true),_msg);
        }
    },
    /*
    **      l.warn(msg)
    */
    warn: function(msg) {
        console.log(this._create("WARNING ",{name:""},"",msg));
    }


}