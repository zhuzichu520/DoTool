import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../storage"
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import Qt.labs.platform 1.1
import com.dotool.ui 1.0
import com.dotool.controller 1.0

CusWindow {

    id:window
    flags: Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint | Qt.Window
    width: 1
    height: 0

    ScreenCaptureController{
        id:controller
    }

    Component.onCompleted: {
        controller.refreshScreen()
        selectArea.retrunParam()
    }

    onActiveChanged: {
        if(active){
            window.visibility = Window.FullScreen
            resizable = false
        }
    }

    ItemImage {
        id:image_screen
        anchors.fill: parent
        source:  controller.screenPixmap
    }

    ItemSelectArea{
        id:selectArea
        onClickRighListener: {
            controller.captureRect(
                             selectArea.getAreaX(),
                             selectArea.getAreaY(),
                             selectArea.getAreaWidth(),
                             selectArea.getAreaHeight()
                             )
            window.close()
        }
    }

    Action {
        shortcut: "ESC"
        onTriggered: window.close()
    }

}
