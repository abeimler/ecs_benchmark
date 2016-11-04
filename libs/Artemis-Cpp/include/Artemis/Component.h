#ifndef COMPONENT_H
#define COMPONENT_H

namespace artemis {
  /**
   * A tag class. All components in the system must extend this class.
   */
  class Component {
  public:
    virtual ~Component() = 0;
  protected:
    Component() {};
  };
  
};

#endif
