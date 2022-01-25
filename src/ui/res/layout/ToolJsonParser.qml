import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../tools/colorpicker"
import "../storage"
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15

CusWindow {

    id:window
    width: 800
    height: 500
    visible: false
    title: "JSON格式化"

    property var jsondata : '{
  "sites": {
    "site": [
      {
        "id": "1",
        "name": "菜鸟教程",
        "url": "www.runoob.com"
      },
      {
        "id": "2",
        "name": "菜鸟工具",
        "url": "c.runoob.com"
      },
      {
        "id": "3",
        "name": "Google",
        "url": "www.google.com"
      }
    ]
  }
}'

    Component.onCompleted: {
        var data = JSON.parse(jsondata);
        if(Array.isArray(data)){

        }

    }

    Component.onDestruction: {
        console.debug("ToolJSON-onDestruction")
    }

    page: CusPage{

        CusToolBar {
            id:toolBar
            maxEnable: false
            title: window.title
        }

        Rectangle{
            id:layoutLeft
            width: 300
            border.width: 1
            border.color: Theme.colorDivider
            color:Theme.colorBackground
            radius: 5
            anchors{
                top:toolBar.bottom
                topMargin: 8
                bottom: parent.bottom
                bottomMargin: 14
                left:parent.left
                leftMargin: 14
            }

            property alias lineNumberFont: lineNumbers.textMetrics.font
            property color lineNumberBackground: "#e0e0e0"
            property color lineNumberColor: "black"
            property alias font: textEdit.font
            property alias text: textEdit.text
            property color textBackground: "white"
            property color textColor: "black"


            Item {
                   anchors.fill: parent

                   ListView {
                       id: lineNumbers
                       property TextMetrics textMetrics: TextMetrics { text: "99999"; font: textEdit.font }
                       model: textEdit.lineCount
                       anchors.left: parent.left
                       anchors.top: parent.top
                       anchors.bottom: parent.bottom
                       anchors.margins: 10
                       width: textMetrics.boundingRect.width
                       clip: true

                       delegate: Rectangle {
                           width: lineNumbers.width
                           height: lineText.height
                           color: layoutLeft.lineNumberBackground
                           Text {
                               id: lineNumber
                               anchors.horizontalCenter: parent.horizontalCenter
                               text: index + 1
                               color: layoutLeft.lineNumberColor
                               font: lineNumbers.textMetrics.font
                           }

                           Text {
                               id: lineText
                               width: flickable.width
                               text: modelData
                               font: textEdit.font
                               visible: false
                               wrapMode: Text.WordWrap
                           }
                       }
                       onContentYChanged: {
                           if (!moving) return
                           flickable.contentY = contentY
                       }
                   }

                   Item {
                       anchors.left: lineNumbers.right
                       anchors.right: parent.right
                       anchors.top: parent.top
                       anchors.bottom: parent.bottom
                       anchors.margins: 10

                       Flickable {
                           id: flickable
                           anchors.fill: parent
                           clip: true
                           contentWidth: textEdit.width
                           contentHeight: textEdit.height
                           TextEdit {
                               id: textEdit
                               width: flickable.width
                               color: layoutLeft.textColor
                               wrapMode: Text.WordWrap
                           }
                           onContentYChanged: {
                               if (lineNumbers.moving) return
                               lineNumbers.contentY = contentY
                           }
                       }
                   }
               }


        }


    }

}
