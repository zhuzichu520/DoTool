import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15
import "../storage"
import "../global/global.js" as Global

ApplicationWindow {
    id:window

    property var router
    property alias page: container.children
    property int borderOffset: 5
    property int containerMargins: window.visibility === Window.Windowed ? borderOffset : 0
    property int windowFlags : Qt.Window | Qt.FramelessWindowHint
    flags: windowFlags
    color:"transparent"

    property int requestCode

    property var prevWindow

    signal windowResult(int requestCode,int resultCode,var data)

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

    DropShadow {
        anchors.fill: container
        radius: 8.0
        samples: 17
        color: Window.active ? Theme.colorPrimary : "#80000000"
        source: container
    }

    Item {
        id:container
        anchors.fill: parent
        anchors.margins: containerMargins
        MouseArea{
            anchors.fill: parent
        }
    }


    Rectangle{
        id:layoutToast
        color: "black"
        height: 0
        clip: true
        property alias text: textToast.text
        anchors{
            left: container.left
            right:container.right
            bottom: container.bottom
        }
        antialiasing: true

        Text{
            id:textToast
            anchors.centerIn: parent
            color : "white"
        }

        Behavior on height{
            NumberAnimation{
                duration: 300
            }
        }
    }

    Rectangle{
        id:layoutLoading
        anchors.fill: container
        color: "#33000000"
        visible: false
        BusyIndicator{
            width: 60
            height: 60
            anchors.centerIn: parent
        }
        z:99
        MouseArea{
            hoverEnabled: true
            anchors.fill: parent
        }
    }

    Timer{
        id:timerToast
        interval: 1500
        onTriggered: {
            layoutToast.text = ""
            layoutToast.height = 0
        }
    }

    function toggleMaximized() {
        if (window.visibility === Window.Maximized) {
            window.showNormal();
        } else {
            window.showMaximized();
        }
    }

    function showToast(text){
        layoutToast.height = 36
        layoutToast.text = text === undefined ? "" : text
        timerToast.restart()
    }

    function showLoading(){
        layoutLoading.visible = true
    }

    function hideLoading(){
        layoutLoading.visible = false
    }

    function navigate(url,requestCode){
        var obj = Router.parseUrl(url)
        if(Object.keys(obj).length===0){
            obj = Router.parseUrl(Router.toUrl(url))
        }
        var path = obj.path;
        var isAttach = obj.isAttach.bool();
        var options = JSON.parse(obj.options)
        var data = Router.obtRouter(path)
        if(data === null){
            console.error("没有注册当前路由："+path)
            return
        }
        var win = Router.obtWindow(data.path)
        if(win !== null && data.onlyOne){
            for(var key in options){
                win[key] = options[key]
            }
            options.requestCode = requestCode
            options.prevWindow = window
            win.show()
            win.raise()
            win.requestActivate()
            return
        }
        options.requestCode = requestCode
        options.prevWindow = window
        var comp = Qt.createComponent(data.path)
        if (comp.status !== Component.Ready){
            console.error("组件创建错误："+path)
            return
        }
        options.router = data
        win = comp.createObject(isAttach?window:null,options)
        win.show()
    }


    function setResult(resultCode,data){
        prevWindow.windowResult(requestCode,resultCode,data)
    }


}
