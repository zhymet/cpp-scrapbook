//
// Created by zbook15 on 9/23/2020.
//
#include <thread>
#include <atomic>
#include <memory>
#include <functional>
#include <stdexcept>

#ifndef NTONESDK_LOOPER_HPP
#define NTONESDK_LOOPER_HPP


class gtlLooper {
private:
    std::thread m_thread_;
    std::atomic_bool m_is_running_;
    std::atomic_bool m_is_abort_requested_;

    // Shared implementation of exiting the loop-function and joining
    // to the main thread.
    void abortAndJoin()
    {
        m_is_abort_requested_.store(true);
        if (m_thread_.joinable())
        {
            m_thread_.join();
        }
    }

    // Conditionally-infinite loop doing sth. iteratively
    void runFunc()
    {
        m_is_running_.store(true);

        while (!m_is_abort_requested_.load())
        {
            try
            {
                // Do something...
            }
            catch (std::runtime_error& e)
            {
                // Some more specific
            }
            catch (...)
            {
                // Make sure that nothing leaves the thread for now...
            }
        }

        m_is_running_.store(false);
    }

public:
    gtlLooper() {

    }

    // Copy denied, Move to be implemented

    ~gtlLooper() {
        abortAndJoin(); // invoke in case the looper goes out of scope.
    };

    void stop() {
        abortAndJoin();
    }

    bool running() const
    {
        return m_is_running_.load();
    }

    // To be called, once the looper should start looping.
    bool run()
    {
        try
        {
            m_thread_ = std::thread(&gtlLooper::runFunc, this);
        }
        catch (...)
        {
            return false;
        }

        return true;
    }
};


#endif //NTONESDK_LOOPER_HPP
