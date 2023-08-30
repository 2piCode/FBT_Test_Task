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

}

void AMOTOR::Execute() noexcept {

}
