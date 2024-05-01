#include "mac.h"
#include <QDebug>
#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include <AppKit/AppKit.h>
#include "com/const.h"
//#include <AppKit/NSColor.h>

NSMutableArray *urls = [[NSMutableArray alloc]init];

Mac::Mac() {
}
Mac::~Mac() {
    if(urls != nil) {
        [urls release];
    }
}

void Mac::initWindow(QWindow* w) {
//    NSView *nsview = ( __bridge NSView * ) reinterpret_cast<void *>( w->winId() );
//    NSWindow *nswindow = [nsview window];
//    [nswindow miniaturize:nil];
    //获取到windows的主视图
//    NSView *themeView = nswindow.contentView.superview;
    //根据层级结构获取到标题栏视图
//    NSView * titleView = themeView.subviews[1];
//    nswindow.titlebarAppearsTransparent = true;
//    nswindow.titleVisibility = NSWindowTitleHidden;
//    nswindow.styleMask =
//            NSResizableWindowMask |
//            NSTitledWindowMask |
//            NSWindowStyleMaskClosable |
//            NSWindowStyleMaskMiniaturizable;
//    nswindow.backgroundColor = NSColor.blackColor;
//    nswindow.appearance = [NSAppearance appearanceNamed: NSAppearanceNameVibrantDark];
}

void Mac::notification(QString title, QString text) {
    NSUserNotification *userNotification = [[[NSUserNotification alloc] init] autorelease];
    userNotification.title = title.toNSString();
    userNotification.informativeText = text.toNSString();
    [[NSUserNotificationCenter defaultUserNotificationCenter] deliverNotification:userNotification];
}

//存在url但又不被允许
bool Mac::existsAllowedURL() {
    return [urls count] > 0;
}

void Mac::loadBookmarks() {
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSArray *urls_ = [userDefaults arrayForKey:@"urls"];
    if (urls_ != nil) {
        [urls removeAllObjects];
        [urls addObjectsFromArray:urls_];
    }
    NSLog(@"load urls %lu", [urls count]);
    for(NSString* url in urls) {
        NSLog(@"load url %@", url);
        NSData* bookmarkdata = [userDefaults objectForKey: url];
        if(bookmarkdata != nil) {
            BOOL isStale;
            NSURL *allowedUrl = [NSURL URLByResolvingBookmarkData:bookmarkdata
                                                          options:NSURLBookmarkResolutionWithSecurityScope
                                                    relativeToURL:nil
                                              bookmarkDataIsStale:&isStale
                                                            error:nullptr];
            BOOL y = (allowedUrl != nil && [allowedUrl startAccessingSecurityScopedResource]);
//            [urls addObject: url];
//            [userDefaults setObject:urls forKey:@"urls"];
            NSLog(@"load urlStr %@ NSURL %@ allowed suc %hhd", url, allowedUrl, y);
        } else {
            NSLog(@"load url %@ not allowed", url);
        }
    }
}

QString Mac::openSelectFile() {
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    [openDlg setCanChooseFiles:NO];
    [openDlg setCanChooseDirectories:YES];
    if ([openDlg runModal] == NSModalResponseOK) {
        for(NSURL* url in [openDlg URLs]) {
            NSString *path = [url path];
            NSLog( @"user selected path:%@", path);
            NSError *error = nil;
            NSData *bookmark = [url bookmarkDataWithOptions:NSURLBookmarkCreationWithSecurityScope
                                 includingResourceValuesForKeys:nil
                                                  relativeToURL:nil
                                                          error:&error];
            if(error != nil) {
                NSLog(@"openSelectFile error %@", error);
                return "";
            }
            if (bookmark == nil) {
                NSLog(@"%@ bookmark is nil", url);
                return "";
            }
            //
            NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
            bool exists = false;
            for(NSString *u in urls) {
                if([u isEqualToString:path]) {
                    exists = true;
                    break;
                }
            }
            if(exists) {
                NSLog( @"user selected path:%@ existed.", [url path]);
            } else {
                [urls addObject:path];
                [userDefaults setObject:urls forKey:@"urls"];
                [userDefaults setObject:bookmark forKey:path];
                [userDefaults synchronize];
                NSLog( @"user selected path:%@ save to userDefaults done.", [url path]);
            }
            return QString::fromNSString(path);
        }
    }
    return "";
}
void Mac::alert(QString tip1, QString tip2) {
    NSAlert *alert = [[NSAlert alloc] init];
    [alert setMessageText:tip1.toNSString()];
    if(!tip2.isEmpty()) {
        [alert setInformativeText:tip2.toNSString()];
    }
    if ([alert runModal] == NSAlertFirstButtonReturn) {
    }
}
void Mac::close() {
}
