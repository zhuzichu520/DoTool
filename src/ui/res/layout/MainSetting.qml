﻿import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import "../view"
import "../storage"

Item {
    anchors.fill: parent

    FontLoader {
        id: awesome
        source: "qrc:/font/iconfont.ttf"
    }

    ListModel{
        id:modelTool
        ListElement{
            name:"颜色取色器"
            func:function(){
                window.startWindow(Router.window_colorpicker)
            }
        }
        ListElement{
            name:"JSON格式化"
            func:function(){
                window.startWindow(Router.window_jsonparser)
            }
        }
        ListElement{
            name:"URL decode"
            func:function(){
                window.startWindow(Router.window_urldecode)
            }
        }
        ListElement{
            name:"二维码工具"
            func:function(){
                window.startWindow(Router.window_qrcode)
            }
        }
        ListElement{
            name:"B站下载器"
            func:function(){
                window.startWindow(Router.window_bbdownloader)
            }
        }
        ListElement{
            name:"tinypng"
            func:function(){
                window.startWindow(Router.window_webpage,false,{title:"tinypng",url:"https://tinypng.com/"})
            }
        }
        ListElement{
            name:"https"
            func:function(){
                window.startWindow(Router.window_webpage,false,{title:"https",url:"https://www.upyun.com/https"})
            }
        }
        ListElement{
            name:"iconfont"
            func:function(){
                window.startWindow(Router.window_webpage,false,{title:"iconfont",url:"https://www.iconfont.cn/"})
            }
        }
    }

    QtObject {
        id: d

        readonly property int cellWidth: 128
        readonly property int cellHeight: 128
        readonly property int iconWidth: 96
        readonly property int iconHeight: 96

        property int dragIndex: -1
        property bool dragBehavior: false
    }

    GridView {
        id: gridView
        anchors.fill: parent
        cellWidth: d.cellWidth
        cellHeight: d.cellHeight
        clip: true
        move: Transition {
            NumberAnimation { properties: "x"; duration: 100; easing.type: Easing.OutCubic }
            NumberAnimation { properties: "y"; duration: 100; easing.type: Easing.OutCubic }
        }
        moveDisplaced: Transition {
            NumberAnimation { properties: "x"; duration: 300; easing.type: Easing.OutCubic}
            NumberAnimation { properties: "y"; duration: 100;  easing.type: Easing.OutCubic }
        }
        model: modelTool
        delegate: Item {
            width: d.cellWidth
            height: d.cellHeight
            z: dragmouseArea.pressed ? 1000 : 1
            Rectangle {
                id: btnIconArea
                anchors.centerIn: parent
                width: d.iconWidth
                height: d.iconWidth
                radius: 8
                color: "transparent"
                border.color: "gray"
                Rectangle {
                    id: btnIcon
                    width: d.iconWidth
                    height: d.iconWidth
                    radius: 8
                    color: hoveMouseArea.containsMouse ? Qt.lighter(Theme.colorPrimary,1.4) : Theme.colorBackground
                    border.color: "black"
                    Behavior on x { enabled: d.dragBehavior; NumberAnimation { duration: 200 } }
                    Behavior on y { enabled: d.dragBehavior; NumberAnimation { duration: 200 } }
                    Text {
                        anchors.centerIn: parent
                        color: Theme.colorFontPrimary
                        text: model.name
                    }
                    MouseArea{
                      id:hoveMouseArea
                      anchors.fill: parent
                      hoverEnabled: true

                    }
                    MouseArea {
                        id: dragmouseArea
                        anchors.fill: parent
                        drag.target: parent

                        cursorShape: Qt.PointingHandCursor
                        onPressed: {
                            d.dragBehavior = false;
                            var pos = gridView.mapFromItem(btnIcon, 0, 0);
                            d.dragIndex = model.index;
                            btnIcon.parent = gridView;
                            btnIcon.x = pos.x
                            btnIcon.y = pos.y
                        }
                        onReleased: {
                            d.dragIndex = -1;
                            var pos = gridView.mapToItem(btnIconArea, btnIcon.x, btnIcon.y);
                            btnIcon.parent = btnIconArea;
                            btnIcon.x = pos.x;
                            btnIcon.y = pos.y;
                            d.dragBehavior = true;
                            btnIcon.x = 0;
                            btnIcon.y = 0;
                        }

                        onPositionChanged: {
                            var pos = gridView.mapFromItem(btnIcon, 0, 0);
                            var idx = gridView.indexAt(pos.x, pos.y);
                            if (idx > -1 && idx < gridView.count) {
                                modelTool.move(d.dragIndex, idx, 1)
                                d.dragIndex = idx;
                            }

                        }

                        onClicked: {
                            model.func()
                        }

                    }
                }
            }
        }
    }

}
