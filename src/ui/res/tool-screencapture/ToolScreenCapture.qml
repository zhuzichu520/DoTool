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
    width: 1
    height: 1
    flags: Qt.FramelessWindowHint

    ScreenCaptureController{
        id:controller
    }

    Component.onCompleted: {
        controller.refreshScreen()
        selectArea.retrunParam()
    }

    onActiveChanged: {
        if(active){
            setGeometry(0,-1,Screen.width,Screen.height+1)
            resizable = false
            flags= Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint | Qt.Window
        }
    }

    ItemImage {
        id:image_screen
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            topMargin: 1
        }
        source: controller.screenPixmap
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
            window.destroy()
        }
    }

    Action {
        shortcut: "ESC"
        onTriggered: window.close()
    }

}
