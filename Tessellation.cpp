//
//  Tessellation.cpp
//  Blox
//
//  Created by Gabe Montague on 3/19/15.
//
//

#include <maya/MVector.h>
#include <math.h>
#include <maya/MGlobal.h>
#include <maya/MString.h>
#include "Tessellation.h"
#include "Utilities.h"

// Constructor
Tessellation::Tessellation() {
    mMode = TessellationSquare;
}

// Access to singleton
Tessellation& Tessellation::get()
{
    static Tessellation instance;
    return instance;
}

// Calculates a snapped motion vector from a starting position and a raw motion vector
MVector Tessellation::snapMotionVector(MVector& input) {
    
    // Behavior depends on tessellation
    switch (mMode) {
        case TessellationSquare: {
            
            // Snap to one of four directions
            double angle = atan2(input.z, input.x);
            
            if      (angle >= -M_PI_4 && angle < M_PI_4 ) return MVector::xAxis;
            else if (angle >= M_PI_4 && angle < 3.0 * M_PI_4) return MVector::zAxis;
            else if (angle >= 3.0 * M_PI_4 || angle < -3.0 * M_PI_4) return MVector::xNegAxis;
            else return MVector::zNegAxis;
        }
        case TessellationNone: {
            
            input.normalize();
            return input;
        }
    }
}

// Mode access
void Tessellation::setMode(TessellationMode mode) {
    mMode = mode;
}
TessellationMode Tessellation::getMode() {
    return mMode;
}