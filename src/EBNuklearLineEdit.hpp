#pragma once

#include <EBNuklearWidget.hpp>
#include <EBString.hpp>

namespace EBCpp::Nuklear
{
    class EBNuklearLineEdit : public EBNuklearWidget
    {
        public:
            EBNuklearLineEdit(int length = 2048) : maxLength(length)
            {
                data = new char(length);
                memset(data, 0, sizeof(data));
            }

            ~EBNuklearLineEdit()
            {
                delete[] data;
            }

            void render(struct nk_context *ctx) override
            {
                int currentLength = strlen(data);
                nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, data, maxLength, 0);
                if( currentLength != strlen(data) )
                {
                    EB_EMIT(textChanged);
                }
            }

            void setText( const EBCpp::EBString & text )
            {
                if( text.length() > maxLength )
                {
                    throw new EBException("Can not set Text to EBNuklearLineEdit. Text is to long!");
                }
                memcpy(data, text.dataPtr(), text.length()+1);
                invalidate();
            }

            EBCpp::EBString getText()
            {
                return EBCpp::EBString(data);
            }

            EB_SIGNAL(textChanged);

        private:
            char * data;
            int maxLength;
    };
}
