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

    property int phoneWidth
    property int phoneHeight

    opacity: 0

    property int standWidth: 420

    Component.onCompleted: {
        controller.startServer(serial)
    }


    PhoneController{
        id:controller

        onShowPhoneChanged:
            (w,h)=>{
                videoItem.updateVideoSize(w,h)
                phoneWidth = standWidth
                phoneHeight = h/w * standWidth
                setGeometry((Screen.width - window.width) / 2,(Screen.height - window.height) / 2,window.w,window.h)
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
                    id:videoItem
                    anchors.fill: parent
                    decoder: controller
                }
            }
        }
    }
}
