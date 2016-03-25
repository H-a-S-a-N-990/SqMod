#ifndef _LIBRARY_CHRONO_TIMER_HPP_
#define _LIBRARY_CHRONO_TIMER_HPP_

// ------------------------------------------------------------------------------------------------
#include "SqBase.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
class Timestamp;

/* ------------------------------------------------------------------------------------------------
 *
*/
class Timer
{
    /* --------------------------------------------------------------------------------------------
     *
    */
    Timer(Int64 t)
        : m_Timestamp(t)
    {
        /* ... */
    }

public:

    /* --------------------------------------------------------------------------------------------
     *
    */
    Timer();

    /* --------------------------------------------------------------------------------------------
     *
    */
    Timer(const Timer & o)
        : m_Timestamp(o.m_Timestamp)
    {
        /* ... */
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    ~Timer()
    {
        /* ... */
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    Timer & operator = (const Timer o)
    {
        m_Timestamp = o.m_Timestamp;
        return *this;
    }

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Int32 Cmp(const Timer & b) const;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    CSStr ToString() const;

    /* --------------------------------------------------------------------------------------------
     *
    */
    void Reset();

    /* --------------------------------------------------------------------------------------------
     *
    */
    Timestamp Restart();

    /* --------------------------------------------------------------------------------------------
     *
    */
    Int64 RestartRaw();

    /* --------------------------------------------------------------------------------------------
     *
    */
    Timestamp GetElapsedTime() const;

    /* --------------------------------------------------------------------------------------------
     *
    */
    Int64 GetElapsedTimeRaw() const;

private:

    // --------------------------------------------------------------------------------------------
    Int64   m_Timestamp;
};

} // Namespace:: SqMod

#endif // _LIBRARY_CHRONO_TIMER_HPP_