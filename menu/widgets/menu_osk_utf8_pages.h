﻿/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2011-2017 - Daniel De Matteis
 *  Copyright (C) 2016-2019 - Brad Parker
 *
 *  RetroArch is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  RetroArch is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with RetroArch.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#if defined(_MSC_VER) && !defined(_XBOX) && (_MSC_VER >= 1500 && _MSC_VER < 1900)
#if (_MSC_VER >= 1700)
/* https://support.microsoft.com/en-us/kb/980263 */
#pragma execution_character_set("utf-8")
#endif
#pragma warning(disable:4566)
#endif

static const char *symbols_page1_grid[] = {
                          "1","2","3","4","5","6","7","8","9","0","Bksp",
                          "!","\"","#","$","%","&","'","*","(",")","Enter",
                          "+",",","-","~","/",":",";","=","<",">","Lower",
                          "?","@","[","\\","]","^","_","|","{","}","Next"};

static const char *uppercase_grid[] = {
                          "1","2","3","4","5","6","7","8","9","0","Bksp",
                          "Q","W","E","R","T","Y","U","I","O","P","Enter",
                          "A","S","D","F","G","H","J","K","L","+","Lower",
                          "Z","X","C","V","B","N","M"," ","_","/","Next"};

static const char *lowercase_grid[] = {
                          "1","2","3","4","5","6","7","8","9","0","Bksp",
                          "q","w","e","r","t","y","u","i","o","p","Enter",
                          "a","s","d","f","g","h","j","k","l","@","Upper",
                          "z","x","c","v","b","n","m"," ","-",".","Next"};

static const char *ninenum_grid[] = {
                          "1\nABC","2\nDEF","3\nGHI","\nBksp",
                          "4\nJKL","5\nMNO","6\nPQR","\nEnter",
                          "7\nSTU","8\nVWX","9\nYZ","\nNext"};

static const char *hiragana_page1_grid[] = {
                          "あ","い","う","え","お","ら","り","る","れ","ろ","Bksp",
                          "か","き","く","け","こ","が","ぎ","ぐ","げ","ご","Enter",
                          "さ","し","す","せ","そ","ざ","じ","ず","ぜ","ぞ","Upper",
                          "た","ち","つ","て","と","だ","ぢ","づ","で","ど","Next"};

static const char *hiragana_page2_grid[] = {
                          "な","に","ぬ","ね","の","ば","び","ぶ","べ","ぼ","Bksp",
                          "は","ひ","ふ","へ","ほ","ぱ","ぴ","ぷ","ぺ","ぽ","Enter",
                          "ま","み","む","め","も","ん","っ","ゃ","ゅ","ょ","Upper",
                          "や","ゆ","よ","わ","を","ぁ","ぃ","ぅ","ぇ","ぉ","Next"};

static const char *katakana_page1_grid[] = {
                          "ア","イ","ウ","エ","オ","ラ","リ","ル","レ","ロ","Bksp",
                          "カ","キ","ク","ケ","コ","ガ","ギ","グ","ゲ","ゴ","Enter",
                          "サ","シ","ス","セ","ソ","ザ","ジ","ズ","ゼ","ゾ","Upper",
                          "タ","チ","ツ","テ","ト","ダ","ヂ","ヅ","デ","ド","Next"};

static const char *katakana_page2_grid[] = {
                          "ナ","ニ","ヌ","ネ","ノ","バ","ビ","ブ","ベ","ボ","Bksp",
                          "ハ","ヒ","フ","ヘ","ホ","パ","ピ","プ","ペ","ポ","Enter",
                          "マ","ミ","ム","メ","モ","ン","ッ","ャ","ュ","ョ","Upper",
                          "ヤ","ユ","ヨ","ワ","ヲ","ァ","ィ","ゥ","ェ","ォ","Next"};
