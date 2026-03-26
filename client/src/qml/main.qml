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

    // API & Vault Connections
    Connections {
        target: apiClient
        function onLoginSuccess(token) {
            loginOverlay.visible = false
            errorText.text = ""
        }
        function onErrorOccurred(message) {
            errorText.text = message
        }
    }

    Connections {
        target: vaultManager
        function onVaultOpened() {
            // Success
        }
        function onVaultError(message) {
            errorText.text = message
        }
    }

    Connections {
        target: authServer
        function onTokenReceived(token) {
            apiClient.setUserToken(token)
            loginOverlay.visible = false
        }
    }

    // Background Glow
    Rectangle {
        anchors.fill: parent
        color: "transparent"
        Rectangle {
            width: 400; height: 400; radius: 200
            color: "#0D3279F9" // 0.05 alpha
            x: parent.width * 0.7; y: -100; scale: 1.5
            SequentialAnimation on opacity {
                loops: Animation.Infinite
                NumberAnimation { from: 0.2; to: 0.5; duration: 4000; easing.type: Easing.InOutQuad }
                NumberAnimation { from: 0.5; to: 0.2; duration: 4000; easing.type: Easing.InOutQuad }
            }
        }
    }

    // Main App Layout (Visible only when unlocked or authenticated via browser)
    RowLayout {
        anchors.fill: parent
        spacing: 0
        visible: !loginOverlay.visible

        // Sidebar
        Rectangle {
            Layout.fillHeight: true
            Layout.preferredWidth: 260
            color: "#D918191D" // 0.85 alpha
            border.color: "#14FFFFFF" // 0.08 alpha
            
            // Premium background gradient
            layer.enabled: true
            layer.effect: MultiEffect {
                blurEnabled: true
                blur: 1.0
                brightness: 0.1
            }

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 32

                RowLayout {
                    spacing: 12
                    Rectangle { width: 32; height: 32; radius: 8; color: "#3279F9"
                        Text { anchors.centerIn: parent; text: "P"; color: "white"; font.bold: true }
                    }
                    Text { text: "ptkxlord"; color: "white"; font.pixelSize: 20; font.weight: Font.Medium }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 8
                    Repeater {
                        model: ["Усі записи", "Генератор", "Налаштування"]
                        delegate: ItemDelegate {
                            id: navItem
                            Layout.fillWidth: true
                            text: modelData
                            palette.text: index === 0 ? "white" : "#88898C"
                            
                            background: Rectangle {
                                id: navBg
                                color: navItem.hovered ? "#0DFFFFFF" : "transparent"
                                radius: 8
                                
                                Rectangle {
                                    id: glow
                                    width: 100; height: 100; radius: 50
                                    color: "#1A3279F9" // 0.1 alpha
                                    visible: navItem.hovered
                                    x: -50; y: -50 // Mockup magnetic offset logic
                                }
                            }
                            
                            Behavior on palette.text { ColorAnimation { duration: 200 } }
                        }
                    }
                }

                Item { Layout.fillHeight: true }

                Button {
                    Layout.fillWidth: true
                    text: "Заблокувати"
                    onClicked: vaultManager.lockVault()
                    contentItem: Text { text: parent.text; color: "#FF4D4D"; horizontalAlignment: Text.AlignHCenter }
                    background: Rectangle { color: "transparent" }
                }
            }
        }

        // List Area
        Rectangle {
            Layout.fillHeight: true
            Layout.preferredWidth: 340
            color: "transparent"
            border.color: "#08FFFFFF" // 0.03 alpha

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                Text { text: "Записи"; color: "white"; font.pixelSize: 24; font.weight: Font.Medium }
                TextField {
                    id: searchField
                    Layout.fillWidth: true; placeholderText: "Пошук..."
                    background: Rectangle { color: "#212226"; radius: 12 }
                }
                ListView {
                    id: entryListView
                    Layout.fillHeight: true; Layout.fillWidth: true; spacing: 12
                    model: 3
                    delegate: Rectangle {
                        id: entryDelegate
                        width: parent.width; height: 70; radius: 16; color: "#18191D"
                        opacity: 0
                        
                        Component.onCompleted: entryAnimator.start()
                        
                        OpacityAnimator {
                            id: entryAnimator
                            target: entryDelegate
                            from: 0
                            to: 1
                            duration: 400
                            easing.type: Easing.OutCubic
                        }

                        RowLayout {
                            anchors.fill: parent; anchors.margins: 16
                            Rectangle { width: 38; height: 38; radius: 10; color: "#2F3034"; Text { anchors.centerIn: parent; text: "G"; color: "#3279F9" } }
                            ColumnLayout { spacing: 2
                                Text { text: "Google"; color: "white"; font.pixelSize: 14 }
                                Text { text: "user@gmail.com"; color: "#88898C"; font.pixelSize: 12 }
                            }
                        }
                        MouseArea { 
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: entryDelegate.color = "#212226"
                            onExited: entryDelegate.color = "#18191D"
                            onClicked: clipboard.setClipboardText("password123") 
                        }
                    }
                }
            }
        }

        // Detail Area
        Rectangle { Layout.fillHeight: true; Layout.fillWidth: true; color: "transparent"
            Text { anchors.centerIn: parent; text: "Виберіть запис для перегляду"; color: "#45474D" }
        }
    }

    // Login Overlay (Glassmorphism)
    Rectangle {
        id: loginOverlay
        anchors.fill: parent
        color: "#E6121317" // 0.9 alpha
        visible: vaultManager.isLocked

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 24
            width: 320

            Text { text: "ptkxlord"; color: "#3279F9"; font.pixelSize: 32; font.weight: Font.Bold; Layout.alignment: Qt.AlignHCenter }

            ColumnLayout {
                spacing: 12; Layout.fillWidth: true
                TextField { id: emailInput; Layout.fillWidth: true; placeholderText: "Електронна пошта"; color: "white"
                    background: Rectangle { color: "#212226"; radius: 12; border.color: parent.activeFocus ? "#3279F9" : "transparent" } }
                TextField { id: passInput; Layout.fillWidth: true; placeholderText: "Майстер-пароль"; echoMode: TextField.Password; color: "white"
                    background: Rectangle { color: "#212226"; radius: 12; border.color: parent.activeFocus ? "#3279F9" : "transparent" } }
            }

            Text { id: errorText; color: "#FF4D4D"; font.pixelSize: 12; Layout.alignment: Qt.AlignHCenter; wrapMode: Text.WordWrap; Layout.fillWidth: true }

            Button {
                Layout.fillWidth: true; text: "Увійти"
                onClicked: {
                    if (vaultManager.openVault("vault.db", passInput.text)) {
                        apiClient.login(emailInput.text, passInput.text)
                    }
                }
                background: Rectangle { color: "#3279F9"; radius: 12 }
                contentItem: Text { text: parent.text; color: "white"; horizontalAlignment: Text.AlignHCenter; font.weight: Font.Medium }
            }
            
            Button {
                Layout.fillWidth: true; text: "Створити нове сховище"
                flat: true; onClicked: vaultManager.createVault("vault.db", passInput.text)
                contentItem: Text { text: parent.text; color: "#88898C"; horizontalAlignment: Text.AlignHCenter }
            }

            Rectangle { Layout.fillWidth: true; height: 1; color: "#0DFFFFFF" }

            Button {
                Layout.fillWidth: true; text: "Увійти через браузер"
                onClicked: {
                    authServer.startServer(5050)
                    Qt.openUrlExternally("http://localhost:5173")
                }
                background: Rectangle { color: "#1A3279F9"; radius: 12; border.color: "#4D3279F9" }
                contentItem: Text { text: parent.text; color: "#3279F9"; horizontalAlignment: Text.AlignHCenter; font.weight: Font.Medium }
            }
        }
    }
}
