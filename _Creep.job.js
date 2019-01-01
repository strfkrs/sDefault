Object.defineProperty(Creep.prototype, 'job', {
    get: function() {
        if (!this._job) {
            if (!this.memory.job) {
                this.memory.job = JOB_UNDEFINED;
            }
            this._job = this.memory.job;
        }
        return this._job;
    },
    set: function(v) {
        this.memory.job = v;
        this._job = v;
    },
    enumerable: false,
    configurable: true
});