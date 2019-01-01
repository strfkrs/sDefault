var rWorker = require("role.worker");

var jBuild = require("job.build");
var jUpgrade = require("job.upgrade");
var jRefillStructures = require("job.refillStructures");
var jRefillTowers = require("job.refillTowers");
var jIdle = require("job.idle");

var aIdle = require("action.idle");
var aHarvest = require("action.harvestSources");
var aRepair = require("action.upgrade");
var aBuild = require("action.build");
var aUpgrade = require("action.upgrade");
var aPickupResources = require("action.pickupResources");
var aTransferToStructures = require("action.transferEnergyToStructures");
var aTransferToTowers = require("action.transferEnergyToTowers");

global.INVALID = 999;

global.ROLE_UNDEFINED =                 19;
global.ROLE_WORKER =                    20;
global.ROLE_MAGE =                      21;
global.ROLE_WARRIOR =                   22;
global.ROLE_SPY =                       23;
global.ROLE_CLAIMER =                   24;

global.JOB_UNDEFINED =                  50;
global.JOB_IDLE =                       51;
global.JOB_REFILL_STRUCTURES =          52;
global.JOB_REFILL_TOWERS =              53;
global.JOB_BUILD =                      54;
global.JOB_UPGRADE =                    55;
global.JOB_SPY =                        56;
global.JOB_INVADE =                     57;
global.JOB_DEFEND =                     58;

global.ACTION_UNDEFINED =               99;
global.ACTION_IDLE =                    100;
global.ACTION_HARVEST =                 101;
global.ACTION_REPAIR =                  102;
global.ACTION_BUILD =                   103;
global.ACTION_UPGRADE =                 104;
global.ACTION_PICKUP =                  105;
global.ACTION_ATTACK =                  106;
global.ACTION_TRANSFER_TO_STRUCTURES =  107;
global.ACTION_TRANSFER_TO_TOWERS =      108;
global.ACTION_SPY =                     109;
global.ACTION_INVASION_WAIT =           110;
global.ACTION_INVASION_MOVE =           111;
global.ACTION_INVASION_EXECUTE =        112;
global.ACTION_INVASION_BUILD =          113;


global.ROLES = {};
global.ROLES[ROLE_WORKER] =                     rWorker;

global.JOBS = {};
global.JOBS[JOB_REFILL_TOWERS] =                jRefillTowers;
global.JOBS[JOB_REFILL_STRUCTURES] =            jRefillStructures;
global.JOBS[JOB_BUILD] =                        jBuild;
global.JOBS[JOB_UPGRADE] =                      jUpgrade;
global.JOBS[JOB_IDLE] =                         jIdle;


global.ACTIONS = {};
global.ACTIONS[ACTION_IDLE] =                   aIdle;
global.ACTIONS[ACTION_HARVEST] =                aHarvest;
global.ACTIONS[ACTION_REPAIR] =                 aRepair;
global.ACTIONS[ACTION_BUILD] =                  aBuild;
global.ACTIONS[ACTION_UPGRADE] =                aUpgrade;
global.ACTIONS[ACTION_PICKUP] =                 aPickupResources;
global.ACTIONS[ACTION_TRANSFER_TO_STRUCTURES] = aTransferToStructures;
global.ACTIONS[ACTION_TRANSFER_TO_TOWERS] =     aTransferToTowers;
