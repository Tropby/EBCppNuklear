#pragma once

#include <EBNuklearWidget.hpp>
#include <EBString.hpp>

namespace EBCpp::Nuklear
{
    class EBNuklearChart : public EBNuklearWidget
    {
        public:
            EBNuklearChart()
            {

            }

            void render(struct nk_context *ctx) override
            {
                nk_size size = values.getSize();

                float v[size];
                int i = 0;
                for(auto f : values)
                {
                    v[i++] = f;
                }

                // NK_CHART_LINES, NK_CHART_COLUMN

                nk_plot(ctx, NK_CHART_LINES, v, size, valueOffset);
            }

            void addValue(const float value)
            {
                values.append(value);
            }

            void removeValue(const int index)
            {
                values.removeAt(index);
            }

        private:
            EBCpp::EBString text;
            int valueOffset = 0;
            EBList<float> values;

    };
}
