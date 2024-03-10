#pragma once

#include <EBList.hpp>
#include <EBNuklearWidget.hpp>
#include <EBString.hpp>
#include <EBEvent.hpp>

namespace EBCpp::Nuklear
{
    class EBNuklearCombobox : public EBNuklearWidget
    {
    public:
        EBNuklearCombobox()
        {
        }

        void render(struct nk_context *ctx) override
        {
            const char *itm[items.getSize()];

            for (int i = 0; i < items.getSize(); i++ )
            {
                EBString s = items.get(i);
                char *c = new char(s.length()+1);
                memcpy(c, s.dataPtr(), s.length()+1);
                itm[i] = c;
            }

            int lastIndex = currentIndex;
            nk_combobox(ctx, itm, items.getSize(), &currentIndex, 20, {width, height});

            if( lastIndex != currentIndex )
            {
                EB_EMIT(changed);
            }

            for (int i = 0; i < items.getSize(); i++ )
            {
                delete[] itm[i];
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

        void setDropdownRect(unsigned int width, unsigned int height)
        {
            this->width = width;
            this->height = height;
        }

        EB_SIGNAL(changed);

    private:
        int currentIndex = 0;
        EBList<EBString> items;
        float width = 100;
        float height = 100;
    };
}
