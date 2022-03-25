import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../storage"
import QtQuick.Window 2.15

CusWindow {

    id:window
    width: 600
    height: 436
    title: "Base64"

    Component.onCompleted: {
        resizable = false
    }

    page: CusPage{

        CusToolBar {
            id:toolBar
            maxEnable: false
            title: window.title
        }

        Rectangle{
            id:layout_top
            height: 170
            border.width: 1
            border.color: Theme.colorDivider
            color:Theme.colorBackground
            radius: 5
            anchors{
                top:toolBar.bottom
                topMargin: 8
                left:parent.left
                right:parent.right
                leftMargin: 14
                rightMargin: 14
            }

            ScrollView {
                anchors.fill: parent
                clip: true
                focus: true
                TextArea {
                    id:textContent
                    wrapMode: Text.WrapAnywhere
                    selectByMouse:true;
                    selectByKeyboard: true
                    color:Theme.colorFontPrimary
                    focus: true
                }
            }
        }

        Row{

            spacing: 14

            anchors{
                top: layout_top.bottom
                bottom : layout_bottom.top
                left: parent.left
                right: parent.right
                leftMargin: 14
                rightMargin: 14
            }

            ListModel{
                id:dataModel

                ListElement{
                    title:"字符串转base64"
                    color:"#3498db"
                    func:function(){
                        textResult.text = UIHelper.toBase64(textContent.text)
                    }
                }

                ListElement{
                    title:"base64转字符串"
                    color:"#f5653b"
                    func:function(){
                        textResult.text = UIHelper.fromBase64(textContent.text)
                    }
                }

                ListElement{
                    title:"清空"
                    color:"#7b7b7b"
                    func:function(){
                        textContent.clear()
                        textResult.clear()
                    }
                }
            }

            Repeater {
                model:dataModel
                delegate: Rectangle{
                    color: model.color
                    height: 28
                    width: textTitle.width + 16
                    radius: 3
                    anchors.verticalCenter: parent.verticalCenter
                    Text{
                        id:textTitle
                        color: "white"
                        text: model.title
                        anchors.centerIn: parent
                        font.pixelSize: 13
                    }
                    MouseArea{
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            model.func()
                        }
                    }
                }
            }
        }

        Rectangle{
            id:layout_bottom
            height: 170
            border.width: 1
            border.color: Theme.colorDivider
            color:Theme.colorBackground
            radius: 5
            anchors{
                bottom:parent.bottom
                bottomMargin: 14
                left:parent.left
                right:parent.right
                leftMargin: 14
                rightMargin: 14
            }

            ScrollView {
                anchors.fill: parent
                TextArea {
                    id:textResult
                    wrapMode: Text.WrapAnywhere
                    selectByMouse: true
                    readOnly: true
                    color:Theme.colorFontPrimary
                }
            }
        }
    }
}
