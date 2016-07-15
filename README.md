# ExtraWindowCam Unreal Engine 4 Plugin
A simple Unreal Engine 4 plugin that allows to have extra game windows with their own camera viewpoints. 

Tested with and compiled for Unreal Engine 4.12.5

## Known issues

- Does not work with motion blur enabled.
- Some bugs related to having a different resolution in the extra window(s) vs the main game window. Use "Lock Res to Main Window" setting to prevent this.
- Some shadow-related bugs, clipping bugs and other small artifacts (jitter). Note that this plugin is essentially an engine hack and its functionality is not (yet) officially supported by the engine.
- Mouse focus in extra windows does not properly work.

## How to use

This plugin adds a new actor class called "ExtraCamWindowActor" which is derived from CameraActor. To use it, simply copy the "Plugins" folder into your game project root directory and then put an ExtraCamWindowActor into your scene.  Note that the extra camera window has a serious performance impact as the scene is rendered another time.

<img alt="Customg Settings" src="https://raw.githubusercontent.com/chaosgrid/ExtraCamWindow/master/extraCamWindowPlugin.png" width="400" \>
