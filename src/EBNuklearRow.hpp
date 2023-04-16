#pragma once

#include <profile/EBLogger.hpp>
#include <EBNuklearWidget.hpp>
#include <EBList.hpp>

namespace EBCpp::Nuklear
{
    class EBNuklearRow : public EBNuklearWidget
    {
        public:
            EBNuklearRow( int height, int columns ) : height((float)height), columns(columns)
            {

            }

            void render(struct nk_context *ctx) const override
            {
                nk_layout_row_static(ctx, height, 100, columns);

                for( const auto &w : widgets)
                {
                    w.get()->render(ctx);
                }                
            }

            void addWidget(const EBPtr<EBNuklearWidget> widget)
            {
                widget->setParent(this);
                widgets.append(widget);
            }

        private:
            float height;
            int columns;

            EBCpp::EBList< EBPtr<EBNuklearWidget> > widgets;

    };
}
