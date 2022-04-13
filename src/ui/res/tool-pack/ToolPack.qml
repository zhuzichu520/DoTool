import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../storage"
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import Qt.labs.platform 1.1
import Qt.labs.settings 1.1
import com.dotool.controller 1.0

CusWindow {

    id:window
    width: 600
    height: 436
    title: "Qt打包工具"

    Component.onCompleted: {
        resizable = false
    }

    PackController{
        id:controller
    }

    Component.onDestruction: {
        settingPack.buildDir = textBuildDir.text
        settingPack.binDir = textBinDir.text
    }

    Settings{
        id:settingPack
        category: "Pack"
        property string buildDir
        property string binDir
    }


    page: CusPage{

        CusToolBar {
            id:toolBar
            maxEnable: false
            title: window.title
        }


        ColumnLayout{

            anchors{
                top: toolBar.bottom
                left: parent.left
                right: parent.right
            }

            spacing: 8


            Row{
                Layout.leftMargin: 14
                Layout.topMargin: 14
                Text{
                    font.pixelSize: 12
                    text:"Qt套件路径："
                    color:Theme.colorFontPrimary
                }
                Text{
                    id:textBuildDir
                    font.pixelSize: 12
                    color:Theme.colorPrimary
                    font.underline: true

                    Component.onCompleted: {
                        if(settingPack.buildDir){
                            text = settingPack.buildDir
                        }else{
                            text = "选择"
                        }
                    }

                    MouseArea{
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            folderDialog.showDialog(function(path){
                                parent.text = path
                            })
                        }
                    }
                }
            }



            Row{
                Layout.leftMargin: 14
                Text{
                    font.pixelSize: 12
                    text:"Bin路径："
                    color:Theme.colorFontPrimary
                }
                Text{
                    id:textBinDir
                    font.pixelSize: 12
                    color:Theme.colorPrimary
                    font.underline: true

                    Component.onCompleted: {
                        if(settingPack.binDir){
                            text = settingPack.binDir
                        }else{
                            text = "选择"
                        }
                    }

                    MouseArea{
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            fileDialog.showDialog(function(path){
                                parent.text = path
                            })
                        }
                    }
                }
            }

            CusButton{
                text:"开始打包"
                Layout.leftMargin: 14
                onClicked: {
                    controller.pack(textBuildDir.text,textBinDir.text)
                }
            }

        }
    }

    FolderDialog{
        property var accetpFunc
        id:folderDialog
        title: "选择文件夹"
        acceptLabel: "确定"
        rejectLabel: "取消"
        onAccepted: {
            if(accetpFunc){
                accetpFunc(folder.toString().substring(8,folder.toString().length))
            }
        }

        function showDialog(func){
            folderDialog.accetpFunc = func
            folderDialog.open()
        }
    }

    FileDialog{
        property var accetpFunc
        id:fileDialog
        title: "选择文件"
        acceptLabel: "确定"
        rejectLabel: "取消"
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
