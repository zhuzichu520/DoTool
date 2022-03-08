import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../storage"
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import com.dotool.controller 1.0

CusWindow {

    id:window
    width: 850
    height: 600
    minimumWidth: 850
    minimumHeight: 600
    title: "Readme编辑器"

    property int layoutWidth: (width-50)/2

    property string readmeData: '# DoTool

一款常用工具集合开源软件

## 1.适用范围

Windows系统（64）

## 2.下载地址
[DoTool工具下载](https://gitee.com/zhu-zichu/doc/raw/master/dotool/setup.exe)

## 3.工具集合

|颜色取色器|
|:---:|
|![](https://github.com/zhuzichu520/doc/blob/master/dotool/tool-colorpicker.png)|

|JSON格式化|
|:---:|
|![](https://github.com/zhuzichu520/doc/blob/master/dotool/tool-jsonparser.png)|

|URL 编解码|
|:---:|
|![](https://github.com/zhuzichu520/doc/blob/master/dotool/tool-urldecode.png)|

|二维码生成器|
|:---:|
|![](https://github.com/zhuzichu520/doc/blob/master/dotool/tool-qrcode.png)|

'

    page: CusPage{

        CusToolBar {
            id:toolBar
            title: window.title
        }



        CusMenuBar {
            id: menuBar
            anchors{
                top:toolBar.bottom
            }
            CusMenu {
                title: qsTr("文件")
                Action { text: qsTr("新建...") }
                Action { text: qsTr("打开...") }
                Action { text: qsTr("保存") }
                Action { text: qsTr("另存为...") }
                CusMenuSeparator { }
                Action { text: qsTr("退出") }
            }
            CusMenu {
                title: qsTr("编辑")
                Action { text: qsTr("剪切") }
                Action { text: qsTr("复制") }
                Action { text: qsTr("粘贴") }
            }
            CusMenu {
                title: qsTr("帮助")
                Action { text: qsTr("关于") }
            }
        }


        Rectangle{
            id:layoutLeft
            width: layoutWidth
            border.width: 1
            border.color: Theme.colorDivider
            color:Theme.colorBackground
            radius: 5
            anchors{
                top:menuBar.bottom
                topMargin: 4
                bottom: parent.bottom
                bottomMargin: 14
                left:parent.left
                leftMargin: 14
            }

            CusLineEditArea{
                id:textLeft
                anchors.fill: parent
                text:readmeData
            }
        }


        Rectangle{
            id:layoutRight
            width: layoutWidth
            border.width: 1
            border.color: Theme.colorDivider
            radius: 5
            anchors{
                top:layoutLeft.top
                bottom: layoutLeft.bottom
                left:layoutLeft.right
                leftMargin: 14
            }

            MouseArea{
                id:mouseShape
                anchors.fill: parent
                acceptedButtons: Qt.NoButton
            }

            Text{
                anchors.fill: parent
                text: textLeft.text
                textFormat: Text.MarkdownText
                onLinkActivated: {
                    Qt.openUrlExternally(link)
                }
                onLinkHovered: {
                    if(link.length!==0){
                        mouseShape.cursorShape = Qt.PointingHandCursor
                    }else{
                        mouseShape.cursorShape = Qt.ArrowCursor
                    }
                }
            }

        }

    }

}
