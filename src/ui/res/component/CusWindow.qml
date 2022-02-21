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
    property int windowFlags : Qt.Window | Qt.FramelessWindowHint
    flags: windowFlags
    visible: true
    color:"transparent"


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

    Rectangle{
        id:layoutToast
        color: "black"
        height: 0
        property alias text: textToast.text
        anchors{
            left: container.left
            right:container.right
            bottom: container.bottom
        }

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

    function showToast(text){
        layoutToast.height = 36
        layoutToast.text = text
        timerToast.restart()
    }

    function showLoading(){
        layoutLoading.visible = true
    }

    function hideLoading(){
        layoutLoading.visible = false
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
