pragma Singleton
import QtQuick 2.15

ListModel{

    Component.onCompleted: {
        append({name:"颜色选择器",url:Router.toUrl(Router.window_colorpicker)})
        append({name:"JSON格式化",url:Router.toUrl(Router.window_jsonparser)})
        append({name:"Markdown编辑器",url:Router.toUrl(Router.window_markdown)})
        append({name:"URL decode",url:Router.toUrl(Router.window_urldecode)})
        append({name:"二维码工具",url:Router.toUrl(Router.window_qrcode)})
        append({name:"屏幕截图",url:Router.toUrl(Router.window_screencapture,true)})
        append({name:"Android投屏",url:Router.toUrl(Router.window_scrcpy)})
        append({name:"tinypng",url:Router.toUrl(Router.window_webpage,false,{title:"tinypng",url:"https://tinypng.com/"})})
        append({name:"https",url:Router.toUrl(Router.window_webpage,false,{title:"https",url:"https://www.upyun.com/https"})})
        append({name:"iconfont",url:Router.toUrl(Router.window_webpage,false,{title:"iconfont",url:"https://www.iconfont.cn/"})})
        append({name:"OpenGL学习",url:Router.toUrl(Router.window_opengl)})
    }

}
