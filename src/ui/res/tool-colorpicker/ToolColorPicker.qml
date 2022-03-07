import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../third/colorpicker"
import "../storage"
import QtQuick.Window 2.15
import com.dotool.ui 1.0

CusWindow {


    id:window
    width: 400
    height: 260
    maximumWidth: 400
    maximumHeight: 260
    minimumWidth: 400
    minimumHeight: 260
    visible: true
    title:"颜色选择器"

    onWindowResult:
        (resultCode,data)=> {
            if(resultCode === 2){
                colorPicker.color = data
            }
        }

    page: CusPage{

        clip: true

        CusToolBar {
            id:toolBar
            maxEnable: false
            title: window.title
        }

        ColorPicker{
            id:colorPicker
            color:"transparent"
            anchors{
                top: toolBar.bottom
                horizontalCenter: parent.horizontalCenter
            }
        }

        Row{
            anchors{
                right: parent.right
                bottom:parent.bottom
            }

            CusToolButton {
                color: "#BBB"
                icon:"\ue61f"
                onClickEvent: {
                    navigate(Router.window_colorfinder,1)
                }
            }
        }
    }
}
