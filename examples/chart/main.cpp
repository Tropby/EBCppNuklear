// Allways inclue Nuklear Implemtation first
#include <EBNuklearImplementation.hpp>

#include <EBApplication.hpp>
#include <EBNuklear.hpp>

class MinimalExample : public EBCpp::EBObject<MinimalExample>
{
    public:
        MinimalExample()
        {
            window = EBCreate<EBCpp::Nuklear::EBNuklearWindow>(400, 400, "EBCpp Nuklear");
            window->setFont("Arial", 9);

            row = EBCreate<EBCpp::Nuklear::EBNuklearRow>(200, 1);
            window->setCentralWidget(row);

            chart = EBCreate<EBCpp::Nuklear::EBNuklearChart>();
            for (int i = 0; i < 5; i++)
            {
                chart->addValue(rand() % 24);
            }
            row->addWidget(chart);
        }

    private:
        EBPtr<EBCpp::Nuklear::EBNuklearWindow> window;
        EBPtr<EBCpp::Nuklear::EBNuklearRow> row;
        EBPtr<EBCpp::Nuklear::EBNuklearChart> chart;
};

EB_APPLICATION(MinimalExample);
