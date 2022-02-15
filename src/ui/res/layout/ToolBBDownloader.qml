import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../storage"
import QtQuick.Window 2.15
import com.dotool.controller 1.0
import com.dotool.ui 1.0
import "../view"

CusWindow {

    id:window
    width: 600
    height: 400
    minimumWidth: 600
    minimumHeight: 400
    title: "B站下载器"
    property bool isExpired : false
    property bool isLogin: false

    //0：二维码开始扫描；1：二维码失效；2：二维码扫描确认中；3：登陆成功
    property int loginsStatus : 0

    BBDownloaderController{
        id:controller

        onLoginSuccess: {
            loginsStatus = 3
        }

        onQrCodeExpired: {
            loginsStatus = 1
        }

        onScanSuccess: {
            loginsStatus = 2
        }
    }

    FontLoader {
        id: awesome
        source: "qrc:/font/iconfont.ttf"
    }


    page: CusPage{

        CusToolBar {
            id:toolBar
            maxEnable: false
            title: window.title
        }

        Item{
            anchors{
                top: toolBar.bottom
                left: parent.left
                right:parent.right
                bottom:parent.bottom
            }

            Rectangle{
                anchors.fill: parent
                visible: loginsStatus === 3
                color: Theme.colorBackground




            }


            Rectangle{
                id:layoutLogin
                anchors.fill: parent
                visible: loginsStatus !== 3
                color: Theme.colorBackground
                ItemImage {
                    id:imageQrCode
                    source: controller.qrPixmap
                    width: 123
                    height: 123
                    anchors.centerIn: parent
                }

                Rectangle{
                    anchors.fill: imageQrCode
                    color: "#88FFFFFF"
                    visible: isExpired


                    Rectangle{
                        width: 60
                        height: 60
                        color: mouseRefresh.containsMouse ? Qt.darker(Theme.colorBackground,1.2) : Theme.colorBackground
                        anchors.centerIn: parent

                        border{
                            width: 1
                            color:Theme.colorDivider
                        }

                        Text {
                            id:textIcon
                            font.pixelSize: 20
                            font.family: awesome.name
                            color:Theme.colorPrimary
                            anchors{
                                horizontalCenter: parent.horizontalCenter
                                top: parent.top
                                topMargin: 15
                            }

                            text:"\ue69c"
                        }

                        Text{
                            text: "点击刷新"
                            color:Theme.colorFontSecondary
                            anchors{
                                horizontalCenter: parent.horizontalCenter
                                bottom: parent.bottom
                                bottomMargin: 7
                            }
                            font.pixelSize: 12
                        }

                        MouseArea{
                            id:mouseRefresh
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                loginsStatus = 0
                                controller.refreshExpired()
                            }
                        }
                    }
                }

                Text{
                    text: {
                        //  "二维码已失效" : "请使用B站客户端\n扫描二维码登录"
                        switch(loginsStatus){
                        case 0:
                            return "请使用B站客户端\n扫描二维码登录"
                        case 1:
                            return "二维码已失效"
                        case 2:
                            return "✅扫描成功<br>请在手机上确认"
                        case 3:
                            return "登陆中...."
                        default:
                            return
                        }

                    }
                    anchors{
                        horizontalCenter: imageQrCode.horizontalCenter
                        top: imageQrCode.bottom
                        topMargin: 14
                    }
                    color:Theme.colorFontPrimary
                    horizontalAlignment: Text.AlignHCenter
                }

            }

        }

    }
}
