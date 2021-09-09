import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: root
    width: 1000
    height: 750
    maximumWidth: width
    maximumHeight: height
    minimumHeight: maximumHeight
    minimumWidth: maximumWidth
    visible: true
    title: qsTr("StellarLINK")

    Field {
        id: field
    }

}
