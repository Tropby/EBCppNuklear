#include "resource.h"

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
            window = EBCreate<EBCpp::Nuklear::EBNuklearWindow>(400, 400, "EBCpp Nuklear");
            window->setFont("Arial", 9);

            row = EBCreate<EBCpp::Nuklear::EBNuklearRow>(30, 1);
            window->setCentralWidget(row);

            label = EBCreate<EBCpp::Nuklear::EBNuklearLabel>();
            label->setText("Test!");
            row->addWidget(label);

            button = EBCreate<EBCpp::Nuklear::EBNuklearButton>();
            button->setText("Click Me");
            button->clicked.connect(this, &BasicExample::buttonClicked);
            row->addWidget(button);

            lineEdit = EBCreate<EBCpp::Nuklear::EBNuklearLineEdit>();
            lineEdit->setText("Ein Text!");
            lineEdit->textChanged.connect(this, &BasicExample::lineEditTextChanged);
            row->addWidget(lineEdit);

            checkBox = EBCreate<EBCpp::Nuklear::EBNuklearCheckbox>();
            checkBox->setText("Checkbox!");
            checkBox->changed.connect(this, &BasicExample::checkboxChanged);
            row->addWidget(checkBox);

            progressbar = EBCreate<EBCpp::Nuklear::EBNuklearProgressBar>();
            progressbar->setMaxValue(100);
            progressbar->setValue(45);
            progressbar->setModifiable(false);
            row->addWidget(progressbar);

            slider = EBCreate<EBCpp::Nuklear::EBNuklearSlider>();
            slider->setMaxValue(100);
            slider->setMinValue(0);
            slider->setValue(5);
            slider->setStep(0.1);
            slider->changed.connect(this, &BasicExample::sliderChanged);
            row->addWidget(slider);

            labelSlider = EBCreate<EBCpp::Nuklear::EBNuklearLabel>();
            row->addWidget(labelSlider);

            radioGroup = EBCreate<EBCpp::Nuklear::EBNuklearRadioGroup>();
            radioGroup->addItem("easy");
            radioGroup->addItem("hard");
            radioGroup->setCurrentIndex(0);
            row->addWidget(radioGroup);

            combobox = EBCreate<EBCpp::Nuklear::EBNuklearCombobox>();
            combobox->addItem("first");
            combobox->addItem("second");
            combobox->addItem("third");
            combobox->setCurrentIndex(0);
            row->addWidget(combobox);

            colorPicker = EBCreate<EBCpp::Nuklear::EBNuklearColorPicker>();
            colorPicker->setColor(255, 0, 0);
            row->addWidget(colorPicker);

            timer.timeout.connect(this, &BasicExample::timeout);
            timer.start(1000);
        }

    private:
        EBPtr<EBCpp::Nuklear::EBNuklearWindow> window;
        EBPtr<EBCpp::Nuklear::EBNuklearRow> row;
        EBPtr<EBCpp::Nuklear::EBNuklearLabel> label;
        EBPtr<EBCpp::Nuklear::EBNuklearButton> button;
        EBPtr<EBCpp::Nuklear::EBNuklearLineEdit> lineEdit;
        EBPtr<EBCpp::Nuklear::EBNuklearCheckbox> checkBox;
        EBPtr<EBCpp::Nuklear::EBNuklearProgressBar> progressbar;
        EBPtr<EBCpp::Nuklear::EBNuklearSlider> slider;
        EBPtr<EBCpp::Nuklear::EBNuklearLabel> labelSlider;
        EBPtr<EBCpp::Nuklear::EBNuklearRadioGroup> radioGroup;
        EBPtr<EBCpp::Nuklear::EBNuklearCombobox> combobox;
        EBPtr<EBCpp::Nuklear::EBNuklearColorPicker> colorPicker;

        EBCpp::EBTimer timer;

        EB_SLOT(sliderChanged)
        {
            labelSlider->setText("Slider Value: " + EBCpp::EBUtils::doubleToStr(slider->getValue(), 1));
            progressbar->setValue(slider->getValue());
        }

        EB_SLOT(timeout)
        {           
            EBCpp::EBString text;
            text = "Watched EBObjects: ";
            text = text + EBCpp::EBUtils::intToStr(EBCpp::EBObjectWatchBase::getCount());
            text = text + "; Shared EBPointer: ";
            text = text + EBCpp::EBUtils::intToStr(EBCpp::EBObjectPointerBase::getCounter());
            label->setText(text);
        }

        EB_SLOT(checkboxChanged)
        {            
            checkBox->setText( checkBox->getState() ? "ON" : "OFF" );
        }

        EB_SLOT(buttonClicked)
        {
            label->setText("");
        }

        EB_SLOT(lineEditTextChanged)
        {
            label->setText(lineEdit->getText());
        }

};

EB_APPLICATION(BasicExample);
