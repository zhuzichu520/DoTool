import QtQuick 2.15

Item {
    anchors.fill: parent

    Text{
        anchors.centerIn: parent
        text:"MainHome"
    }

    Component.onCompleted: {
        console.debug("MainHome-onCompleted")
    }

    Component.onDestruction: {
        console.debug("MainHome-onDestruction")
    }

}
