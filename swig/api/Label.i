%module ilixi_Label

%import(module="ilixi_Widget") <ui/Widget.h>
%import(module="ilixi_TextBase") <ui/TextBase.h>
%import(module="ilixi_Margin") <types/Margin.h>
%import(module="ilixi_Font") <types/Font.h>
%import(module="ilixi_Size") <types/Size.h>

%include "std_string.i"

%{
#include <ilixiGUI.h>
using namespace ilixi;
%}

%include <ui/Label.h>

%extend ilixi::Label {
  void setFont(ilixi::Font* font)
  {
    $self->setFont(font);
  }
}

%extend ilixi::Label {
  void setText(std::string text)
  {
    $self->setText(text);
  }
}