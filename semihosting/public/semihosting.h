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
    @file   semihosting.h
    @brief  ARM Semihosting support
 */

#include <stddef.h>
#include <stdint.h>

namespace Mark3 {

//---------------------------------------------------------------------------
/**
 * File mode flags, used for opening files with properties corresponding to the
 * ANSI standard file modes.
 */
enum class FileModeFlags : uint32_t {
    r,      // ANSI file mode "r"
    rb,     // ANSI file mode "rb"
    rp,     // ANSI file mode "r+"
    rpb,    // ANSI file mode "r+b"
    w,      // ANSI file mode "w"
    wb,     // ANSI file mode "wb"
    wp,     // ANSI file mode "w+"
    wpb,    // ANSI file mode "w+b"
    a,      // ANSI file mode "a"
    ab,     // ANSI file mode "ab"
    ap,     // ANSI file mode "a+"
    apb     // ANSI file mode "a+b"
};

//---------------------------------------------------------------------------
/**
 * Class for performing ARM semihosting calls
 */
class SemiHosting {
public:
    /**
     * @brief Open open a file in the host environment
     * @param szName_ Path of the file in the host
     * @param eFlags_ ANSI file mode flags to apply to the file
     * @return fd corresponding to the file, or -1 on error
     */
    static int32_t Open(const char* szName_, FileModeFlags eFlags_);

    /**
     * @brief Close Close a previously opened file in the host
     * @param s32Fd_ file descriptor of the file opened in the host
     * @return 0 on success, -1 on error.
     */
    static int32_t Close(int32_t s32Fd_);

    /**
     * @brief Read read data from an open file in the host
     * @param s32Fd_ file descriptor corresponding to host-side file read from
     * @param pvData_ data buffer to read into
     * @param sCount_ number of bytes to read
     * @return number of bytes read, or -1 on error
     */
    static int32_t Read(int32_t s32Fd_, const void* pvData_, size_t sCount_);

    /**
     * @brief Write write data to an open file in the host
     * @param s32Fd_ file descriptor corresponding to host-side file write from
     * @param pvData_ data buffer to write from
     * @param sCount_ number of bytes to write
     * @return number of bytes written, or -1 on error
     */
    static int32_t Write(int32_t s32Fd_, const void* pvData_, size_t sCount_);

    /**
     * @brief Exit exit from the semihosted environment.  Terminates system simulation.
     * @param u32Rc_ reason for exiting the semihosted environment.
     */
    static void Exit(uint32_t u32Rc_);
};

} // namespace Mark3
