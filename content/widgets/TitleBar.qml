import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.2
import ProtectClient

ToolBar {

    property StackView stack

    property alias title: titleLabel.text
    property alias leftButtonText: leftButton.text
    property alias rightButtonIcon: rightButton.icon.source
    property alias rightButtonEnabled: rightButton.enabled

    property int leftButtonWidth: 30
    property int rightButtonWidth: 30

    signal leftButtonClicked
    signal rightButtonClicked

    contentHeight: leftButton.implicitHeight

    RowLayout {
        anchors.fill: parent

        ToolButton {
            id: leftButton
            font: Constants.largeFont
            Layout.preferredWidth: leftButtonWidth

            onClicked: leftButtonClicked()
        }

        Label {
            id: titleLabel
            elide: Label.ElideRight
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }

        ToolButton {
            id: rightButton
            flat: false
            display: AbstractButton.IconOnly
            font: Constants.largeFont
            Layout.preferredWidth: rightButtonWidth

            onClicked: rightButtonClicked()
        }
    }
}
