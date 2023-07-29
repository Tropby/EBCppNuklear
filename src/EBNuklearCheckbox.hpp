#pragma once

#include <EBNuklearWidget.hpp>
#include <EBString.hpp>
#include <EBEvent.hpp>

namespace EBCpp::Nuklear
{
    class EBNuklearCheckbox : public EBNuklearWidget
    {
    public:
        EBNuklearCheckbox()
        {
        }

        void render(struct nk_context *ctx) override
        {
            nk_bool lastState = state;

            nk_checkbox_label(ctx, text.dataPtr(), &state);

            if( lastState != state )
            {
                EB_EMIT(changed);
            }
        }

        void setText(const EBCpp::EBString &text)
        {
            this->text = text;
            invalidate();
        }

        void setState(const bool state)
        {
            this->state = state;
            invalidate();
        }

        bool getState() const
        {
            return state;
        }

        EB_SIGNAL(changed);

    private:
        EBCpp::EBString text;
        nk_bool state;
    };
}
