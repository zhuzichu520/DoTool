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
    width: 1
    height: 0

    Component.onCompleted: {
        selectArea.retrunParam()
    }

    onActiveChanged: {
        if(active){
            window.visibility = Window.FullScreen
        }
    }

    Image {
        id:image_screen
        anchors.fill: parent
        source:  "image://screen/"+UIHelper.getScreenIndex()
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
