import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../storage"
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import com.dotool.controller 1.0

CusWindow {

    id:window
    width: 650
    height: 500
    title: "JSON格式化"

    Component.onCompleted: {
        resizable = false
    }

    JsonParserController{
        id:controller
    }

    page: CusPage{

        CusToolBar {
            id:toolBar
            title: window.title
            maxEnable: false
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
                id:textLeft
                anchors.fill: parent
                text:'{"sites": {"site": [{"id": "1","name": "菜鸟教程","url": "www.runoob.com"},{"id": "2","name": "菜鸟工具","url": "c.runoob.com"},{"id": "3","name": "Google","url": "www.google.com"}]}}'
            }
        }


        Rectangle{
            id:layoutRight
            width: 300
            border.width: 1
            border.color: Theme.colorDivider
            color:Theme.colorBackground
            radius: 5
            anchors{
                top:layoutLeft.top
                bottom: layoutLeft.bottom
                left:layoutLeft.right
                leftMargin: 14
            }

            CusLineEditArea{
                anchors.fill: parent
                text:controller.jsonFormat(textLeft.text)
            }
        }

    }

}
