import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../storage"
import QtQuick.Window 2.15
import com.dotool.controller 1.0
import com.dotool.ui 1.0
import "../view"

Rectangle {

    color: Theme.colorBackground1
    anchors.fill: parent

    Text{
        text:"下载"
        anchors.centerIn: parent
        color:Theme.colorFontPrimary
    }
}
