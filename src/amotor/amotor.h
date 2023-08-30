#pragma once

#include "amotor/amotor-base.h"

class AMOTOR : public AMOTOR_Base {
public:
    AMOTOR(IFunctionalBlockData& storage);
    virtual ~AMOTOR();
    void Init() noexcept override;
    void Execute() noexcept override;

    // размер технологических данных
    static lword_t TechDataSize();

    // структура технологических данных
    // опишите здесь или в другой структуре поля тех-данных
    // struct TechData {
    // };

private:
    // технологические данные
    // TechData& tech_data_;
};
