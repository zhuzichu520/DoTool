import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../tools/colorpicker"
import "../storage"
import QtQuick.Window 2.15

CusWindow {

    signal chooseColor(string color)

    width: 400
    height: 300
    maximumWidth: 400
    maximumHeight: 300
    minimumWidth: 400
    minimumHeight: 300
    visible: true
    title:"取色器"

    Component.onCompleted: {
        console.debug("ToolColorPicker-onCompleted")
    }

    Component.onDestruction: {
        console.debug("ToolColorPicker-onDestruction")
    }

    page: CusPage{

        CusToolBar {
            id:toolBar
            maxEnable: false
            title: window.title
        }

        ColorPicker{
            id:colorPicker
            color:"transparent"
            anchors{
                top: toolBar.bottom
                horizontalCenter: parent.horizontalCenter
            }
        }

        Button{
            text: "确认"
            anchors{
                right: parent.right
                bottom: parent.bottom
                rightMargin: 10
                bottomMargin: 10
            }
            onClicked: {
                chooseColor(colorPicker.colorValue)
                close()
            }
        }

    }

}
