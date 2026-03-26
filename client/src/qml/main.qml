import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

Window {
    id: window
    width: 1000
    height: 700
    visible: true
    title: qsTr("ptkxlord - Premium Password Manager")
    color: "#121317"

    // Custom Font Loading Mockup (Assume Google Sans Flex is available)
    font.family: "Google Sans Flex"

    // Background Layer
    Rectangle {
        id: mainBg
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#121317" }
            GradientStop { position: 1.0; color: "#18191D" }
        }

        // Animated subtle glow (Antigravity style)
        Rectangle {
            id: accentGlow
            width: 400; height: 400
            radius: 200
            color: "rgba(50, 121, 249, 0.05)"
            x: parent.width * 0.7; y: -100
            scale: 1.5
            
            SequentialAnimation on opacity {
                loops: Animation.Infinite
                NumberAnimation { from: 0.2; to: 0.5; duration: 4000; easing.type: Easing.InOutQuad }
                NumberAnimation { from: 0.5; to: 0.2; duration: 4000; easing.type: Easing.InOutQuad }
            }
        }
    }

    // Main Layout
    RowLayout {
        anchors.fill: parent
        spacing: 0

        // Sidebar (Glassmorphism)
        Rectangle {
            id: sidebar
            Layout.fillHeight: true
            Layout.preferredWidth: 260
            color: "rgba(24, 25, 29, 0.7)"
            border.color: "rgba(255, 255, 255, 0.05)"
            
            // Blur effect simulation (requires MultiEffect or similar in Qt 6)
            /*
            MultiEffect {
                anchors.fill: parent
                source: sidebar
                blurEnabled: true
                blur: 0.5
            }
            */

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 32

                // Logo
                RowLayout {
                    spacing: 12
                    Rectangle {
                        width: 32; height: 32; radius: 8
                        color: "#3279F9"
                        Text { anchors.centerIn: parent; text: "P"; color: "white"; font.bold: true }
                    }
                    Text {
                        text: "ptkxlord"
                        color: "white"
                        font.pixelSize: 20
                        font.weight: Font.Medium
                    }
                }

                // Navigation
                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 8
                    
                    Repeater {
                        model: ["Усі записи", "Генератор", "Налаштування"]
                        delegate: ItemDelegate {
                            Layout.fillWidth: true
                            text: modelData
                            font.pixelSize: 14
                            palette.text: index === 0 ? "white" : "#88898C"
                            background: Rectangle {
                                color: highlighted ? "rgba(255, 255, 255, 0.05)" : "transparent"
                                radius: 8
                            }
                        }
                    }
                }

                Item { Layout.fillHeight: true }

                // Lock Button
                Button {
                    Layout.fillWidth: true
                    text: "Заблокувати"
                    flat: true
                    onClicked: vaultManager.lockVault()
                    contentItem: Text {
                        text: parent.text
                        color: "#FF4D4D"
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
            }
        }

        // Secondary List View Area
        Rectangle {
            id: listArea
            Layout.fillHeight: true
            Layout.preferredWidth: 340
            color: "transparent"
            border.color: "rgba(255, 255, 255, 0.03)"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                
                Text {
                    text: "Записи"
                    color: "white"
                    font.pixelSize: 24
                    font.weight: Font.Medium
                }

                TextField {
                    Layout.fillWidth: true
                    placeholderText: "Пошук..."
                    color: "white"
                    background: Rectangle {
                        color: "#212226"
                        radius: 12
                        border.color: parent.activeFocus ? "#3279F9" : "transparent"
                    }
                }

                ListView {
                    id: entryList
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    spacing: 12
                    clip: true
                    model: vaultManager.isLocked ? 0 : 5 // Mockup logic

                    delegate: Rectangle {
                        width: parent.width; height: 70
                        radius: 16
                        color: "#18191D"
                        border.color: "rgba(255, 255, 255, 0.05)"

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 16
                            spacing: 12
                            
                            Rectangle {
                                width: 38; height: 38; radius: 10
                                color: "#2F3034"
                                Text { anchors.centerIn: parent; text: modelData ? modelData[0] : "G"; color: "#3279F9" }
                            }

                            ColumnLayout {
                                spacing: 2
                                Text { text: "Google Account"; color: "white"; font.pixelSize: 14; font.weight: Font.Medium }
                                Text { text: "user@gmail.com"; color: "#88898C"; font.pixelSize: 12 }
                            }
                        }
                        
                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: parent.color = "#2F3034"
                            onExited: parent.color = "#18191D"
                        }
                    }
                }
            }
        }

        // Content / Detail Area
        Rectangle {
            id: detailArea
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "transparent"

            ColumnLayout {
                anchors.centerIn: parent
                spacing: 16
                visible: vaultManager.isLocked

                Text {
                    text: "Ваше сховище заблоковано"
                    color: "white"
                    font.pixelSize: 20
                }

                Button {
                    text: "Розблокувати"
                    onClicked: stackView.push(loginView)
                    // Custom style here...
                }
            }
            
            // Content when unlocked mockup
            Text {
                visible: !vaultManager.isLocked
                anchors.centerIn: parent
                text: "Виберіть запис для перегляду деталей"
                color: "#45474D"
            }
        }
    }

    // Transitions
    onVisibleChanged: {
        if (visible) revealAnim.start()
    }

    SequentialAnimation {
        id: revealAnim
        NumberAnimation { target: window; property: "opacity"; from: 0; to: 1; duration: 800; easing.type: Easing.OutExpo }
    }
}
