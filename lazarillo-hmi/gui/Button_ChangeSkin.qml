import QtQuick 2.12
import QtQuick.Controls 2.12

import lazarillo.utils 1.0

RoundButton {
    id: changeSkinButton

    width: 50
    height: width
    flat: true
    icon.color: style.overlayColor
    icon.source: style.iconPath

    onClicked: style.changeSkin()
}
