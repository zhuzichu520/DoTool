import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import "../view"
import "../storage"

Item {
    anchors.fill: parent

    FontLoader {
        id: awesome
        source: "qrc:/font/iconfont.ttf"
    }

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
        ListElement{
            name:"二维码工具"
            func:function(){
                window.startWindow(Router.window_qrcode)
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

                Text{
                    anchors{
                        right: parent.right
                        bottom: parent.bottom
                        margins: 5
                    }
                    font.family: awesome.name
                    text:"\ue601"
                    color:item_mouse_option.containsMouse ? Theme.colorPrimary : Theme.colorFontPrimary
                    MouseArea{
                        id:item_mouse_option
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            console.debug("123")
                        }
                    }
                }

            }
        }
    }


}
