pragma Singleton
import QtQuick 2.15

ListModel{

    Component.onCompleted: {
        append({name:"颜色取色器",path:Router.window_colorpicker})
        append({name:"JSON格式化",path:Router.window_jsonparser})
        append({name:"URL decode",path:Router.window_urldecode})
        append({name:"二维码工具",path:Router.window_qrcode})
        append({name:"B站下载器",path:Router.window_bbdownloader})
        append({name:"tinypng",path:Router.window_webpage})
        append({name:"https",path:Router.window_webpage})
        append({name:"iconfont",path:Router.window_webpage})
    }

}
