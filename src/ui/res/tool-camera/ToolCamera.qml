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
    width: 830
    height: 540
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

        Rectangle{
            id:background
            anchors{
                top: toolBar.bottom
                left: parent.left
                bottom: parent.bottom
            }
            width: viewfinder.width + 30
            height: viewfinder.height
            color: Theme.colorBackground
        }

        Rectangle{
            id:divider
            height: background.height - 20
            width: 5
            radius: 5
            z:2
            color: Theme.colorPrimary
            anchors{
                top: background.top
                topMargin: 10
            }
            x:10
        }

        MouseArea {
            id: mouseArea
            enabled: true
            anchors.fill:  divider
            z:3
            drag {
                target: divider
                axis: Drag.XAxis
                minimumX: 10
                maximumX: background.width - 20
            }
            cursorShape: Qt.SplitHCursor
            onPositionChanged:  {
                if (drag.active)
                    updatePosition()
            }
            onReleased: {
                updatePosition()
            }
            function updatePosition() {
                 effect.dividerValue = (divider.x-10)/(background.width-30)
            }
        }

        ShaderEffectSource {
            id: theSource
            smooth: true
            hideSource: true
            sourceItem: viewfinder
            anchors.fill: viewfinder
        }

        VideoOutput {
            id: viewfinder
            width: 640
            height: 480
            source: camera
            autoOrientation: true
            anchors{
                top:toolBar.bottom
                topMargin: 15
                left: parent.left
                leftMargin: 15
            }
            Camera{
                id: camera
                captureMode: Camera.CaptureStillImage
                videoRecorder {
                    resolution: "640x480"
                    frameRate: 30
                }
                onErrorCodeChanged: {
                    showToast("无可用摄像头")
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {

                }
            }
        }

        EffectBillboard{
            id:effect
            anchors.fill: viewfinder
            targetWidth: viewfinder.width
            targetHeight: viewfinder.height
            dividerValue: 0.0
            source: theSource
        }

    }
}
