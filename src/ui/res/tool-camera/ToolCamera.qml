import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../storage"
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import com.dotool.ui 1.0
import QtMultimedia 5.15

CusWindow {

    id:window
    width: 800
    height: 510
    title: "摄像头"

    Component.onCompleted: {
        resizable = false
    }

    page: CusPage{

        CusToolBar {
            id:toolBar
            title: window.title
            maxEnable: false
        }

        Camera{
            id: camera
            captureMode: Camera.CaptureStillImage
            videoRecorder {
                resolution: "640x480"
                frameRate: 30
            }
            onErrorCodeChanged: {
                console.debug("------onErrorCodeChanged------")
            }
        }
        VideoOutput {
            id: viewfinder
            width: 640
            height: 480
            source: camera
            autoOrientation: true
            anchors{
                top:toolBar.bottom
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    showToast("toolBar:"+window.getToolBarHeight())
                }
            }
        }
    }
}
