//
//  Tessellation.h
//  Blox
//
//  The tessellation manager provides mathematical operations to ensure that
//  moved blocks fall into the user's tessellation.
//
//  Created by Gabe Montague on 3/19/15.
//
//

#ifndef Blox_Tessellation_h
#define Blox_Tessellation_h

class MVector;

// Holds types of tessellations
enum TessellationMode {
    TessellationSquare,
    TessellationNone
};

class Tessellation {
public:
    
    // Access to singleton
    static Tessellation& get();
    
    // Calculates a snapped motion vector from a starting position and a raw motion vector
    MVector snapMotionVector(MVector& input);
    
    // Mode access
    void setMode(TessellationMode mode);
    TessellationMode getMode();

private:
    Tessellation();
    TessellationMode mMode;
    
    // Prevent copies
    Tessellation(Tessellation const&);
    void operator=(Tessellation const&);
};

// Pointer to

#endif
