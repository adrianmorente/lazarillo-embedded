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
  std::string get_name();

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

protected:
  // Unique name of the service
  std::string m_name{""};

private:
  /**
   * Private method used for initializing the messaging context, used by 
   * inheriting children. 
   */
  void init_messaging();
};
}

#endif // SERVICE_BASE_INC_SERVICE_BASE_H
