﻿pragma Singleton
import QtQuick 2.15

QtObject {

    property string window_colorpicker: "qrc:/tool-colorpicker/ToolColorPicker.qml"
    property string window_jsonparser: "qrc:/tool-jsonparser/ToolJsonParser.qml"
    property string window_urldecode: "qrc:/tool-urldecode/ToolUrlDecode.qml"
    property string window_qrcode: "qrc:/tool-qrcode/ToolQrcode.qml"
    property string window_screencapture: "qrc:/tool-screencapture/ToolScreenCapture.qml"
    property string window_webpage: "qrc:/webview/WebPage.qml"

    property var router_table: [
        {
            path:window_colorpicker,
            onlyOne:true
        },
        {
            path:window_jsonparser,
            onlyOne:true
        },
        {
            path:window_urldecode,
            onlyOne:true
        },
        {
            path:window_qrcode,
            onlyOne:true
        },
        {
            path:window_screencapture,
            onlyOne:true
        },
        {
            path:window_webpage,
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


    function toUrl(path,isAttach=false,options={}){
        return path+"?isAttach="+isAttach + "&options="+JSON.stringify(options)
    }

    function parseUrl(url){
        let obj = {}
        if (url.indexOf('?') < 0) return obj
        let arr = url.split('?')
        obj.path = arr[0]
        url = arr[1]
        let array = url.split('&')
        for (let i = 0; i < array.length; i++) {
            let arr2 = array[i]
            let arr3 = arr2.split('=')
            obj[arr3[0]] = arr3[1]
        }
        return obj
    }

}
