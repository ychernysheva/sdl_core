/**
 * @file Navigation.qml
 * @brief Navigation.
 * Copyright (c) 2013, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

import QtQuick 2.0
import "Common.js" as Common

Item {
    function isReady () {
        return {
            available: dataContainer.hmiNavigationAvailable
        }
    }

    function showConstantTBT(navigationTexts, turnIcon, distanceToManeuver,
                             distanceToManeuverScale, maneuverComplete,
                             softButtons, appID) {
        navigationTexts.forEach(fillTexts);
        if (turnIcon !== undefined) {
            dataContainer.navigationModel.icon = turnIcon;
        }
        dataContainer.navigationModel.distanceToManeuver = distanceToManeuver;
        dataContainer.navigationModel.distanceToManeuverScale = distanceToManeuverScale;
        if (maneuverComplete !== undefined) {
            dataContainer.navigationModel.maneuverComplete = maneuverComplete;
        }
        if (softButtons !== undefined) {
            dataContainer.navigationModel.softButtons.clear();
            softButtons.forEach(fillSoftButtons);
        }
        dataContainer.navigationModel.appId = appID;
        contentLoader.go("./views/TurnByTurnView.qml");
    }

    function alertManeuver(softButtons) {

    }

    function updateTurnList(turnList, softButtons, appID) {

    }

    function fillTexts(element, index, array) {
        switch (element.fieldName) {
        case Common.TextFieldName.navigationText1:
            dataContainer.navigationModel.text1 = element.fieldText;
            break;
        case Common.TextFieldName.navigationText2:
            dataContainer.navigationModel.text2 = element.fieldText;
            break;
        case Common.TextFieldName.ETA:
            dataContainer.navigationModel.eta = element.fieldText;
            break;
        case Common.TextFieldName.totalDistance:
            dataContainer.navigationModel.totalDistance = element.fieldText;
            break;
        }
    }

    function fillSoftButtons(element, index, array) {
        dataContainer.navigationModel.softButtons.append(
                    {
                        type: element.type,
                        name: element.text,
                        image: element.image,
                        isHighlighted: element.isHighlighted,
                        buttonId: element.softButtonID,
                        action: element.systemAction
                    });
    }
}
