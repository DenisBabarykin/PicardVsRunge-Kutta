#ifndef TIMER_H
#define TIMER_H

#include <cassert>

#ifndef __OPENCV_CORE_HPP__
    #define WINDOWS_LEAN_AND_MEAN 1
    #include <windows.h>
#endif

/*
 * Не знаю, зачем это, поэтому закомментировал
#undef min
#undef max
*/

namespace ns_timer
{

    class Frequency
    { //Класс для получения и хранения частоты таймера
    public:
        #ifndef __OPENCV_CORE_HPP__
            typedef unsigned long long Time;  // Изначально было просто long long, добавил unsigned
        #else
            typedef double Time;
        #endif

    private:
        Time v; //Частота таймера для перевода Time в секунды

        inline Frequency(Frequency const &);            //Скрытый конструктор копии
        inline Frequency &operator=(Frequency const &); //Скрытый оператор присваивания

    public:
        inline Frequency(void);  //Конструктор по-умолчанию
        inline ~Frequency(void); //Деструктор

        inline Time value(void) const;
    };

    //***********************************************************************************************************

    Frequency const frequency; //Частота таймера для перевода Time в секунды

    //***********************************************************************************************************

    class Timer
    { //Класс Timer имитирует некий счётчик времени,
      //  который можно запустить и остановить
    public:
        typedef long long Time;

    private:
        //Если true, то таймер запущен. Иначе -- нет
        bool state;

        //Сколько времени набежало за все предыдущие интервалы
        Time timeTotal;
        //Момент начала последнего, ещё незавершённого интервала (если запущен)
        Time timeLastStart;

        //Узнать текущее значение времени в "тиках"
        static inline Time now(void);

    public:
        //Конструктор по-умолчанию
        inline Timer(bool start = false);
        //Конструктор копии
        inline Timer(Timer const &T);
        //Деструктор
        inline ~Timer(void);
        //Оператор присваивания
        inline Timer &operator=(Timer const &T);

        //Узнать текущее значение таймера в секундах
        inline double get(void) const;
        //Узнать текущее значение таймера в секундах
        inline operator double(void) const;
        //Узнать текущее значение таймера в "тиках" (максимальная точность)
        inline Time getTickCount(void) const;
        //Узнать частоту таймера (число "тиков" в секунду)
        static inline Frequency::Time getFrequency(void);

        //Запустить таймер
        inline void start(bool reset = false);
        //Запустить таймер и узнать значение на момент запуска
        inline double startGet(void);

        //Пауза таймера
        inline void pause(void);
        //Пауза таймера и возврат значения
        inline double pauseGet(void);

        //Остановка таймера. Отличается от паузы обнулением счётчика
        inline void stop(void);
        //Остановка таймера. Возвращается значение на момент остановки, ДО обнуления
        inline double stopGet(void);
    };

    //***********************************************************************************************************

    inline Frequency::Frequency(void): v(0)
    { //Конструктор по-умолчанию
        #ifdef __OPENCV_CORE_HPP__
            v = cv::getTickFrequency();
        #else
            if( !QueryPerformanceFrequency( reinterpret_cast<LARGE_INTEGER *>(&v) ) ) v = 0;
        #endif
        assert( v );
    }

    inline Frequency::~Frequency(void)
    { //Деструктор
        ;
    }

    inline Frequency::Time Frequency::value(void) const
    {
        return v;
    }

    //***********************************************************************************************************

    inline Timer::Time Timer::now(void)
    { //Узнать текущее значение времени в "тиках"
        Timer::Time timeNow;
        #ifdef __OPENCV_CORE_HPP__
            timeNow = cv::getTickCount();
        #else
            BOOL const res( QueryPerformanceCounter( reinterpret_cast<LARGE_INTEGER *>(&timeNow) ) );
            assert( res );
        #endif
        return timeNow;
    }

    inline Timer::Timer(bool const startNow): state(false),
                                              timeTotal(0),
                                              timeLastStart(0)
    { //Конструктор по-умолчанию
        if(startNow) start();
    }

    inline Timer::Timer(Timer const &T): state(T.state),
                                         timeTotal(T.timeTotal),
                                         timeLastStart(T.timeLastStart)
    { //Конструктор копии
        ;
    }

    inline Timer::~Timer(void)
    { //Деструктор
        ;
    }

    inline Timer &Timer::operator=(Timer const &T)
    { //Оператор присваивания
        state         = T.state;
        timeTotal     = T.timeTotal;
        timeLastStart = T.timeLastStart;
        return *this;
    }

    inline double Timer::get(void) const
    { //Узнать текущее значение таймера в секундах
        if(state) //Таймер бежит
            return static_cast<double>( timeTotal + ( now() - timeLastStart ) ) / getFrequency();
        else //Таймер остановлен
            return static_cast<double>( timeTotal ) / getFrequency();
    }

    inline Timer::operator double(void) const
    {
        return get();
    }

    inline Timer::Time Timer::getTickCount(void) const
    { //Узнать текущее значение таймера в "тиках"
        if(state) //Таймер бежит
            return timeTotal + ( now() - timeLastStart );
        else //Таймер остановлен
            return timeTotal;
    }

    inline Frequency::Time Timer::getFrequency(void)
    { //Узнать частоту таймера (число "тиков" в секунду)
        return frequency.value();
    }

    inline void Timer::start(bool const reset)
    { //Запустить таймер
        assert( !state );
        state = true;
        if(reset) timeTotal = 0;
        timeLastStart = now(); //Запуск таймера
    }

    inline double Timer::startGet(void)
    { //Запустить таймер и узнать значение на момент запуска
        assert( !state );
        double const res( get() ); //Чтобы возвр. время совпало со временем старта, вызываю get() до старта
        state = true;
        timeLastStart = now(); //Запуск таймера
        return res;
    }

    inline void Timer::pause(void)
    { //Пауза таймера
        assert( state );
        state = false;
        timeTotal += now() - timeLastStart; //Пауза таймера
    }

    inline double Timer::pauseGet(void)
    { //Пауза таймера и возврат значения
        assert( state );
        state = false;
        timeTotal += now() - timeLastStart; //Пауза таймера
        return get();
    }

    inline void Timer::stop(void)
    { //Остановка таймера. Отличается от паузы обнулением счётчика
        assert( state );
        state = false;
        timeTotal = 0; //Остановка таймера
    }

    inline double Timer::stopGet(void)
    { //Остановка таймера. Возвращается значение на момент остановки, ДО обнуления
        assert( state );
        state = false;
        timeTotal += now() - timeLastStart; //Пауза таймера
        double const res( get() ); //Чтобы вернуть набежавшее время на момент остановки
        timeTotal = 0; //Обнуляю набежавшее время
        return res; //Возвращаю время до обнуления
    }

}

#endif // TIMER_H
