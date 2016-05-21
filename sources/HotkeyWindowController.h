#import "ProfileModel.h"
#import <Cocoa/Cocoa.h>
#import <Carbon/Carbon.h>

@class PseudoTerminal;

@interface HotkeyWindowController : NSObject

// Hotkey windows' restorable state is saved in the application delegate because these windows are
// often ordered out, and ordered-out windows are not saved. This is assigned to when the app state
// is decoded and updated from saveHotkeyWindowState.
@property(nonatomic, retain) NSDictionary *restorableState;
@property(nonatomic, readonly) BOOL rollingInHotkeyTerm;
@property(nonatomic, readonly, getter=isHotKeyWindowOpen) BOOL hotKeyWindowOpen;
@property(nonatomic, readonly) BOOL haveEventTap;
@property(nonatomic, readonly) int controlRemapping;
@property(nonatomic, readonly) int leftOptionRemapping;
@property(nonatomic, readonly) int rightOptionRemapping;
@property(nonatomic, readonly) int leftCommandRemapping;
@property(nonatomic, readonly) int rightCommandRemapping;
@property(nonatomic, readonly, getter=isAnyModifierRemapped) BOOL anyModifierRemapped;

// Indicates if pressing some hotkey opens a dedicated window.
@property(nonatomic, readonly) BOOL haveHotkeyBoundToWindow;

+ (instancetype)sharedInstance;
+ (void)closeWindowReturningToHotkeyWindowIfPossible:(NSWindow *)window;

- (void)showHotKeyWindow;
- (void)createHiddenHotkeyWindow;
- (void)doNotOrderOutWhenHidingHotkeyWindow;
- (void)fastHideHotKeyWindow;
- (void)hideHotKeyWindow:(PseudoTerminal*)hotkeyTerm;
- (PseudoTerminal*)hotKeyWindow;
- (BOOL)eventIsHotkey:(NSEvent*)e;
- (void)unregisterHotkey;
- (BOOL)registerHotkey:(int)keyCode modifiers:(int)modifiers;
- (void)beginRemappingModifiers;
- (void)stopEventTap;

// Returns the profile to be used for new hotkey windows, or nil if none defined.
- (Profile *)profile;

// Updates -restorableState and invalidates the app's restorable state.
- (void)saveHotkeyWindowState;

// Make the app that was active before the hotkey window was opened active.
- (void)restorePreviouslyActiveApp;

@end
