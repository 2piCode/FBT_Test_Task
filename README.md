## Разработка функционального блока счётчика с помощью FBT

### Описание параметров
parameters:
- qufa
    * spec: set
    * type: lreal
    * default_value: 1.0
    * description: Количественный коэффицент счетчика
- round 
    * spec: set
    * type: bool 
    * default_value: 0
    * description: Циклический счетчик
- mode
    * spec: set
    * type: lint
    * default_value: 0
    * description: Рабочий режим
- in
    * spec: input
    * type: bool
    * value: 0
    * description: Вход
- pin
    * spec: set
    * type: bool
    * default_value: 0
    * description: Предыдущее значение входа
- delta
    * spec: set
    * type: lint
    * default_value: 1
    * description: Приращение в счетчике
- min
    * spec: set
    * type: lint
    * default_value: 0
    * description: Минимум
- max
    * spec: set
    * type: lint
    * default_value: 0
    * description:Максимум
- ud
    * spec: set
    * type: bool
    * default_value: 0
    * description: Направление счета (вверх/вниз)
- reset
    * spec: input
    * type: bool
    * default_value: 0
    * description: Сброс
- clr
    * spec: input
    * type: bool
    * default_value: 0
    * description: Очистить счетчик
- hold
    * spec: input
    * type: bool
    * default_value: 0
    * description: Счетчик фиксации Hold
- count
    * spec: output
    * type: lint
    * value: 0
    * description: Значение счетчика
- cumcount
    * spec: output
    * type: lint
    * value: 0
    * description: Значение накапливающего счетчика
- pcum
    * spec: output
    * type: lint
    * value: 0
    * description: Предыдущее значение накапливающего счетчика
- lim
    * spec: output
    * type: bool
    * value: 0 
    * description: Предельное значение