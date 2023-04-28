// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2
import QtQuick.Controls 6.2
import ProtectClient
import com.abeir.protect
import "widgets"

Window {
    id: root
    minimumHeight: Constants.height
    minimumWidth: Constants.width
    maximumHeight: Constants.height
    maximumWidth: Constants.width

    visible: true
    title: "Protect"

    TitleBar {
        id: titleBar
        anchors.right: parent.right
        anchors.left: parent.left

        title: stackView.currentItem ? stackView.currentItem.title : 'Protect'
        leftButtonText: stackView.depth > 1 ? "\u25C0" : "\u2630"
        rightButtonIcon: stackView.currentItem ? stackView.currentItem.menuButtonIcon : ''
        rightButtonEnabled: stackView.currentItem ? !!stackView.currentItem.showMenuButton : false

        onLeftButtonClicked: {
            if (stackView.depth > 1) {
                stackView.pop();
                return;
            }else{
                drawer.open()
            }
        }
        onRightButtonClicked: {
            stackView.currentItem.clickMenuButton()
        }
    }


    StackView {
        id: stackView
        anchors.top: titleBar.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
    }

    DrawerMenu {
        id: drawer
        width: root.width * 0.33
        height: root.height
    }

    Component.onCompleted: {
        if(MemberManager.isLoggedIn){
            stackView.push('qrc:/content/AccountPage.qml', {"stackView": stackView});
        }else{
            stackView.push('qrc:/content/LoginPage.qml', {"stackView": stackView});
        }
    }

}
