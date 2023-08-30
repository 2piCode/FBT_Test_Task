#include "amotor/amotor.h"
#include <stdexcept>

lword_t AMOTOR::TechDataSize() {
    // задайте значения для AMOTOR::TechData, 
    // или другой структуры хранящей технологические данные
    // и верните размер тех-данных в данной функции
    return 0; // return sizeof(AMOTOR::TechData);
}

AMOTOR::AMOTOR(IFunctionalBlockData& storage) 
    : AMOTOR_Base(storage)
    // инициализация технологических данных
    //, tech_data_ = *static_cast<AMOTOR::TechData*>(storage.GetTechData()) 
    { }    

AMOTOR::~AMOTOR() {

}

void AMOTOR::Init() noexcept {
    count = ud ? min : max;
}

void AMOTOR::Execute() noexcept {
    cumcount = static_cast<lint_t>(cumcount) + lint_t(1);
    if(reset && clr)
    { }
    else if(reset)
    {
        Reset();
    } else if(clr) {
        Clear();
    }
    auto mode = static_cast<lint_t>(this->mode);
    switch (mode) {
        case 0:
            continuous_execute();
            break;
        case 1:
            rising_execute();
            break;
        case 2:
            falling_execute();
            break;
    }
    auto count = static_cast<lint_t>(this->count);
    auto max = static_cast<lint_t>(this->max);
    auto min = static_cast<lint_t>(this->min);
    if(round && (count == max || count == min))
    {
        this->count = count + (max - min) * (ud ? 1 : -1);
        return;
    }

    if(count > static_cast<lint_t>(max))
    {
        lim = lint_t(1);
    }
    else if (count < static_cast<lint_t>(min))
    {
        lim = lint_t(1);
    }
}

void AMOTOR::Reset() noexcept {
    reset = false;
    pcum = cumcount;
    cumcount = lint_t(0);
    Init();
}

void AMOTOR::Clear() noexcept {
    clr = false;
    Init();
}

void AMOTOR::continuous_execute() noexcept {

    count = static_cast<lint_t>(count) + static_cast<lint_t>(delta) * static_cast<lreal_t>(qufa);
}

void AMOTOR::rising_execute() noexcept {
    if(in)
        count = static_cast<lint_t>(count) + (ud ? 1 : -1);
}

void AMOTOR::falling_execute() noexcept {
    if(!in)
        count = static_cast<lint_t>(count) + (ud ? 1 : -1);
}
