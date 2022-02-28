pragma Singleton
import QtQuick 2.15

QtObject {

    property string window_colorpicker: "/window/colorpicker"
    property string window_jsonparser: "/window/jsonparser"
    property string window_urldecode: "/window/urldecode"
    property string window_qrcode: "/window/qrcode"
    property string window_bbdownloader: "/window/bbdownloader"
    property string window_webpage: "/window/webpage"

    property var router_table: [
        {
            path:window_colorpicker,
            url:"qrc:/tool-colorpicker/ToolColorPicker.qml",
            onlyOne:true
        },
        {
            path:window_jsonparser,
            url:"qrc:/tool-jsonparser/ToolJsonParser.qml",
            onlyOne:true
        },
        {
            path:window_urldecode,
            url:"qrc:/tool-urldecode/ToolUrlDecode.qml",
            onlyOne:true
        },
        {
            path:window_qrcode,
            url:"qrc:/tool-qrcode/ToolQrcode.qml",
            onlyOne:true
        },
        {
            path:window_bbdownloader,
            url:"qrc:/tool-bbdownloader/ToolBBDownloader.qml",
            onlyOne:true
        },
        {
            path:window_webpage,
            url:"qrc:/webview/WebPage.qml",
            onlyOne:true
        }
    ]

    property var windows : new Map()

    function obtRouter(path){
        for(var index in router_table){
            var item = router_table[index]
            if(item.path === path){
                return item
            }
        }
        return null
    }

    function obtWindow(path){
        for(var key in windows){
            if (key === path) {
                return windows[key]
            }
        }
        return null
    }

    function addWindow(path,window){
        windows[path] = window
    }

    function removeWindow(path){
        delete windows[path]
    }

    function toParam(){

    }

    function parse(url){

    }

}
