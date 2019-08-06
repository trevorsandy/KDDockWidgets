/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KD_MULTISPLITTER_SEPARATOR_P_H
#define KD_MULTISPLITTER_SEPARATOR_P_H

#include "docks_export.h"

#include <QWidget>
#include <QPointer>

namespace KDDockWidgets {
class Anchor;

class DOCKS_EXPORT Separator : public QWidget
{
    Q_OBJECT
public:
    explicit Separator(Anchor *anchor, QWidget *parent = nullptr);
    bool isVertical() const;
    bool isStatic() const;
    int position() const;

    const Anchor *anchor() const { return m_anchor; }
    virtual void move(int p) = 0;

protected:
    void onMousePress();
    void onMouseMove(QPoint globalPos);
    void onMouseRelease();

private:
    const QPointer<Anchor> m_anchor; // QPointer so we don't dereference invalid point in paintEvent() when Anchor is deleted.
};

}

#endif