#ifndef SERVICE_BASE_INC_SERVICE_BASE_H
#define SERVICE_BASE_INC_SERVICE_BASE_H

#include <memory>
#include <string>

namespace lzr
{
namespace service
{
class ServiceBase
{
public:
    /**
     * Returns the name of the service
     */
    virtual std::string get_name() = 0;

    /**
     * Does all the initialization tasks on start
     */
    virtual void init() = 0;

    /**
     * Runs the service blocking until ending
     */
    void run();

    /**
     * Abstract run method called by @ref run(). Intended to be implemented by
     * children.
     */
    virtual int run_internal() = 0;

    /**
     * Terminates the service. Blocks until run returns
     */
    virtual void finish() = 0;

private:
    /**
     * Private method used for initializing the messaging context, used by
     * inheriting children.
     */
    void init_messaging();
};
} // namespace service
} // namespace lzr

#endif // SERVICE_BASE_INC_SERVICE_BASE_H
