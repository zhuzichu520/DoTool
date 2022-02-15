import QtQuick 2.15

import "../storage"


Item {
    anchors.fill: parent

    Text{
        anchors.centerIn: parent
        text:"MainHome"
    }

    property ListModel dataModel: ListModel {
          ListElement { title: qsTr("电话") }
          ListElement { title: qsTr("相册") }
          ListElement { title: qsTr("短信") }
          ListElement { title: qsTr("网络") }
          ListElement { title: qsTr("微信") }
          ListElement { title: qsTr("设置") }
          ListElement { title: qsTr("日历") }
          ListElement { title: qsTr("天气") }
          ListElement { title: qsTr("百度") }
          ListElement { title: qsTr("时间") }
          ListElement { title: qsTr("生活") }
      }



    Component.onCompleted: {
        console.debug("MainHome-onCompleted")
    }

    Component.onDestruction: {
        console.debug("MainHome-onDestruction")
    }

}
