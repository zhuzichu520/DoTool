import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import "../storage"
import "../view"


Rectangle {

    property string title
    property url logo
    property var window: Window.window
    property bool maxEnable: true
    property bool minEnable: true
    property bool closeEnable: true
    property bool darkEnable: true

    clip: true
    height: 30

    anchors{
        left: parent.left
        right: parent.right
        top:parent.top
    }

    function toggleMaximized() {
        if (window.visibility === Window.Maximized) {
            window.showNormal();
        } else {
            window.showMaximized();
        }
    }

    Rectangle {
        id:layout_top
        color: Theme.colorBackground1
        anchors.fill: parent

        TapHandler {
            onTapped: if (tapCount === 2) toggleMaximized()
            gesturePolicy: TapHandler.DragThreshold
        }

        MouseArea{
            anchors.fill: parent
            acceptedButtons: Qt.NoButton

        }

        DragHandler {
            grabPermissions: TapHandler.CanTakeOverFromAnything
            onActiveChanged: if (active) { window.startSystemMove(); }
        }

        RowLayout {
            spacing: 5
            anchors.left: parent.left
            anchors.leftMargin: 8
            height: parent.height
            Image {
                sourceSize: Qt.size(15,15)
                source: logo
            }

            Text {
                text: title
                font.pixelSize: 12
            }
        }

        RowLayout {
            spacing: 0
            anchors.right: parent.right
            anchors.rightMargin: 5
            height: parent.height

            CusToolButton {
                icon: AppStorage.isDark ? "\ue6c9" : "\ue6e6"
                color: AppStorage.isDark ? "#FA9D16" : "#FA9D16"
                onClickEvent: {
                    AppStorage.isDark = !AppStorage.isDark
                }
                visible: darkEnable
            }

            CusToolButton {
                icon: "🗕"
                onClickEvent: window.showMinimized()
                visible: minEnable
            }
            CusToolButton {
                icon: window.visibility === Window.Maximized ? "🗗" : "🗖"
                onClickEvent: window.toggleMaximized();
                visible: maxEnable
            }
            CusToolButton {
                icon: "🗙"
                onClickEvent: window.close();
                visible: closeEnable
            }
        }
    }

}
