#include "widget.h"
#include "widget2.h"
#include <QApplication>
#include <QtAndroid>
#include <QAndroidJniEnvironment>

#include <QtAndroidExtras/QAndroidJniObject>
#include <QScreen>
#include <QtAndroidExtras/QAndroidJniEnvironment>


enum Orientation
   {
       Unlocked = 4,           // SCREEN_ORIENTATION_SENSOR    (Android)
       LandscapeLocked = 0,    // SCREEN_ORIENTATION_LANDSCAPE (Android)  横屏
       PortraitLocked = 1,     // SCREEN_ORIENTATION_PORTRAIT  (Android)  竖屏
   };
//设置横屏竖屏



//void setOrientation()
//{
//    QAndroidJniObject activity = QtAndroid::androidActivity();
//    QAndroidJniObject windowManager = activity.callObjectMethod("getWindowManager", "()Landroid/view/WindowManager;");
//    QAndroidJniObject defaultDisplay = windowManager.callObjectMethod("getDefaultDisplay", "()Landroid/view/Display;");

//    QAndroidJniObject context = QtAndroid::androidContext();
//    QAndroidJniObject resources = context.callObjectMethod("getResources", "()Landroid/content/res/Resources;");
//    QAndroidJniObject configuration = resources.callObjectMethod("getConfiguration", "()Landroid/content/res/Configuration;");
//    jint rotation = configuration.getField<jint>("orientation");

//    int orientation;
//    if (rotation == 1) {
//        // Portrait mode
//        orientation = 1; // SCREEN_ORIENTATION_PORTRAIT
//    } else {
//        // Landscape mode
//        orientation = 0; // SCREEN_ORIENTATION_LANDSCAPE
//    }

//    activity.callMethod<void>("setRequestedOrientation", "(I)V", orientation);
//}










void setOrientation(Orientation orientation)   //
{
   const QAndroidJniObject Activity = QtAndroid::androidActivity();
   QAndroidJniEnvironment JniEnv;

   Activity.callMethod<void>("setRequestedOrientation", "(I)V", orientation);
   if(JniEnv->ExceptionCheck())
   {
       qDebug() << "setOrientation:: failed to set orientation!!!";
       JniEnv->ExceptionDescribe();
       JniEnv->ExceptionClear();
   }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setOrientation(LandscapeLocked);
//     setOrientation();
    Widget2 w;
    w.showFullScreen();
    w.show();
    return a.exec();
}
