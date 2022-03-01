import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import "../view"
import "../storage"

Item {
    anchors.fill: parent


    ColumnLayout{
        anchors{
            top: parent.top
            left: parent.left
            topMargin: 24
            leftMargin: 24
        }

        Text{
            font.pixelSize: 24
            text:"DoTool"
            font.bold: true
            color:Theme.colorFontPrimary
        }

        Text{
            font.pixelSize: 12
            text:"版本：v0.0.1"
            Layout.topMargin: 20
            color:Theme.colorFontPrimary
        }
        Text{
            font.pixelSize: 12
            text:"本软件开源"
            color:Theme.colorFontPrimary
        }

        Row{
            Text{
                font.pixelSize: 12
                text:"项目链接："
                color:Theme.colorFontPrimary
            }
            Text{
                font.pixelSize: 12
                text:"Github"
                color:Theme.colorPrimary
                font.underline: true
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {

                    }
                }
            }
        }

        Text{
            font.pixelSize: 12
            text:"邮箱：524787275@qq.com"
            color:Theme.colorFontPrimary
        }

        Text{
            font.pixelSize: 12
            text:"作者严重缺钱，找一份Android或Qt兼职，有岗位的联系上面邮箱"
            color:Theme.colorFontPrimary
        }


        Text{
            font.pixelSize: 12
            text:"这个开源项目对您有帮助的话就支持一下吧，请喝杯咖啡，你敢白嫖我就敢用爱发电0-0~"
            color:Theme.colorFontPrimary
        }

        Image{
            width: 732/7
            height: 862/7
            sourceSize: Qt.size(width,height)
            fillMode: Image.PreserveAspectFit
            source: "qrc:/image/paycode.jpg"
        }

    }





}
