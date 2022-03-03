import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../storage"
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import Qt.labs.platform 1.1

CusWindow {

    id:window
    flags: Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint | Qt.Window
    color:"#00000000"
    width: Screen.width
    height: Screen.height

    Component.onCompleted: {
        selectArea.retrunParam()
    }

    Image {
        id:image_screen
        anchors.fill: parent
        source:  "image://screen/%1".arg(String(new Date().getTime()))
    }

    ItemSelectArea{
        id:selectArea
        onClickRighListener: {

        }
    }

    Action {
        shortcut: "ESC"
        onTriggered: window.close()
    }

}
