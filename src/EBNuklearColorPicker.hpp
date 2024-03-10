#pragma once

#include <EBList.hpp>
#include <EBNuklearWidget.hpp>
#include <EBString.hpp>
#include <EBEvent.hpp>

namespace EBCpp::Nuklear
{
    class EBNuklearColorPicker : public EBNuklearWidget
    {
    public:
        EBNuklearColorPicker()
        {
        }

        void render(struct nk_context *ctx) override
        {    
            nk_layout_row_dynamic(ctx, 200, 1);

            nk_colorf lastColor = color;

            color = nk_color_picker(ctx, color, NK_RGBA);

            if( 
                lastColor.r != color.r ||
                lastColor.g != color.g ||
                lastColor.b != color.b ||
                lastColor.a != color.a
            )
            {
                EB_EMIT(changed);
                EB_LOG_DEBUG(color.r << " " << color.g << " " << color.b << " " << color.a);
            }
        }
      
        void setColor( uint8_t red, uint8_t green, uint8_t blue)
        {
            color.r = red / 255.0f;
            color.g = green / 255.0f;
            color.b = blue / 255.0f;
        }

        EB_SIGNAL(changed);

    private:
        nk_colorf color = {0.8f, 0.3f, 0.2f, 1.0f};
    };
}
