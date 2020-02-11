// ------------------------------------------------
// File : template.h
// Date: 4-apr-2002
// Author: giles
// Desc:
//
// (c) 2002 peercast.org
// ------------------------------------------------
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// ------------------------------------------------

#ifndef _TEMPLATE2_H
#define _TEMPLATE2_H

#include <list>
#include "stream.h"
#include "picojson.h"

// HTML テンプレートシステム
class Template2
{
public:
    enum
    {
        TMPL_UNKNOWN,
        TMPL_LOOP,
        TMPL_IF,
        TMPL_ELSE,
        TMPL_ELSIF,
        TMPL_END,
        TMPL_FRAGMENT,
        TMPL_FOREACH
    };

    Template2();
    ~Template2();

    void initVariableWriters();

    bool inSelectedFragment()
    {
        if (selectedFragment.empty())
            return true;
        else
            return selectedFragment == currentFragment;
    }

    // 変数
    void    writeVariable(Stream &, const String &, int);

    // ディレクティブの実行
    int     readCmd(Stream &, Stream *, int);
    void    readIf(Stream &, Stream *, int);
    void    readLoop(Stream &, Stream *, int);
    void    readForeach(Stream &, Stream *, int);
    void    readFragment(Stream &, Stream *, int);

    void    readVariable(Stream &, Stream *, int);
    void    readVariableJavaScript(Stream &in, Stream *outp, int loop);
    void    readVariableRaw(Stream &in, Stream *outp, int loop);
    int     readTemplate(Stream &, Stream *, int);
    bool    writeObjectProperty(Stream& s, const String& varName, picojson::object object);
    picojson::array evaluateCollectionVariable(String& varName);

    bool    evalCondition(const std::string& cond, int loop);
    std::vector<std::string> tokenize(const std::string& input);
    std::pair<std::string,std::string> readStringLiteral(const std::string& input);
    std::string evalStringLiteral(const std::string& input);
    std::string getStringVariable(const std::string& varName, int loop);

    std::string selectedFragment;
    std::string currentFragment;
    picojson::value currentElement;

  picojson::object env_;
};

#endif
