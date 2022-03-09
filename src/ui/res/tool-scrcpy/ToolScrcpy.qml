import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../storage"
import QtQuick.Window 2.15
import com.dotool.controller 1.0
import QtQuick.Layouts 1.15

CusWindow {

    id:window
    width: 600
    height: 700
    minimumWidth: 600
    minimumHeight: 700
    title: "Android投屏"


    property int deviceIndex: 0

    ScrcpyController{
        id:controller
        onOutLog:
            (log,newLine)=>{
                inputLog.append(log)
                if(newLine){
                    inputLog.append("")
                }
            }
    }

    page: CusPage{

        CusToolBar {
            id:toolBar
            title: window.title
        }

        Rectangle{
            id:layoutTop
            border.width: 1
            border.color: Theme.colorDivider
            color:Theme.colorBackground
            radius: 5
            height: 80
            anchors{
                top: toolBar.bottom
                topMargin: 14
                left:parent.left
                leftMargin: 14
                right: parent.right
                rightMargin: 14
            }
            Button{
                text:"刷新设备列表"
                anchors.centerIn: parent
                onClicked: {
                    controller.updateDevice()
                    deviceIndex = 0
                }
            }
        }

        Rectangle{
            id:layoutDevices
            border.width: 1
            border.color: Theme.colorDivider
            color:Theme.colorBackground
            radius: 5
            height: 300
            anchors{
                top: layoutTop.bottom
                topMargin: 14
                left:parent.left
                leftMargin: 14
                right: parent.right
                rightMargin: 14
            }

            Text{
                id:lableDevice
                text:"设备列表"
                color:Theme.colorFontPrimary
                anchors{
                    top: parent.top
                    left: parent.left
                    topMargin: 10
                    leftMargin: 10
                }
            }

            ListView{
                anchors{
                    left: parent.left
                    right: dividerHCenter.left
                    top: lableDevice.bottom
                    bottom: parent.bottom
                    leftMargin: 1
                    topMargin: 5
                }
                model:controller.deviceList
                clip: true
                delegate: Rectangle{
                    height: 30
                    width: parent.width
                    color: deviceIndex === index ?  Theme.colorPrimary : Theme.colorBackground2
                    Text{
                        anchors{
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            leftMargin: 14
                        }
                        text:modelData
                    }

                    Rectangle{
                        width: parent.width
                        height: 1
                        anchors.bottom: parent.bottom
                        color:Theme.colorDivider
                    }

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            deviceIndex = index
                        }
                    }

                }
            }

            Rectangle{
                id:dividerHCenter
                height: parent.height
                width: 1
                anchors{
                    horizontalCenter: parent.horizontalCenter
                }
                color:Theme.colorDivider
            }

            Column{
                anchors{
                    left: dividerHCenter.right
                    right: parent.right
                    top: parent.top
                    bottom: parent.bottom
                }
                spacing:10
                leftPadding: 10
                topPadding: 10
                Text{
                    text:"设备序列号："+(controller.deviceList[deviceIndex] ? controller.deviceList[deviceIndex] : "")
                }
                Button{
                    text:"启动服务"
                    onClicked: {
                        controller.startServer(controller.deviceList[deviceIndex])
                    }
                }
                Button{
                    text: "停止服务"
                }
            }

        }

        Rectangle{
            id:layoutAdb
            border.width: 1
            border.color: inputAdb.focus ? Theme.colorPrimary : Theme.colorDivider
            color: Theme.colorBackground
            radius: 5
            height: 40
            anchors{
                top: layoutDevices.bottom
                topMargin: 14
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
                color:Theme.colorFontPrimary
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
                            inputLog.append("asdasdasd\n")
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

        Rectangle{
            id:layoutConsloe
            border.width: 1
            border.color: Theme.colorDivider
            color:Theme.colorBackground
            radius: 5
            anchors{
                top:layoutAdb.bottom
                bottom: parent.bottom
                left:parent.left
                right: parent.right
                margins: 14
            }

            ScrollView {
                anchors.fill: parent
                TextArea {
                    id:inputLog
                    readOnly: true
                    color:Theme.colorFontPrimary
                }
            }
        }



    }
}
