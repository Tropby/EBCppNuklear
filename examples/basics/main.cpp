
// Allways inclue Nuklear Implemtation first
#include <EBNuklearImplementation.hpp>

#include <EBApplication.hpp>
#include <EBNuklear.hpp>

#include <EBUtils.hpp>

#include <EBTimer.hpp>

class BasicExample : public EBCpp::EBObject<BasicExample>
{
    public:
        BasicExample()
        {
            test = EBCreate<EBCpp::Nuklear::EBNuklearWindow>(400, 400);
            test->setFont("Arial", 9);

            label = EBCreate<EBCpp::Nuklear::EBNuklearLabel>();
            label->setText("Test!");

            button = EBCreate<EBCpp::Nuklear::EBNuklearButton>();
            button->setText("Click Me");
            button->clicked.connect(this, &BasicExample::buttonClicked);

            lineEdit = EBCreate<EBCpp::Nuklear::EBNuklearLineEdit>();
            lineEdit->setText("Ein Text!");
            lineEdit->textChanged.connect(this, &BasicExample::textChanged);

            row = EBCreate<EBCpp::Nuklear::EBNuklearRow>(25, 1);
            row->addWidget(label->cast<EBCpp::Nuklear::EBNuklearWidget>());
            row->addWidget(button->cast<EBCpp::Nuklear::EBNuklearWidget>());
            row->addWidget(lineEdit.cast<EBCpp::Nuklear::EBNuklearWidget>());

            test->setCentralWidget(row->cast<EBCpp::Nuklear::EBNuklearWidget>());

            timer.timeout.connect(this, &BasicExample::timeout);
            timer.start(1000);
        }

    private:
        EBPtr<EBCpp::Nuklear::EBNuklearWindow> test;
        EBPtr<EBCpp::Nuklear::EBNuklearRow> row;
        EBPtr<EBCpp::Nuklear::EBNuklearLabel> label;
        EBPtr<EBCpp::Nuklear::EBNuklearButton> button;
        EBPtr<EBCpp::Nuklear::EBNuklearLineEdit> lineEdit;

        EBCpp::EBTimer timer;

        static inline int counter = 0;

        EB_SLOT(timeout)
        {
            EBCpp::EBString text;
            //text = "Hellorld! ";
            //text = text + EBCpp::EBUtils::intToStr(counter++);
            text = "Watched Objects: ";
            text = text + EBCpp::EBUtils::intToStr(EBCpp::EBObjectWatchBase::getCount());
            text = text + " Shared Pointer: ";
            text = text + EBCpp::EBUtils::intToStr(EBCpp::EBObjectPointerBase::getCounter());
            label->setText(text);
        }

        EB_SLOT(buttonClicked)
        {
            counter = 0;
            label->setText("");
        }

        EB_SLOT(textChanged)
        {
            label->setText(lineEdit->getText());
        }

};

EB_APPLICATION(BasicExample);
