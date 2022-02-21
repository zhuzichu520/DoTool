import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../storage"
import QtQuick.Window 2.15
import com.dotool.controller 1.0
import com.dotool.ui 1.0
import "../view"

Popup {
    id:root

    property alias text: title.text

    modal: true
    width: 360
    height: 180
    anchors.centerIn: parent
    background: Rectangle{
        radius: 5

        color:Theme.colorBackground

        Text{
            id:title
            anchors{
                top: parent.top
                left: parent.left
                topMargin: 18
                leftMargin: 18
            }
        }

        Text{
            id:btnDownlaod
            text:"下载"
            anchors{
                right: parent.right
                bottom: parent.bottom
                rightMargin: 12
                bottomMargin: 12
            }
            color:Theme.colorPrimary
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    root.close()
                }
            }
        }

        Text{
            id:btnCancel
            text:"取消"
            anchors{
                top: btnDownlaod.top
                right: btnDownlaod.left
                rightMargin: 24
            }
            color:Theme.colorFontSecondary
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    root.close()
                }
            }
        }



    }
}
