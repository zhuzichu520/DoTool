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


    property string serial

    title: serial

    opacity: 0

    width: 1
    height: 1

    property int standWidth: 360

    property int menuWidth: 48

    Component.onCompleted: {
        controller.startServer(serial)
    }


    PhoneController{
        id:controller
        onShowPhoneChanged:
            (w,h)=>{
                videoItem.width = standWidth
                videoItem.height = h/w * standWidth
                window.width = videoItem.width + 2*borderOffset + menuWidth
                window.height = videoItem.height + toolBar.height + 2*borderOffset
                window.minimumWidth =  window.width
                window.minimumHeight = window.height
                window.maximumWidth =  window.width
                window.maximumHeight = window.height
                setGeometry((Screen.width - window.width) / 2,(Screen.height - window.height) / 2,window.width,window.height)
                opacity = 1
                videoItem.updateVideoSize(w,h)
            }
        onServerStop: {
            window.close()
        }
    }

    page: CusPage{

        id:page

        Rectangle{
            width: menuWidth
            height: parent.height
            color:"black"
            anchors{
                right: parent.right
                top: parent.top
            }
        }

        CusToolBar {
            id:toolBar
            title: window.title
            maxEnable: false
            anchors{
                left: parent.left
                right: parent.right
                rightMargin: menuWidth
                top:parent.top
            }
        }

        Item{
            id:layoutPhone
            anchors{
                top: toolBar.bottom
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }
        }

        Rectangle{
            id:layoutItem
            color: "black"
            anchors{
                top: layoutPhone.top
                left: layoutPhone.left
            }
            width: childrenRect.width
            height: childrenRect.height
            VideoItem {
                id:videoItem
                decoder: controller
            }
        }
    }
}
