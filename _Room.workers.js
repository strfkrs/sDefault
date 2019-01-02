Object.defineProperty(Room.prototype, 'workers', {
    get: function() {
        if (this._workers == undefined) {
            
            if (this.memory.workerNames == undefined) {
                this.memory.workerNames = this.creeps.map(f => f.name);
            }
            this._workers = this.memory.workerNames.map(name => Game.creeps[name]);
        }
        return this._workers;
    },
    enumerable: false,
    configurable: true
});

Room.prototype.workersAdd = function(worker) {

    let workers = this.workers;
    if (!workers.includes(worker)) {
        workers.push(worker);
    
        this._workers = workers;
        this.memory.workerNames.push(worker.name);
    }
}

Room.prototype.workersRemoveByName = function(workerName) {

    let names = this.memory.workerNames.slice(0);
    if (names.includes(workerName)) {

        const index = names.indexOf(workerName);
        if (index > -1) {
    
            names.splice(index, 1);
    
            this.memory.workerNames = names;
            this._workers = names.map(name => Game.creeps[name]);
        }
    }
}