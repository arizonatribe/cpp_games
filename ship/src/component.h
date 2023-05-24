#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
  public:
    Component(class Actor* ownr, int order = 0);

    virtual ~Component();
    virtual void Update(float deltaTime);

    int GetUpdateOrder() const {
      return updateOrder;
    };

  protected:
    Actor* owner;
    int updateOrder;
};

#endif
