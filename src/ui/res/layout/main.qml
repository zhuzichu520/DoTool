import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import "../component"

CusWindow {
    id:window
    width: 800
    height: 600
    minimumWidth: 300
    minimumHeight: 300
    title: qsTr("DoTool")


    Component.onCompleted: {
        console.debug("DoTool-onCompleted")
    }

    Component.onDestruction: {
        console.debug("DoTool-onDestruction")
    }

    page: CusPage{

        CusToolBar {
            id:toolBar
        }

        CusSliderBar{
            id:slider
        }

        Loader{
            id:content
            anchors{
                top:toolBar.bottom
                left: slider.right
                bottom: parent.bottom
                right:parent.right
            }
            source: slider.getUrl()
        }
    }


}
