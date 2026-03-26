import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

Window {
    id: root
    width: 1000
    height: 700
    visible: true
    title: qsTr("ptkxlord - Premium Password Manager")
    color: "#121317" // Deep Space background

    Rectangle {
        id: mainBackground
        anchors.fill: parent
        color: "transparent"

        // Animated gradient background
        Rectangle {
            id: gradientBg
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#121317" }
                GradientStop { position: 1.0; color: "#18191D" }
            }
        }

        // Sidebar
        Rectangle {
            id: sidebar
            width: 250
            height: parent.height
            color: "#18191D"
            border.color: "rgba(255, 255, 255, 0.05)"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 20

                Text {
                    text: "ptkxlord"
                    color: "#3279F9"
                    font.pixelSize: 24
                    font.weight: Font.Medium
                    Layout.alignment: Qt.AlignHCenter
                }

                // Sidebar items mockup
                Item { Layout.fillHeight: true }
            }
        }

        // Content Area
        Rectangle {
            id: contentArea
            anchors.left: sidebar.right
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            color: "transparent"

            Text {
                anchors.centerIn: parent
                text: "Welcome to ptkxlord"
                color: "#FFFFFF"
                font.pixelSize: 32
                font.weight: Font.Light
            }
        }
    }
}
