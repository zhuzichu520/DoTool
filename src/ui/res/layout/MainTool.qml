import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import "../view"
import "../storage"

Item {
    anchors.fill: parent


    ListModel{
        id:modelTool
        ListElement{
            name:"颜色取色器"
            func:function(){
               window.startWindow(Router.window_colorpicker)
            }
        }
        ListElement{
            name:"JSON格式化"
            func:function(){
                 window.startWindow(Router.window_jsonparser)
            }
        }
    }

    GridView{
        id:grid
        anchors.fill: parent
        model:modelTool
        focus: true
        delegate: Rectangle{
            width: grid.cellWidth
            height: grid.cellHeight
            radius: 5
            color: item_mouse.containsMouse ? Qt.lighter(Theme.colorPrimary,1.4) : "transparent"

            MouseArea{
                id:item_mouse
                hoverEnabled: true
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    model.func()
                }
            }

            Column {
                id:item_column
                spacing: 14
                anchors.centerIn: parent
                Image {
                    source: "qrc:/image/ic_logo.ico";
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text {
                    text: model.name;
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: Theme.colorFontPrimary
                }
            }
        }
    }


}
