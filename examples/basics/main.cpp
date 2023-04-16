

// Allways inclue Nuklear Implemtation first
#include <EBNuklearImplementation.hpp>

#include <EBApplication.hpp>
#include <EBNuklearWindow.hpp>

#include <EBNuklearLabel.hpp>
#include <EBNuklearRow.hpp>

#include <EBTimer.hpp>

class BasicExample : public EBCpp::EBObject<BasicExample>
{
    public:
        BasicExample()
        {
            test = EBCreate<EBCpp::Nuklear::EBNuklearWindow>(400, 400);

            row = EBCreate<EBCpp::Nuklear::EBNuklearRow>(22, 1);
            label = EBCreate<EBCpp::Nuklear::EBNuklearLabel>();

            label->setText("Test!");

            row->addWidget(label->cast<EBCpp::Nuklear::EBNuklearWidget>());
            test->setCentralWidget(row->cast<EBCpp::Nuklear::EBNuklearWidget>());

            timer.timeout.connect(this, &BasicExample::timeout);
            timer.start(1000);
        }

    private:
        EBPtr<EBCpp::Nuklear::EBNuklearWindow> test;
        EBPtr<EBCpp::Nuklear::EBNuklearRow> row;
        EBPtr<EBCpp::Nuklear::EBNuklearLabel> label;

        EBCpp::EBTimer timer;

        EB_SLOT(timeout)
        {
            static int i = 0;

            EBCpp::EBString text;
            text = "Hellorld! ";
            text = text + EBCpp::EBUtils::intToStr(i++);
            label->setText(text);
        }
};

EB_APPLICATION(BasicExample);
