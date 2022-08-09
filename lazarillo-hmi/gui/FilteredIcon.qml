import QtQuick 2.12
import QtGraphicalEffects 1.12

import lazarillo.utils 1.0

Item {
    id: filteredIcon

    property alias source: image.source

    Image {
        id: image
        smooth: true
    }

    ColorOverlay {
        anchors.fill: image
        source: image
        color: style.overlayColor
    }
}
