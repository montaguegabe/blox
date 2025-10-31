//
//  Blox.cpp
//  Blox
//
//  The main definition file for the plugin.
//

#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>
#include <maya/MString.h>

#include "Blox.h"
#include "CoreCommands.h"
#include "Tessellation.h"

// Initializes the plugin
MStatus initializePlugin(MObject obj) {

    // Initialize an instance of the plugin function group
    MFnPlugin plugin(obj, "Avurne", "0.1", "Any");

    // Register commands
    plugin.registerCommand("bloxActivate", CmdActivate::creator);
    plugin.registerCommand("bloxDeactivate", CmdDeactivate::creator);
    plugin.registerCommand("bloxForward", CmdForward::creator);
    plugin.registerCommand("bloxBackward", CmdBackward::creator);
    plugin.registerCommand("bloxRight", CmdRight::creator);
    plugin.registerCommand("bloxLeft", CmdLeft::creator);

    return MS::kSuccess;
}

// Uninitialize the plugin
MStatus uninitializePlugin(MObject obj) {

    // Initialize an instance of the plugin function group
    MFnPlugin plugin(obj);

    // Deregister commands
    plugin.deregisterCommand("bloxActivate");
    plugin.deregisterCommand("bloxDeactivate");
    plugin.deregisterCommand("bloxForward");
    plugin.deregisterCommand("bloxBackward");
    plugin.deregisterCommand("bloxRight");
    plugin.deregisterCommand("bloxLeft");

    // Deactivate the hotkeys
    MGlobal::sourceFile("BloxDeactivate");

    return MS::kSuccess;
}