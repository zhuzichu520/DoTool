import QtQuick 2.0

Item {
    id:root

    property alias icon : textIcon.text
    property alias color : textIcon.color
    signal clickEvent

    height: 30
    width: 30

    FontLoader {
        id: awesome
        source: "qrc:/font/iconfont.ttf"
    }

    Text {
        id:textIcon
        font.pixelSize: 12
        font.family: awesome.name
        color: "#BBB"
        anchors.centerIn: parent
    }

    MouseArea {
        cursorShape: Qt.PointingHandCursor
        anchors.fill: parent
        onClicked: clickEvent()
    }

}
