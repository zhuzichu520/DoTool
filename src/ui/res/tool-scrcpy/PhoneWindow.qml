import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../storage"
import QtQuick.Window 2.15
import com.dotool.controller 1.0
import com.dotool.ui 1.0
import QtQuick.Layouts 1.15
import QtMultimedia 5.15

CusWindow {

    id:window

    property int w: phoneWidth + 2*borderOffset
    property int h: phoneHeight + toolBar.height + 2*borderOffset

    property string serial

    width: w
    height: h
    minimumWidth: w
    minimumHeight: h
    title: serial

    property int phoneWidth:1
    property int phoneHeight:1

    opacity: 0

    property int standWidth: 320

    Component.onCompleted: {
        controller.startServer(serial)
    }


    PhoneController{
        id:controller

        onShowPhoneChanged:
            (w,h)=>{
                phoneWidth = standWidth
                phoneHeight = h/w * 320
                opacity = 1
            }
    }

    page: CusPage{

        id:page

        CusToolBar {
            id:toolBar
            title: window.title
        }

        Item{
            id:layoutPhone
            anchors{
                top: toolBar.bottom
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }


            Rectangle{
                color: "black"
                anchors.centerIn: parent
                width: window.phoneWidth
                height: window.phoneHeight
                VideoItem {
                    anchors.fill: parent
                    decoder: controller
                }
            }
        }
    }
}
