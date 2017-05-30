
#import "RenderVC.h"

#include "osgNativeLib.h"

@interface RenderVC ()

@property (nonatomic, strong) CADisplayLink *displayLink;
@property (nonatomic, strong) UIView *renderView;
@property (nonatomic, strong) IBOutlet UIView *parentView;

@end

@implementation RenderVC

#pragma mark - PUBLIC

- (void)viewDidLayoutSubviews {
    [super viewDidLayoutSubviews];
    [self setupWindow];
    [self loadResources];
}

#pragma mark - PRIVATE

- (void)loadResources
{
    // Get path to the model.
    CFURLRef fileURL =
        CFBundleCopyResourceURL(
            CFBundleGetMainBundle(), CFSTR("box"), CFSTR("osgt"), 0);
    CFStringRef filePath = CFURLCopyFileSystemPath(fileURL, kCFURLPOSIXPathStyle);
    CFStringEncoding encodingMethod = CFStringGetSystemEncoding();
    const char *absolutePath = CFStringGetCStringPtr(filePath, encodingMethod);
    // Load the model.
    osgNativeLib::loadModel(absolutePath);
}

- (void)setupWindow
{
    // Remove old display link.
    if (self.displayLink) {
        [self.displayLink invalidate];
        self.displayLink = nil;
    }
    // Create new display link.
    self.displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(step)];
    [self.displayLink
        addToRunLoop:[NSRunLoop currentRunLoop]
        forMode:NSDefaultRunLoopMode];
    // Embed OpenSceneGraph render view.
    self.renderView =
        osgNativeLib::init(
            self.parentView.frame.size.width,
            self.parentView.frame.size.height,
            [UIScreen mainScreen].scale,
            self.parentView);
    [self.view sendSubviewToBack:self.renderView];
}

- (void)step
{
    osgNativeLib::frame();
}

@end

