#pragma once

#include <EBNuklearWidget.hpp>
#include <EBString.hpp>
#include <EBEvent.hpp>

namespace EBCpp::Nuklear
{
    class EBNuklearSlider : public EBNuklearWidget
    {
    public:
        EBNuklearSlider()
        {
        }

        void render(struct nk_context *ctx) override
        {
            if (nk_slider_float(ctx, minValue, &value, maxValue, step))
            {
                EB_EMIT(changed);
            }
        }
        
        const float getValue() const
        {
            return this->value;
        }

        void setValue(const float value)
        {
            this->value = value;
            invalidate();
        }

        void setMaxValue(const float value)
        {
            this->maxValue = value;
            invalidate();
        }

        void setMinValue(const float value)
        {
            this->minValue = value;
            invalidate();
        }

        void setStep(const float value)
        {
            this->step = value;
            invalidate();
        }

        EB_SIGNAL(changed);

    private:
        float value;
        float maxValue;
        float minValue;
        float step;
    };
}
