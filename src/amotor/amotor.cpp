#include "amotor/amotor.h"

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
    count = static_cast<bool_t>(ud) ? static_cast<lint_t>(max) : static_cast<lint_t>(min);
}

void AMOTOR::Execute() noexcept {
    cumcount = static_cast<lint_t>(cumcount) + lint_t{1} * static_cast<lint_t>(delta) * static_cast<lreal_t>(qufa);
    if(lim && hold)
        return;

    if(reset)
        Reset();

    if(clr)
        Clear();

    ExecuteMode();
    CheckLimits();
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

void AMOTOR::ExecuteMode() noexcept {
    auto mode = static_cast<lint_t>(this->mode);
    switch (mode) {
        case 0:
            ContinuousExecute();
            break;
        case 1:
            FrontExecute(true);
            break;
        case 2:
            FrontExecute(false);
            break;
    }
}

void AMOTOR::CheckLimits() noexcept {
    auto count = static_cast<lint_t>(this->count);
    auto max = static_cast<lint_t>(this->max);
    auto min = static_cast<lint_t>(this->min);
    if(round && (count == max || count == min))
    {
        this->count = count + (max - min) * (ud ? 1 : -1);
        return;
    }

    if(count > static_cast<lint_t>(max) || count < static_cast<lint_t>(min))
        lim = bool_t {true};
}

void AMOTOR::ContinuousExecute() noexcept {
    count = static_cast<lint_t>(count) + static_cast<lint_t>(delta) * static_cast<lreal_t>(qufa) * (ud ? -1 : 1);
}

void AMOTOR::FrontExecute(bool_t is_forward_front) noexcept {
    if(is_forward_front && !pin && in ||
        !is_forward_front && !in && pin)
        count = static_cast<lint_t>(count) + (ud ? -1 : 1) * static_cast<lreal_t>(qufa);
    pin = in;
}
