#pragma once

#include <EBNuklearWidget.hpp>
#include <EBString.hpp>
#include <EBEvent.hpp>

namespace EBCpp::Nuklear
{
    class EBNuklearButton : public EBNuklearWidget
    {
    public:
        EBNuklearButton()
        {
        }

        void render(struct nk_context *ctx) override
        {
            if (nk_button_label(ctx, text.dataPtr()))
            {
                EB_EMIT(clicked);
            }
        }

        void setText(const EBCpp::EBString &text)
        {
            this->text = text;
            invalidate();
        }

        EB_SIGNAL(clicked);

    private:
        EBCpp::EBString text;
    };
}
