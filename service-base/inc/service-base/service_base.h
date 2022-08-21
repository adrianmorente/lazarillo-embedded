#ifndef SERVICE_BASE_INC_SERVICE_BASE_H
#define SERVICE_BASE_INC_SERVICE_BASE_H

#include <string>

namespace utils
{
class ServiceBase
{
public:
  /**
   * Class destructor
   */
  ~ServiceBase();

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
  virtual void run() = 0;

  /**
   * Terminates the service. Blocks until run returns
   */
  virtual void finish() = 0;
};
}

#endif // SERVICE_BASE_INC_SERVICE_BASE_H
