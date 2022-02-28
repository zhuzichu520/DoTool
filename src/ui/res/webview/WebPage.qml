import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../storage"
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import com.dotool.controller 1.0
import QtWebView 1.1
import QtQuick.Controls.Styles 1.0

CusWindow {

    property alias url: webView.url

    id:window
    width: 800
    height: 600
    visible: false
    minimumWidth: 800
    minimumHeight: 600
    title: "网页浏览器"

    page: CusPage{

        CusToolBar {
            id:toolBar
            title: window.title
        }

        WebView{
            id:webView
            anchors{
                top: toolBar.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
        }

        ProgressBar {
            id: progressBar
            height: 3
            opacity: value !== 0 ? 1 : 0
            anchors {
                left: parent.left
                top: toolBar.bottom
                right: parent.right
            }
            value: webView && webView.loadProgress < 100 ? webView.loadProgress/100 : 0
            Behavior on opacity {
                NumberAnimation{
                    duration: 300
                }
            }
        }
    }
}
