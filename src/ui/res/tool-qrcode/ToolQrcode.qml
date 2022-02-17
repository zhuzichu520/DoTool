import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../storage"
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QZXing 3.3

CusWindow {

    id:window
    width: 800
    height: 500
    minimumWidth: 800
    minimumHeight: 500
    visible: false
    title: "二维码工具"

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

            CusLineEditArea{
                id:inputField
                anchors.fill: parent
                text:'Hellow world!'
            }
        }

        Rectangle{
            id:layoutRight
            border.width: 1
            border.color: Theme.colorDivider
            color:Theme.colorBackground
            radius: 5
            anchors{
                top:layoutLeft.top
                bottom: layoutLeft.bottom
                left: layoutLeft.right
                right: parent.right
                leftMargin: 14
                rightMargin: 14
            }

            Image{
                id:imageQRcode
                sourceSize.width: 250
                sourceSize.height: 250
                anchors.centerIn: parent
                source: "image://QZXing/encode/" + inputField.text +
                        "?correctionLevel=M" +
                        "&format=qrcode"
                cache: false
                MouseArea{
                    anchors.fill: parent
                    acceptedButtons:  Qt.RightButton
                    onClicked: {
                        if (mouse.button === Qt.RightButton) {
                            optionMenu.popup()
                        }
                    }
                }
            }

            Menu {
                id:optionMenu
                title: "菜单"
                MenuItem {
                    text: "保存"
                    onTriggered:{

                    }
                }
            }

        }
    }
}
