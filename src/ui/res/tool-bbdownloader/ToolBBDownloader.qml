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

    //loginStatus 0：二维码开始扫描；1：二维码失效；2：二维码扫描确认中；3：登陆成功
//    property int loginsStatus : 0

    BBDownloaderController{
        id:controller

        onLoginSuccess: {
            controller.loginStatus = 3
        }

        onQrCodeExpired: {
            controller.loginStatus = 1
        }

        onScanSuccess: {
            controller.loginStatus = 2
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
                visible: controller.loginStatus === 3
                color: Theme.colorBackground

                Rectangle{
                    height: 42
                    width: parent.width
                    color:Theme.colorBackground

                    ItemImage{
                        id:avatar
                        width: 30
                        height: 30
                        round: true
                        anchors{
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            leftMargin: 6
                        }
                        source: controller.avatar
                    }

                    Text{
                        anchors{
                            verticalCenter: parent.verticalCenter
                            left: avatar.right
                            leftMargin: 6
                        }
                        color:Theme.colorFontPrimary
                        text:controller.username

                    }

                }

                Rectangle{
                    width: parent.width
                    height: 1
                    anchors{
                        top: parent.top
                        topMargin: 42
                    }
                    color:Theme.colorDivider
                }

                Item{
                    id:pannle

                    property int curIndex: 0

                    anchors{
                        top: parent.top
                        left: parent.left
                        right: parent.right
                        bottom: parent.bottom
                        topMargin: 42
                    }

                    ListModel{
                        id:sliderModel
                        ListElement{
                            name:"下载"
                            icon:"\ue603"
                            url:"qrc:/tool-bbdownloader/Download.qml"
                        }
                        ListElement{
                            name:"文件"
                            icon:"\ue602"
                            url:"qrc:/tool-bbdownloader/File.qml"
                        }
                        ListElement{
                            name:"设置"
                            icon:"\ue6c7"
                            url:"qrc:/tool-bbdownloader/Setting.qml"
                        }
                    }

                    ListView{
                        id:listView
                        boundsBehavior: Flickable.StopAtBounds
                        width: 48
                        model:sliderModel
                        height: parent.height
                        delegate: Item{
                            width: 48
                            height: 48
                            Text{
                                anchors.centerIn: parent
                                text:model.icon
                                font.family: awesome.name
                                color:pannle.curIndex === model.index ? Theme.colorPrimary : Theme.colorFontPrimary
                                font.pixelSize: 24
                            }
                            MouseArea{
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    pannle.curIndex = model.index
                                }
                            }
                        }
                    }

                    Loader{
                        id:container
                        anchors{
                            top:listView.top
                            bottom: listView.bottom
                            right: parent.right
                            left: listView.right
                        }
                        source: sliderModel.get(pannle.curIndex).url
                    }


                }


            }


            Rectangle{
                id:layoutLogin
                anchors.fill: parent
                visible: controller.loginStatus !== 3
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
                    visible: controller.loginStatus === 1

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
                                controller.loginStatus = 0
                                controller.refreshExpired()
                            }
                        }
                    }
                }

                Text{
                    text: {
                        //  "二维码已失效" : "请使用B站客户端\n扫描二维码登录"
                        switch(controller.loginStatus){
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
