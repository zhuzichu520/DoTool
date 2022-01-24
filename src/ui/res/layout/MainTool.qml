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
        ListElement{
            name:"URL decode"
            func:function(){
                window.startWindow(Router.window_urldecode)
            }
        }
    }

    GridView{
        id:grid
        anchors.fill: parent
        model:modelTool
        focus: true
        delegate: Item{
            width: grid.cellWidth
            height: grid.cellHeight

            Rectangle{
                radius: 5
                anchors.fill: parent
                anchors.margins: 10
                color: item_mouse.containsMouse ? Qt.lighter(Theme.colorPrimary,1.4) : Theme.colorBackground
                Text {
                    text: model.name;
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    color: Theme.colorFontPrimary
                }

                MouseArea{
                    id:item_mouse
                    hoverEnabled: true
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        model.func()
                    }
                }
            }
        }
    }


}
