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
    title: "Opencv学习"

    Component.onCompleted: {
        resizable = false
    }

    OpencvController{
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
            id:backgroundLeft
            width: 160
            anchors{
                top: toolBar.bottom
                left: parent.left
            }
        }

        Rectangle{
            id:backgroundRight
            color: Theme.colorBackground2
            anchors{
                top: toolBar.bottom
                left: layoutOptions.right
                bottom: parent.bottom
                right: parent.right
            }
        }

        ColumnLayout{
            id:layoutOptions
            anchors.fill: backgroundLeft
            spacing: 8
            CusButton{
                text:"选择图片"
                Layout.topMargin: 16
                Layout.alignment: Qt.AlignHCenter
                onClicked: {
                    fileDialog.showDialog(function(path){
                        controller.readMat(path)
                    })
                }
            }
            CusButton{
                text:"识别身份证号码"
                Layout.topMargin: 16
                Layout.alignment: Qt.AlignHCenter
                onClicked: {
                    controller.recognizeIdCard()
                }
            }
        }

        ItemImage{
            source: controller.source
            width: controller.size.width
            height: controller.size.height
            anchors.centerIn: backgroundRight
        }

    }


    FileDialog{
        property var accetpFunc
        id:fileDialog
        title: "选择文件"
        acceptLabel: "确定"
        rejectLabel: "取消"
        folder: StandardPaths.writableLocation(StandardPaths.PicturesLocation)
        onAccepted: {
            if(accetpFunc){
                accetpFunc(file.toString().substring(8,file.toString().length))
            }
        }

        function showDialog(func){
            fileDialog.accetpFunc = func
            fileDialog.open()
        }
    }

}
