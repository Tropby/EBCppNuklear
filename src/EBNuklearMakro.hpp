#pragma once

#include "EBNuklear.hpp"

#define EB_NUKLEAR_START { \
    EBPtr<EBCpp::Nuklear::EBNuklearWidget> currentWidget;

#define EB_NUKLEAR_WINDOW currentWidget = EBCreate<EBCpp::Nuklear::EBNuklearWindow>(400, 400);

#define EB_NUKLEAR_END }
