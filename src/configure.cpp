/***************************************************************************
*   Copyright (C) 2007 by BOP                                             *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/
#include <QtGui>

#include "configure.h"
#include "ssheet.h"

const bool highlightMatch_Def = true;
const bool beepSound_Def = true;
const int stepBookHitMax_Def = 10;
const int stepTotalHitMax_Def = 100;
const int maxLimitBookHit_Def = 15000;
const int maxLimitTotalHit_Def = 15000;
const int historyMax_Def = 500;
const int limitImageNum_Def = 700;
const int limitBrowserChar_Def = 1000000;
const int limitMenuHit_Def = 1000;
const int indentOffset_Def = 30;

#if defined (Q_WS_MAC)
const char* waveProcess_Def = "";
const char* mpegProcess_Def = "open";
const char* browserProcess_Def = "open";
#elif defined (Q_WS_WIN)
const char* waveProcess_Def = "";
const char* browserProcess_Def =
    "\"C:/Program Files/Internet Explorer/IEXPLORE.EXE\"";
const char* mpegProcess_Def =
    "\"C:/Program Files/Windows Media Player/wmplayer.exe\"";
#elif defined (Q_OS_LINUX)
const char* waveProcess_Def = "play";
const char* mpegProcess_Def = "";
const char* browserProcess_Def = "konqueror";
#else
const char* waveProcess_Def = "";
const char* mpegProcess_Def = "";
const char* browserProcess_Def = "";
#endif
const char* googleUrl_Def =
    "http://www.google.com/search?rls=ja-jp&ie=UTF-8&oe=UTF-8&q=";
const char* wikipediaUrl_Def = "http://ja.wikipedia.org/wiki/";
const char* userDefUrl_Def = "http://en.wikipedia.org/wiki/";

static Configure *configure_s = new Configure();

Configure *Configure::configure()
{
    return configure_s;
}

void Configure::load()
{
    QSettings conf("QOLIBRI_1_0", "EpwingConfigure");

    highlightMatch = conf.value("highlight_match", highlightMatch_Def).toBool();
    beepSound = conf.value("beep_sound", beepSound_Def).toBool();
    historyMax = conf.value("hist_max", historyMax_Def).toInt();
    waveProcess = conf.value("wave_proc", waveProcess_Def).toString();
    mpegProcess = conf.value("mpeg_proc", mpegProcess_Def).toString();
    browserProcess = conf.value("browser_proc", browserProcess_Def).toString();
    googleUrl = conf.value("google_url", googleUrl_Def).toString();
    wikipediaUrl = conf.value("wikipedia_url", wikipediaUrl_Def).toString();
    userDefUrl = conf.value("userdef_url", userDefUrl_Def).toString();
    limitImageNum = conf.value("limit_image", limitImageNum_Def).toInt();
    limitBrowserChar = conf.value("limit_char", limitBrowserChar_Def).toInt();
    limitMenuHit = conf.value("limit_menu", limitMenuHit_Def).toInt();
    indentOffset = conf.value("indent_offset", indentOffset_Def).toInt();
    maxLimitBookHit = conf.value("limt_book", maxLimitBookHit_Def).toInt();
    maxLimitTotalHit = conf.value("limit_total", maxLimitTotalHit_Def).toInt();
    stepBookHitMax = conf.value("step_book", stepBookHitMax_Def).toInt();
    stepTotalHitMax = conf.value("step_total", stepTotalHitMax_Def).toInt();
    QVariant vfont = conf.value("browser_font", qApp->font());
    browserFont = vfont.value<QFont>();
    QVariant afont = conf.value("application_font", qApp->font());
    qApp->setFont(afont.value<QFont>());

    QSettings ssheets("QOLIBRI_1_0", "EpwingStyleSheet");
    dictSheet = ssheets.value("dictionary", dictStyleSheet).toString();
    bookSheet = ssheets.value("book", bookStyleSheet).toString();
    statusBarSheet = ssheets.value("widgets1", statusBarStyleSheet).toString();
}

void Configure::save()
{
    QSettings conf("QOLIBRI_1_0", "EpwingConfigure");

    conf.setValue("hightlight_match", highlightMatch);
    conf.setValue("beep_sound", beepSound);
    conf.setValue("hist_max", historyMax);
    conf.setValue("wave_proc", waveProcess);
    conf.setValue("mpeg_proc", mpegProcess);
    conf.setValue("browser_proc", browserProcess);
    conf.setValue("google_url", googleUrl);
    conf.setValue("wikipedia_url", wikipediaUrl);
    conf.setValue("userdef_url", userDefUrl);
    conf.setValue("limit_image", limitImageNum);
    conf.setValue("limit_char", limitBrowserChar);
    conf.setValue("limit_menu", limitMenuHit);
    conf.setValue("limt_book", maxLimitBookHit);
    conf.setValue("limit_total", maxLimitTotalHit);
    conf.setValue("indent_offset", indentOffset);
    conf.setValue("step_book", stepBookHitMax);
    conf.setValue("step_total", stepTotalHitMax);
    conf.setValue("browser_font", browserFont);
    conf.setValue("application_font", qApp->font());

    QSettings ssheets("QOLIBRI_1_0", "EpwingStyleSheet");
    ssheets.setValue("dictionary", dictSheet);
    ssheets.setValue("book", bookSheet);
    ssheets.setValue("widgets1", statusBarSheet );
}

void Configure::setDefault()
{
    highlightMatch = highlightMatch_Def;
    beepSound = beepSound_Def;
    historyMax = historyMax_Def;
    waveProcess = waveProcess_Def;
    mpegProcess = mpegProcess_Def;
    browserProcess = browserProcess_Def;
    googleUrl = googleUrl_Def;
    wikipediaUrl = wikipediaUrl_Def;
    userDefUrl = userDefUrl_Def;
    limitImageNum = limitImageNum_Def;
    limitBrowserChar = limitBrowserChar_Def;
    limitMenuHit = limitMenuHit_Def;
    indentOffset = indentOffset_Def;
    maxLimitBookHit = maxLimitBookHit_Def;
    maxLimitTotalHit = maxLimitTotalHit_Def;
    stepBookHitMax = stepBookHitMax_Def;
    stepTotalHitMax = stepTotalHitMax_Def;
    browserFont = qApp->font();
}

