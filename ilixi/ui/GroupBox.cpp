/*
 Copyright 2010-2012 Tarik Sekmen.

 All Rights Reserved.

 Written by Tarik Sekmen <tarik@ilixi.org>.

 This file is part of ilixi.

 ilixi is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 ilixi is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with ilixi.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <ui/GroupBox.h>
#include <graphics/Painter.h>
#include <types/Font.h>
#include <core/Logger.h>

namespace ilixi
{

D_DEBUG_DOMAIN( ILX_GROUPBOX, "ilixi/ui/GroupBox", "GroupBox");

GroupBox::GroupBox(std::string title, Widget* parent)
        : Frame(parent),
          _title(new Label(""))
{
    ILOG_TRACE_W(ILX_GROUPBOX);
    setConstraints(MinimumConstraint, MinimumConstraint);
    _title->setFont(stylist()->defaultFont(StyleHint::TitleFont));
    _title->setSingleLine(true);
    setTitle(title);
    setMargin(5);
    addChild(_title);
}

GroupBox::~GroupBox()
{
    ILOG_TRACE_W(ILX_GROUPBOX);
}

int
GroupBox::heightForWidth(int width) const
{
    ILOG_TRACE_W(ILX_GROUPBOX);
    return _layout->heightForWidth(
            width - _margin.hSum()
                    - stylist()->defaultParameter(StyleHint::FrameOffsetLR))
            + stylist()->defaultParameter(StyleHint::FrameOffsetTB)
            + _titleSize.height();
}

Size
GroupBox::preferredSize() const
{
    ILOG_TRACE_W(ILX_GROUPBOX);
    Size s = _layout->preferredSize();
    return Size(
            std::max(s.width(), _titleSize.width()) + _margin.hSum()
                    + stylist()->defaultParameter(StyleHint::FrameOffsetLR),
            s.height() + _margin.vSum()
                    + stylist()->defaultParameter(StyleHint::FrameOffsetTB)
                    + _titleSize.height());
}

std::string
GroupBox::title() const
{
    return _title->text();
}

Size
GroupBox::titleSize() const
{
    return _titleSize;
}

void
GroupBox::setTitle(std::string title)
{
    if (_title->text() != title)
    {
        _title->setText(title);
        Size s = _title->preferredSize();
        _titleSize.setWidth(
                s.width()
                        + stylist()->defaultParameter(StyleHint::TabOffsetLR));
        _titleSize.setHeight(
                s.height()
                        + stylist()->defaultParameter(StyleHint::TabOffsetTop));
        update();
    }
}

void
GroupBox::compose(const PaintEvent& event)
{
    Painter painter(this);
    painter.begin(event);
    stylist()->drawGroupBox(&painter, this);
    painter.end();
}

int
GroupBox::canvasY() const
{
    return _margin.top()
            + stylist()->defaultParameter(StyleHint::FrameOffsetTop)
            + _titleSize.height();
}

int
GroupBox::canvasHeight() const
{
    return height() - _margin.vSum() - _titleSize.height()
            - stylist()->defaultParameter(StyleHint::FrameOffsetTB);
}

void
GroupBox::updateLayoutGeometry()
{
    ILOG_TRACE_W(ILX_GROUPBOX);
    ILOG_DEBUG(
            ILX_GROUPBOX,
            " -> Canvas(%d, %d, %d, %d)\n", canvasX(), canvasY(), canvasWidth(), canvasHeight());
    Size s = _title->preferredSize();
    _title->setGeometry(
            2 * stylist()->defaultParameter(StyleHint::TabOffsetLeft),
            stylist()->defaultParameter(StyleHint::TabOffsetTop), s.width(),
            s.height());
    _layout->setGeometry(canvasX(), canvasY(), canvasWidth(), canvasHeight());
}

} /* namespace ilixi */