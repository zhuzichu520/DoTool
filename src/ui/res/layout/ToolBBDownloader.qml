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
    title: "B站下载器"

    property bool isExpired : false
    property bool isLogin: false

    BBDownloaderController{
        id:controller

        onLoginSuccess: {
            isSuccess = true
        }

        onQrCodeExpired: {
            isExpired = true
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
                visible: isLogin
                color: Theme.colorBackground




            }


            Rectangle{
                id:layoutLogin
                anchors.fill: parent
                visible: !isLogin
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
                                isExpired = false
                                controller.refreshExpired()
                            }
                        }
                    }
                }

                Text{
                    text: isExpired ? "二维码已失效" : "请使用B站客户端\n扫描二维码登录"
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
