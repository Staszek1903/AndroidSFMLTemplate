#include "component.h"

//size_t BaseComponent::base_id = 1;

//BaseComponent::BaseComponent()
//    :data(nullptr), size(0)
//{;}

//BaseComponent::BaseComponent(const BaseComponent & other)
//    :BaseComponent( static_cast<uint8_t*> (other.getDataPtr()), other.getDataSize())
//{
//	Console::get()<<"base copy_constructor\n";
//}

//BaseComponent & BaseComponent::operator= (const BaseComponent & other)
//{
//    size = other.getDataSize();
//    data = static_cast<uint8_t*>(other.getDataPtr());
    
//    Console::get()<<"base copy operator\n";
//    return *this;
//}

//BaseComponent::BaseComponent(uint8_t *data, size_t size)
//    : data(data),size(size)
//{;}

//BaseComponent::~BaseComponent()
//{}

//void *BaseComponent::getDataPtr() const
//{
//    return static_cast<void*>(data);
//}

//size_t BaseComponent::getDataSize() const
//{
//    return size;
//}

//void BaseComponent::release()
//{
//    throw std::runtime_error("Component::release not available yet\n");
//}

//void BaseComponent::allocate(ComponentManager &manager, size_t entity_id, size_t component_id)
//{
//    if(size == 0) throw std::runtime_error("cannot allocate component of size 0\n");
//    manager.allocate_id_container(component_id, size);

//    void * data_temp = manager.allocate_new_component(entity_id, component_id);
//    data = static_cast<uint8_t*>(data_temp);
//}

stuff::TypeID stuff::getNewComponentTypeID()
{
    static stuff:: TypeID idCounter = 0;
    if(idCounter > stuff::MAX_COMPONENT_TYPE_ID)
        throw std::runtime_error("component type counts exceed MAX_COMPONENT_TYPE_ID<"
                                 +std::to_string(stuff::MAX_COMPONENT_TYPE_ID));
    return idCounter++;
}
