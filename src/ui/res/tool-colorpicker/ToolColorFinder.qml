import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../storage"
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import Qt.labs.platform 1.1
import com.dotool.controller 1.0
import com.dotool.ui 1.0

CusWindow {

    property var onColorEvent

    id:window
    flags: Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint | Qt.Window
    width: 0
    height: 1

    ColorFinderController{
        id:controller
    }

    Component.onCompleted: {
        controller.refreshScreen()
    }

    onActiveChanged: {
        if(window.active){
            window.visibility = Window.FullScreen
        }
    }

    ItemImage {
        id:imageScreen
        anchors.fill: parent
        source:  controller.screenPixmap
        visible: false
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onPositionChanged: {
            popup.x = mouse.x + 10
            popup.y = mouse.y + 10
            controller.refreshSclae(mouse.x * Screen.devicePixelRatio,mouse.y * Screen.devicePixelRatio)
        }
        onClicked: {
            if(requestCode === 1){
                setResult(2,textColor.text)
            }
            window.close()
        }
    }

    Rectangle{

        property color borderColor : "#FF36C590"

        id:popup
        width: 80
        height: 80
        antialiasing: true
        border{
            width: 1
            color: borderColor
        }

        ItemImage {
            source: controller.scalePixmap
            anchors.fill: parent
            anchors.margins: 1
        }

        Rectangle{
            width: 1
            height: parent.height
            color: popup.borderColor
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle{
            width: parent.width
            height: 1
            color: popup.borderColor
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Rectangle{
        width: popup.width
        height: 30
        x:popup.x
        y:popup.y+popup.height
        color:"black"

        Text{
            id:textColor
            anchors.centerIn: parent
            color:"white"
            text:controller.colorText
            font.pixelSize: 14
        }
    }

}
