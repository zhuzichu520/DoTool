import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../storage"
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import Qt.labs.platform 1.1
import Qt.labs.settings 1.1
import com.dotool.controller 1.0
import com.dotool.ui 1.0

CusWindow {

    id:window
    width: 800
    height: 800
    title: "人脸识别"

    Component.onCompleted: {
        resizable = false
    }

    FaceController{
        id:controller
    }

    ListModel{
        id:listModel

    }

    page: CusPage{

        CusToolBar {
            id:toolBar
            maxEnable: false
            title: window.title
        }



        Rectangle{
            anchors{
                top: toolBar.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }

            CameraItem{
                anchors.centerIn:parent
            }

        }


    }

}
