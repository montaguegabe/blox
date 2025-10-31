//
//  CoreCommands.h
//  Blox
//

#ifndef __Blox__CoreCommands__
#define __Blox__CoreCommands__

#include <maya/MPxCommand.h>
#include <maya/MStatus.h>
#include <maya/MVector.h>

#pragma mark - Helper Functions

// Retrives the camera looking direction as a vector
MVector getCameraVector(MStatus &stat);

// Translates the selection
MStatus translateSelection(MVector byVector);

// Translates camera
MStatus translateCamera(MVector translation);

#pragma mark - Enable/Disable Commands

// Activates the Blox system
class CmdActivate : MPxCommand {
  public:
    static void *creator();
    MStatus doIt(const MArgList &args);
};

// Deactivates the Blox system
class CmdDeactivate : MPxCommand {
  public:
    static void *creator();
    MStatus doIt(const MArgList &args);
};

#pragma mark - Motion Commands

class CmdMotion : public MPxCommand {
  public:
    MStatus undoIt();
    MStatus redoIt();

  protected:
    MVector mMoveVector;
};

// Moves block forward
class CmdForward : CmdMotion {
  public:
    static void *creator();
    MStatus doIt(const MArgList &args);
    MStatus undoIt();
    MStatus redoIt();
    bool isUndoable() const { return true; }
};

// Moves block backwards
class CmdBackward : CmdMotion {
  public:
    static void *creator();
    MStatus doIt(const MArgList &args);
    MStatus undoIt();
    MStatus redoIt();
    bool isUndoable() const { return true; }
};

// Moves block right
class CmdRight : CmdMotion {
  public:
    static void *creator();
    MStatus doIt(const MArgList &args);
    MStatus undoIt();
    MStatus redoIt();
    bool isUndoable() const { return true; }
};

// Moves block backwards
class CmdLeft : CmdMotion {
  public:
    static void *creator();
    MStatus doIt(const MArgList &args);
    MStatus undoIt();
    MStatus redoIt();
    bool isUndoable() const { return true; }
};

#endif /* defined(__Blox__CoreCommands__) */
