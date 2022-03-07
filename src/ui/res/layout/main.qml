import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtWebView 1.1
import "../component"

CusWindow {
    id:window
    width: 596
    height: 600
    minimumWidth: 596
    minimumHeight: 600
    title: qsTr("DoTool")
    visible: true

    page: CusPage{

        CusToolBar {
            id:toolBar
        }

        ListModel{
            id:sliderModel
            ListElement{
                name:"首页"
                icon:"\ue719"
                fontSize:24
                url:"qrc:/layout/MainHome.qml"
            }
            ListElement{
                name:"设置"
                icon:"\ue6c7"
                fontSize:24
                url:"qrc:/layout/MainSetting.qml"
            }
            ListElement{
                name:"关于"
                icon:"\ue622"
                fontSize:21
                url:"qrc:/layout/MainAbout.qml"
            }
        }


        CusSliderBar{
            id:slider
            model: sliderModel
        }

        Loader{
            id:content
            anchors{
                top:toolBar.bottom
                left: slider.right
                bottom: parent.bottom
                right:parent.right
            }
            source: slider.getUrl()
        }
    }


}
