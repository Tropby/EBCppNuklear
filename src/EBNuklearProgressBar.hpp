#pragma once

#include <EBNuklearWidget.hpp>
#include <EBString.hpp>
#include <EBEvent.hpp>

namespace EBCpp::Nuklear
{
    class EBNuklearProgressBar : public EBNuklearWidget
    {
    public:
        EBNuklearProgressBar()
        {
        }

        void render(struct nk_context *ctx) override
        {
            if (nk_progress(ctx, &value, maxValue, modifiable))
            {
                EB_EMIT(changed);
            }
        }

        const float getValue() const
        {
            return this->value;
        }        

        void setValue(const uint32_t value)
        {
            this->value = value;
            invalidate();
        }

        void setMaxValue(const uint32_t value)
        {
            this->maxValue = value;
            invalidate();
        }

        void setModifiable(const bool isModifiable)
        {
            if( isModifiable )
                modifiable = NK_MODIFIABLE;
            else
                modifiable = NK_FIXED;
        }

        EB_SIGNAL(changed);

    private:
        nk_size value;
        nk_size maxValue;
        nk_modify modifiable = NK_FIXED;
    };
}
