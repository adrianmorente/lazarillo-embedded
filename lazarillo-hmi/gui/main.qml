import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import Qt.labs.settings 1.0

import lazarillo.utils 1.0

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Lazarillo")

    Settings {
        property string skinType: style.type
        property color backgroundColor: style.backgroundColor
        property color overlayColor: style.overlayColor
        property string iconPath: style.iconPath
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: style.backgroundColor
    }

    Rectangle {
        id: header
        anchors {
            top: parent.top
            topMargin: -60
            horizontalCenter: parent.horizontalCenter
        }
        height: parent.height/4
        width: 250
        radius: height
        color: style.backgroundColor
        border {
            width: 2
            color: style.accentColor
        }
    }

    Button_ChangeSkin {
        id: skinButton
        anchors {
            top: parent.top
            right: parent.right
            margins: 10
        }
    }

    FooterMenu {
        id: footer
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }

    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
}
