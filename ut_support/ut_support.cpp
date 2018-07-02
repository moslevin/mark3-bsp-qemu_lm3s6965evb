/*===========================================================================
     _____        _____        _____        _____
 ___|    _|__  __|_    |__  __|__   |__  __| __  |__  ______
|    \  /  | ||    \      ||     |     ||  |/ /     ||___   |
|     \/   | ||     \     ||     \     ||     \     ||___   |
|__/\__/|__|_||__|\__\  __||__|\__\  __||__|\__\  __||______|
    |_____|      |_____|      |_____|      |_____|

--[Mark3 Realtime Platform]--------------------------------------------------

Copyright (c) 2018 Funkenstein Software Consulting, all rights reserved.
See license.txt for more information
===========================================================================*/
/*!
    @file   ut_support.cpp
    @brief  Unit test support for terminal output abstraction
 */

#include "mark3.h"
#include "driver.h"
#include "memutil.h"
#include "semihosting.h"
#include <string.h>

//---------------------------------------------------------------------------
using namespace Mark3;
namespace Mark3 {

// Simple device driver for outputting data via the ARM semihosting interface
class SemiHostedMonitor : public Driver
{
public:
    virtual void     Init()
    {
    }

    virtual uint8_t  Open()
    {
        return 0;
    }

    virtual uint8_t  Close()
    {
        return 0;
    }

    virtual uint16_t Read(uint16_t u16Bytes_, uint8_t* pu8Data_)
    {
        SemiHosting::Read(0, pu8Data_, u16Bytes_);
        return u16Bytes_;
    }

    virtual uint16_t Write(uint16_t u16Bytes_, uint8_t* pu8Data_)
    {
        SemiHosting::Write(1, pu8Data_, u16Bytes_);
        return u16Bytes_;
    }

    virtual uint16_t Control(uint16_t u16Event_, void* pvIn_, uint16_t u16SizeIn_, void* pvOut_, uint16_t u16SizeOut_)
    {
        return 0;
    }
};

static SemiHostedMonitor clMonitor;

namespace UnitTestSupport {
void OnInit(void)
{
    clMonitor.SetName("/dev/tty"); //!< Add the serial driver
    clMonitor.Init();

    DriverList::Add(&clMonitor);
}

void OnStart(void)
{
    clMonitor.Open();
}

void OnIdle(void)
{
    // stub
}

void OnExit(int rc)
{
    SemiHosting::Exit(rc);
}

} // namespace UnitTest
} // namespace Mark3
