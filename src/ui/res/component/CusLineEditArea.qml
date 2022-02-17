import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../third/colorpicker"
import "../storage"
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15

ScrollView{

    property int numberWidth : 30
    property alias text: editArea.text
    id:scroll
    anchors.fill: parent
    focus: true
    clip: true
    Rectangle{
        anchors.fill: listNumber
        color: "#f0f0f0"
    }

    ListView{
        id:listNumber
        height: editArea.height
        width: scroll.numberWidth
        model:editArea.lineCount
        delegate: Item{
            height: editArea.font.pixelSize+2
            width: scroll.numberWidth
            Text{
                text:modelData + 1
                anchors{
                    verticalCenter: parent.verticalCenter
                    right: parent.right
                    rightMargin: 2
                }
                color: parseInt((editArea.cursorRectangle.y/editArea.contentHeight)*editArea.lineCount) === index ? Theme.colorPrimary : "#AAAAAA"
            }
        }
    }

    Rectangle{
        color:"#ffef0b"
        height: editArea.font.pixelSize+2
        width: scroll.width - listNumber.width
        x: listNumber.width
        y: editArea.cursorRectangle.y - 2
        visible: false
    }

    TextArea{
        id:editArea
        wrapMode: Text.WrapAnywhere
        x:scroll.numberWidth
        focus: true
        selectByMouse: true
        topPadding: 2
        bottomPadding: 2
        leftPadding: 2
        color:Theme.colorFontPrimary
        rightPadding: scroll.numberWidth + 2
    }
}
