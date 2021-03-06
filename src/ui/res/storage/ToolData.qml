pragma Singleton
import QtQuick 2.15

ListModel{

    Component.onCompleted: {
        append({name:"颜色选择器",url:Router.toUrl(Router.window_colorpicker)})
        append({name:"JSON格式化",url:Router.toUrl(Router.window_jsonparser)})
        append({name:"Markdown编辑器",url:Router.toUrl(Router.window_markdown)})
        append({name:"URL decode",url:Router.toUrl(Router.window_urldecode)})
        append({name:"Base64",url:Router.toUrl(Router.window_base64)})
        append({name:"md5&sha",url:Router.toUrl(Router.window_digest)})
        append({name:"二维码工具",url:Router.toUrl(Router.window_qrcode)})
        append({name:"摄像头",url:Router.toUrl(Router.window_camera)})
        append({name:"屏幕截图",url:Router.toUrl(Router.window_screencapture,true)})
        append({name:"Android投屏",url:Router.toUrl(Router.window_scrcpy)})
        append({name:"OpenCv学习",url:Router.toUrl(Router.window_opencv)})
        append({name:"人脸识别",url:Router.toUrl(Router.window_face)})
        //        append({name:"Qt打包工具",url:Router.toUrl(Router.window_pack)})
        //        append({name:"tinypng",url:Router.toUrl(Router.window_webpage,false,{title:"tinypng",url:"https://tinypng.com/"})})
        //        append({name:"https",url:Router.toUrl(Router.window_webpage,false,{title:"https",url:"https://www.upyun.com/https"})})
        //        append({name:"iconfont",url:Router.toUrl(Router.window_webpage,false,{title:"iconfont",url:"https://www.iconfont.cn/"})})
        //        append({name:"OpenGL学习",url:Router.toUrl(Router.window_opengl)})
    }

}
