import QtQuick 2.15
import QtQuick.Controls 2.15
import "../component"
import "../storage"
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import com.dotool.ui 1.0

CusWindow {

    id:window
    width: 600
    height: 600
    title: "OpenGL学习"

    page: CusPage{

        CusToolBar {
            id:toolBar
            title: window.title
        }

        ItemOpenGL{
            width: 100
            height: 100
            anchors.centerIn: parent
        }

    }

}
