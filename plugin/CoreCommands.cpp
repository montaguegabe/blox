//
//  CoreCommands.cpp
//  Blox
//

#include <maya/M3dView.h>
#include <maya/MArgList.h>
#include <maya/MDagPath.h>
#include <maya/MFn.h>
#include <maya/MFnCamera.h>
#include <maya/MFnTransform.h>
#include <maya/MGlobal.h>
#include <maya/MItSelectionList.h>
#include <maya/MPoint.h>
#include <maya/MPxCommand.h>
#include <maya/MTypes.h>
#include <maya/MVector.h>

#include "CoreCommands.h"
#include "Tessellation.h"
#include "Utilities.h"

#pragma mark - Enable/Disable Commands

// Activates the Blox system
MStatus CmdActivate::doIt(const MArgList &args) {

    MS stat = MGlobal::sourceFile("BloxActivate");
    return stat;
}
void *CmdActivate::creator() { return new CmdActivate; }

// Deactivates the Blox system
MStatus CmdDeactivate::doIt(const MArgList &args) {

    MS stat = MGlobal::sourceFile("BloxDeactivate");
    return stat;
}
void *CmdDeactivate::creator() { return new CmdDeactivate; }

#pragma mark - Helper Functions

// Retrives the camera looking direction as a vector
MVector getCameraVector(MStatus &stat) {

    MFnDagNode dagFn;
    MDagPath cameraPath;
    M3dView currentView = M3dView::active3dView();
    if (!stat)
        return MVector::zero;
    if (!currentView.getCamera(cameraPath)) {
        MGlobal::displayError("Current view has no valid camera");
        return MVector::zero;
    }
    MFnCamera cameraFn(cameraPath);
    MVector cameraVector = cameraFn.viewDirection(MSpace::kWorld, &stat);
    if (!stat) {
        stat.perror("Error getting camera vector");
        return MVector::zero;
    }

    return cameraVector;
}

// Translates the selection by a vector
MStatus translateSelection(MVector translation) {

    MS stat;

    // Instantiate wrappers to be filled
    MDagPath node;
    MObject component;

    // Store the active selection list
    MSelectionList list;
    MGlobal::getActiveSelectionList(list);

    // Iterate through the list's transform nodes
    for (MItSelectionList listIter(list, MFn::kTransform); !listIter.isDone();
         listIter.next()) {

        // Stores the current selection item as both a DAG path and an MObject
        listIter.getDagPath(node, component);

        // Sets the object on which the DAG node function set acts
        MFnTransform transformFn(node, &stat);
        if (stat)
            transformFn.translateBy(translation, MSpace::kWorld);
        else {
            MGlobal::displayError(
                "Couldn't operate transformations on selection");
            return stat;
        }
    }

    return MStatus::kSuccess;
}

// Translates camera
MStatus translateCamera(MVector translation) {

    MS stat;

    // Set camera eye point
    MFnDagNode dagFn;
    MDagPath cameraPath;
    M3dView currentView = M3dView::active3dView();
    if (!stat)
        return MS::kFailure;
    if (!currentView.getCamera(cameraPath)) {
        return MS::kFailure;
    }
    MFnCamera cameraFn(cameraPath);
    MPoint eyePoint = cameraFn.eyePoint(MSpace::kWorld);
    MPoint coiPoint = cameraFn.centerOfInterestPoint(MSpace::kWorld);
    eyePoint += translation;
    coiPoint += translation;
    cameraFn.setEyePoint(eyePoint, MSpace::kWorld);
    cameraFn.setCenterOfInterestPoint(coiPoint, MSpace::kWorld);

    return MS::kSuccess;
}

#pragma mark - Motion Commands

// Undo and redo for motion commands are the same
MStatus CmdMotion::redoIt() {

    // Translate selection
    MS stat = translateSelection(mMoveVector);
    checkStatusReturn();

    // Keep selection in focus
    stat = translateCamera(mMoveVector);
    checkStatusReturn();

    return MStatus::kSuccess;
}
MStatus CmdMotion::undoIt() {

    MS stat = translateSelection(mMoveVector * -1.0);
    checkStatusReturn();

    return MStatus::kSuccess;
}

// Moves block forward
MStatus CmdForward::doIt(const MArgList &args) {

    MS stat;

    MVector cameraVector = getCameraVector(stat);
    checkStatusReturn();

    mMoveVector = Tessellation::get().snapMotionVector(cameraVector);

    return redoIt();
}
void *CmdForward::creator() { return new CmdForward; }
MStatus CmdForward::undoIt() { return CmdMotion::undoIt(); }
MStatus CmdForward::redoIt() { return CmdMotion::redoIt(); }

// Moves block backwards
MStatus CmdBackward::doIt(const MArgList &args) {

    MS stat;

    MVector cameraVector = getCameraVector(stat);
    checkStatusReturn();
    cameraVector *= -1.0;

    mMoveVector = Tessellation::get().snapMotionVector(cameraVector);

    return redoIt();
}
void *CmdBackward::creator() { return new CmdBackward; }
MStatus CmdBackward::undoIt() { return CmdMotion::undoIt(); }
MStatus CmdBackward::redoIt() { return CmdMotion::redoIt(); }

// Moves block right
MStatus CmdRight::doIt(const MArgList &args) {

    MS stat;

    MVector cameraVector = getCameraVector(stat);
    checkStatusReturn();
    cameraVector = cameraVector.rotateBy(MVector::kYaxis, -M_PI_2);

    mMoveVector = Tessellation::get().snapMotionVector(cameraVector);

    return redoIt();
}
void *CmdRight::creator() { return new CmdRight; }
MStatus CmdRight::undoIt() { return CmdMotion::undoIt(); }
MStatus CmdRight::redoIt() { return CmdMotion::redoIt(); }

// Moves block left
MStatus CmdLeft::doIt(const MArgList &args) {

    MS stat;

    MVector cameraVector = getCameraVector(stat);
    checkStatusReturn();
    cameraVector = cameraVector.rotateBy(MVector::kYaxis, M_PI_2);

    mMoveVector = Tessellation::get().snapMotionVector(cameraVector);

    return redoIt();
}
void *CmdLeft::creator() { return new CmdLeft; }
MStatus CmdLeft::undoIt() { return CmdMotion::undoIt(); }
MStatus CmdLeft::redoIt() { return CmdMotion::redoIt(); }
