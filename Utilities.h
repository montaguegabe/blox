//
//  Debug.h
//  Blox
//
//  Created by Gabe Montague on 3/19/15.
//
//

#ifndef Blox_Debug_h
#define Blox_Debug_h

// Checks an MStatus for use in command classes only
#define checkStatus() if(!stat){stat.perror("Blox error"); return stat;}
#define checkStatusMsg(a) if(!stat){displayError(a); return stat;}
#define checkStatusReturn() if(!stat){return stat;}

// Outputs a double to the info bar
#define logDouble(a) MString loggingStr; loggingStr = a; MGlobal::displayInfo(loggingStr);

#endif
