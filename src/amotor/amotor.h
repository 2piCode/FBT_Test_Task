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
    void Reset() noexcept;
    void Clear() noexcept;
    void ExecuteMode() noexcept;
    void ContinuousExecute() noexcept;
    void FrontExecute(bool_t) noexcept;
    void CheckLimits() noexcept;
    // технологические данные
    // TechData& tech_data_;
};
