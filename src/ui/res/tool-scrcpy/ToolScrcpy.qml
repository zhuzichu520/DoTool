import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../storage"
import QtQuick.Window 2.15
import com.dotool.controller 1.0

CusWindow {

    id:window
    width: 600
    height: 800
    minimumWidth: 600
    minimumHeight: 800
    title: "Android投屏"

    ScrcpyController{
        id:controller
    }

    page: CusPage{

        CusToolBar {
            id:toolBar
            maxEnable: false
            title: window.title
        }


        Rectangle{
            id:layoutConsloe
            border.width: 1
            border.color: Theme.colorDivider
            color:Theme.colorBackground
            radius: 5
            height: 160
            anchors{
                bottom: parent.bottom
                bottomMargin: 14
                left:parent.left
                leftMargin: 14
                right: parent.right
                rightMargin: 14
            }


        }

        Rectangle{
            border.width: 1
            border.color: inputAdb.focus ? Theme.colorPrimary : Theme.colorDivider
            color: Theme.colorBackground
            radius: 5
            height: 40
            anchors{
                bottom: layoutConsloe.top
                bottomMargin: 14
                left:parent.left
                leftMargin: 14
                right: parent.right
                rightMargin: 14
            }


            Text{
                id:textAdb
                text:"adb命令："
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: 10
                }
                color:Theme.colorFontPrimary
            }

            TextInput{
                id:inputAdb
                clip: true
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: textAdb.right
                    right: layoutOptions.left
                    leftMargin: 2
                    rightMargin: 5
                }
                focus: true
                text: "devices"
            }

            Row{
                id:layoutOptions
                spacing: 4
                anchors{
                    verticalCenter: parent.verticalCenter
                    right: parent.right
                    rightMargin: 10
                }

                ListModel{
                    id:dataModel

                    ListElement{
                        title:"执行"
                        color:"#3498db"
                        func:function(){
                            controller.adbExec(inputAdb.text)
                        }
                    }

                    ListElement{
                        title:"终止"
                        color:"#f5653b"
                        func:function(){
                        }
                    }

                    ListElement{
                        title:"清理"
                        color:"#7b7b7b"
                        func:function(){
                        }
                    }
                }

                Repeater {
                    model:dataModel
                    delegate: Rectangle{
                        color: model.color
                        height: 20
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
        }

    }
}
