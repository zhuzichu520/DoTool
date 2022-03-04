import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../third/colorpicker"
import "../storage"
import QtQuick.Window 2.15
import com.dotool.controller 1.0
import com.dotool.ui 1.0

CusWindow {

    signal chooseColor(string color)
    id:window
    width: 400
    height: 260
    maximumWidth: 400
    maximumHeight: 260
    minimumWidth: 400
    minimumHeight: 260
    visible: true
    title:"取色器"

    Component.onCompleted: {
        console.debug("ToolColorPicker-onCompleted")
    }

    Component.onDestruction: {
        console.debug("ToolColorPicker-onDestruction")
    }

    ColorPickerController{
        id:controller
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

        Row{
            anchors{
                right: parent.right
                bottom:parent.bottom
            }

            PanelBorder {
                height: 15; width: 50
                anchors.verticalCenter: parent.verticalCenter
                TextInput {
                    id: captureEdit
                    anchors.fill: parent
                    color: "#AAAAAA"
                    selectionColor: "#FF7777AA"
                    font.pixelSize: 11
                    maximumLength: 9
                    focus: false
                    text:textColor.text
                    readOnly: true
                    selectByMouse: true
                }
            }

            CusToolButton {
                color: "#BBB"
                icon:"\ue61f"
                onClickEvent: {
                    windowFull.showFullWindow()
                }
            }
        }


    }

    Window{

        signal colorChanged(string color)

        id:windowFull
        flags: Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint | Qt.Window
        color:"#00000000"

        onActiveChanged: {
            if(active){
                windowFull.visibility = Window.FullScreen
            }
        }

        Image {
            id:imageScreen
            anchors.fill: parent
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
                console.debug(textColor.text)
                colorChanged(textColor.text)
                windowFull.close()
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

        function showFullWindow(){
            imageScreen.source = ""
            imageScreen.source = "image://screen/0"
            controller.refreshScreen()
            windowFull.show()
        }

    }

}
