# Blox

Rapid prototyping + nostalgia plugin for Autodesk Maya

## Installation

### Plugin Directory (`plugin/`)

The `plugin/` directory contains the core Blox plugin:

- **C++ Source Files**: Build these into a Maya plugin bundle (`.bundle` on macOS, `.mll` on Windows)
- **MEL Scripts**: `BloxActivate.mel` and `BloxDeactivate.mel` - These are automatically called by the plugin to set up hotkeys

**To install:**

1. **Build the plugin**:

   - Open `Blox.xcodeproj` in Xcode (macOS) or build with your preferred build system
   - The output will be `Blox.bundle` (macOS) or `Blox.mll` (Windows)

2. **Copy plugin files to Maya's plugin directory**:

   - Copy the compiled `.bundle`/`.mll` file to your Maya plugin directory:
     - macOS: `~/Library/Preferences/Autodesk/maya/[version]/plug-ins/`
     - Windows: `Documents/maya/[version]/plug-ins/`
   - Copy `BloxActivate.mel` and `BloxDeactivate.mel` to the same directory

3. **Load the plugin in Maya**:
   - Open Maya → Windows → Settings/Preferences → Plug-in Manager
   - Find "Blox" and check "Loaded" and "Auto load"

### Scripts Directory (`scripts/`)

The `scripts/` directory contains standalone utility scripts:

- **`rebuildScene.mel`**: Optimizes block scenes by merging colinear blocks along X, Y, and Z axes.

**To install:**

1. Copy `rebuildScene.mel` to your Maya scripts directory:

   - macOS: `~/Library/Preferences/Autodesk/maya/[version]/scripts/`
   - Windows: `Documents/maya/[version]/scripts/`

2. **Usage**: In Maya, source the script and call the function:
   ```mel
   source rebuildScene;
   RebuildScene();
   ```

**Note**: The `rebuildScene.mel` script attempts to solve an NP-hard problem (rectilinear polygon partitioning), so it uses a heuristic approach. While it works well for most cases, it may not always produce optimal results for complex block arrangements.

## Controls

| Shortcut | Action                   |
| -------- | ------------------------ |
| ⌘0       | Menu                     |
| ⌘1       | Delete                   |
| ⌘3       | Snap onto grid           |
| ⌘5       | Duplicate/Select         |
| ⌘7       | Move up                  |
| ⌘9       | Move down                |
| ⌘8       | Move forward             |
| ⌘2       | Move backward            |
| ⌘4       | Move left                |
| ⌘6       | Move right               |
| ⌘+       | Increase grid resolution |
| ⌘-       | Decrease grid resolution |
| ⌥⌘8      | Rotate pitch (forward)   |
| ⌥⌘2      | Rotate pitch (backward)  |
| ⌥⌘4      | Rotate yaw (left)        |
| ⌥⌘6      | Rotate yaw (right)       |
| ⌥⌘7      | Rotate roll (up)         |
| ⌥⌘9      | Rotate roll (down)       |
