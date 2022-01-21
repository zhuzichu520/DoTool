import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../tools/colorpicker"
import "../storage"
import QtQuick.Window 2.15

CusWindow {

    id:window
    width: 800
    height: 500
    visible: false
    title: "JSON格式化"

    property var jsondata : '{
  "sites": {
    "site": [
      {
        "id": "1",
        "name": "菜鸟教程",
        "url": "www.runoob.com"
      },
      {
        "id": "2",
        "name": "菜鸟工具",
        "url": "c.runoob.com"
      },
      {
        "id": "3",
        "name": "Google",
        "url": "www.google.com"
      }
    ]
  }
}'

    Component.onCompleted: {
        var data = JSON.parse(jsondata);
        if(Array.isArray(data)){

        }

    }

    Component.onDestruction: {
        console.debug("ToolJSON-onDestruction")
    }

    page: CusPage{

        CusToolBar {
            id:toolBar
            maxEnable: false
            title: window.title
        }


    }

}
