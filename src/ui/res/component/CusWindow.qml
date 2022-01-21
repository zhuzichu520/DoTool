import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import "../storage"

ApplicationWindow {
    id:window

    property var router

    property alias page: container.children
    property int borderOffset: 5
    property int containerMargins: window.visibility === Window.Windowed ? borderOffset : 0

    flags: Qt.Window | Qt.FramelessWindowHint
    visible: true
    color: "transparent"

    onClosing: function(closeevent){
        try{
            window.destroy()
            closeevent.accepted = false
        }catch(err){

        }
    }

    Component.onCompleted: {
        if(router !== undefined){
            Router.addWindow(router.path,window)
        }
    }

    Component.onDestruction: {
        if(router !== undefined){
            Router.removeWindow(router.path)
        }
    }

    WindowResize{
        border: borderOffset
        enabled: window.visibility === Window.Windowed
    }

    function toggleMaximized() {
        if (window.visibility === Window.Maximized) {
            window.showNormal();
        } else {
            window.showMaximized();
        }
    }

    BorderImage {
        source: "qrc:/image/bg_shadow_border.png"
        anchors.fill: parent
        border{
            left: 20
            top: 20
            right: 20
            bottom: 20
        }
        smooth:true
    }


    Item {
        id:container
        anchors.fill: parent
        anchors.margins: containerMargins
        MouseArea{
            anchors.fill: parent
        }
    }


    function startWindow(path,isAttach,options={}){
        var data = Router.obtRouter(path)
        if(data === null){
            console.error("没有注册当前路由："+path)
            return
        }
        var win = Router.obtWindow(data.path)
        if(win !== null && data.onlyOne){
            win.show()
            win.raise()
            win.requestActivate()
            return
        }
        var comp = Qt.createComponent(data.url)
        if (comp.status !== Component.Ready){
            console.error("组件创建错误："+path)
            return
        }
        options.router = data
        win = comp.createObject(isAttach?root:null,options)
        win.show()
    }


}
