#pragma once

#include <EBNuklearWidget.hpp>
#include <EBString.hpp>

namespace EBCpp::Nuklear
{
    class EBNuklearLabel : public EBNuklearWidget
    {
        public:
            EBNuklearLabel() : alignment( NK_TEXT_ALIGN_LEFT | NK_TEXT_ALIGN_TOP )
            {

            }

            void render(struct nk_context *ctx) override
            {
                nk_label(ctx, text.dataPtr(), alignment);                                
            }

            void setText( const EBCpp::EBString & text )
            {
                this->text = text;
                invalidate();
            }

            void setAlignment( const enum nk_text_align alignment )
            {
                this->alignment = alignment;
                invalidate();
            }

        private:
            EBCpp::EBString text;
            uint32_t alignment;
    };
}
