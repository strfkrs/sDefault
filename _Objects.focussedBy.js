var l = require("logger");

Object.defineProperty(Structure.prototype, 'focussedBy', {
    get: function() {
        
        if (!this._focussedBy) {
            l.debug("Objects.focussedBy","Reloading Structure "+this.structureType+" "+this.id);
            this._focussedBy = _.filter(this.room.creeps, (c) => c.focus == this);
        }
        
        return this._focussedBy;
    },
    set: function(newValue) {
        if (newValue) {
            this._focussedBy = newValue;
        } else {
            this._focussedBy = [];
        }
    },
    enumerable: false,
    configurable: true
});

Object.defineProperty(Resource.prototype, 'focussedBy', {
    get: function() {
        
        if (!this._focussedBy) {
            l.debug("Objects.focussedBy","Reloading Ressource "+this.id);
            this._focussedBy = _.filter(this.room.creeps, (c) => c.focus == this);
        }
        
        return this._focussedBy;
    },
    set: function(newValue) {
        if (newValue) {
            this._focussedBy = newValue;
        } else {
            this._focussedBy = [];
        }
    },
    enumerable: false,
    configurable: true
});

Object.defineProperty(Source.prototype, 'focussedBy', {
    get: function() {
        
        if (!this._focussedBy) {
            l.debug("Objects.focussedBy","Reloading Source "+this.id);
            this._focussedBy = _.filter(this.room.creeps, (c) => c.focus == this);
        }
        
        return this._focussedBy;
    },
    set: function(newValue) {
        if (newValue) {
            this._focussedBy = newValue;
        } else {
            this._focussedBy = [];
        }
    },
    enumerable: false,
    configurable: true
});

Object.defineProperty(Flag.prototype, 'focussedBy', {
    get: function() {
        
        if (!this._focussedBy) {
            l.debug("Objects.focussedBy","Reloading Flag "+this.id);
            this._focussedBy = _.filter(this.room.creeps, (c) => c.focus == this);
        }
        
        return this._focussedBy;
    },
    set: function(newValue) {
        if (newValue) {
            this._focussedBy = newValue;
        } else {
            this._focussedBy = [];
        }
    },
    enumerable: false,
    configurable: true
});