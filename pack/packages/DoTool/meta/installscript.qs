/****************************************************************************
**
** Copyright (C) 2020 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the FOO module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

function Component()
{
    installer.installationFinished.connect(this, Component.prototype.installationFinishedPageIsShown);
    installer.finishButtonClicked.connect(this, Component.prototype.installationFinished);
}

Component.prototype.createOperations = function()
{
    component.createOperations();
}

Component.prototype.installationFinishedPageIsShown = function()
{
    try {
        if (installer.isInstaller() && installer.status == QInstaller.Success) {
            installer.addWizardPageItem( component, "SettingForm", QInstaller.InstallationFinished );
        }
    } catch(e) {
        console.log(e);
    }
}

Component.prototype.installationFinished = function()
{
    try {
        if (installer.isInstaller() && installer.status == QInstaller.Success) {
            var settingForm = component.userInterface( "SettingForm" );
            if (settingForm && settingForm.startRun.checked) {
                QDesktopServices.openUrl("file:///" + installer.value("TargetDir") + "/DoTool.exe");
            }

            if (systemInfo.productType === "windows" && settingForm && settingForm.shortcut.checked) {
                component.addOperation(
                              "CreateShortcut",
                              "@TargetDir@/DoTool.exe",
                              "@StartMenuDir@/DoTool.lnk",
                              "workingDirectory=@TargetDir@",
                              "iconPath=@TargetDir@/DoTool.exe",
                              "iconId=0",
                              "description=@TargetDir@/DoTool.exe"
                              );

                component.addOperation(
                              "CreateShortcut",
                              "@TargetDir@/DoTool.exe",
                              "@HomeDir@/Desktop/DoTool.lnk",
                              "workingDirectory=@TargetDir@",
                              "iconPath=@TargetDir@/DoTool.exe",
                              "iconId=0",
                              "description=@TargetDir@/DoTool.exe");
            }
        }
    } catch(e) {
        console.log(e);
    }
}

