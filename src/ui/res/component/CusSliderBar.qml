import QtQuick 2.15
import "../view"
import "../storage"

Rectangle {
    id:root

    property int curIndex: 0

    width: 70
    height: parent.height
    anchors.left: parent.left
    color: Theme.colorBackground

    FontLoader {
        id: awesome
        source: "qrc:/font/iconfont.ttf"
    }

    ListModel{
        id:sliderModel
        ListElement{
            name:"首页"
            icon:"\ue719"
            url:"qrc:/layout/MainHome.qml"
        }
        ListElement{
            name:"工具"
            icon:"\ue6d7"
            url:"qrc:/layout/MainTool.qml"
        }
        ListElement{
            name:"设置"
            icon:"\ue6c7"
            url:"qrc:/layout/MainSetting.qml"
        }
    }

    Item{
        id:layout_logo
        width: 70
        height: 70
        anchors.top: parent.top

        Text {
            text: qsTr("DoTool")
            anchors.centerIn: parent
            color: Theme.colorPrimary
            font.italic: true
            font.bold: true
        }

    }


    ListView{
        model:sliderModel
        boundsBehavior: Flickable.StopAtBounds
        anchors{
            top:layout_logo.bottom
            left: parent.left
            right:parent.right
            bottom: parent.bottom
        }
        delegate: Item{
            width: 70
            height: 50
            Text{
                anchors.centerIn: parent
                text:model.icon
                font.family: awesome.name
                color:curIndex === model.index ? Theme.colorPrimary : Theme.colorFontPrimary
                font.pixelSize: 24
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    curIndex = model.index
                }
            }
        }
    }

    function getUrl(){
        return sliderModel.get(curIndex).url
    }

}
