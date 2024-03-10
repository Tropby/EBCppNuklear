#pragma once

#include <EBList.hpp>
#include <EBNuklearWidget.hpp>
#include <EBString.hpp>
#include <EBEvent.hpp>

namespace EBCpp::Nuklear
{
    class EBNuklearRadioGroup : public EBNuklearWidget
    {
    public:
        EBNuklearRadioGroup()
        {
        }

        void render(struct nk_context *ctx) override
        {
            int index = 0;
            int lastIndex = currentIndex;
            for( const auto item : items )
            {
                if( nk_option_label(ctx, item.get().dataPtr(), currentIndex == index) ) 
                {
                    currentIndex = index;
                }
                index++;
            }

            if( lastIndex != currentIndex )
            {
                EB_EMIT(changed);
            }
        }

        void addItem(const EBString &value)
        {
            items.append(value);
        }

        void removeItem(const int index)
        {
            items.removeAt(index);
        }

        void setCurrentIndex(const int index)
        {
            this->currentIndex = index;
            invalidate();
        }

        const EBString getCurrentValue() 
        {
            return items.get(currentIndex);
        }

        bool getCurrentIndex() const
        {
            return currentIndex;
        }

        EB_SIGNAL(changed);

    private:
        unsigned int currentIndex = 0;
        EBList<EBString> items;
    };
}
