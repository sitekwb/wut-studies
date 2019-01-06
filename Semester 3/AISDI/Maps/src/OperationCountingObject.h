//
// Created by Bronisław Sitek on 2019-01-02.
//

#ifndef AISDI_MAPS_HASHSPECIALISATION_H
#define AISDI_MAPS_HASHSPECIALISATION_H


#include <utility>
#include <ostream>

namespace
{

    class OperationCountingObject
    {
    public:
        OperationCountingObject(int value_ = 0)
                : value(value_)
        {
            ++constructedObjects;
        }

        OperationCountingObject(const OperationCountingObject& other)
                : value(std::move(other.value))
        {
            ++constructedObjects;
            ++copiedObjects;
        }

        OperationCountingObject(OperationCountingObject&& other)
                : value(other.value)
        {
            ++constructedObjects;
            ++movedObjects;
        }

        ~OperationCountingObject()
        {
            ++destroyedObjects;
        }

        OperationCountingObject& operator=(const OperationCountingObject& other)
        {
            ++assignedObjects;
            value = other.value;
            return *this;
        }

        OperationCountingObject& operator=(OperationCountingObject&& other)
        {
            ++assignedObjects;
            ++movedObjects;
            value = std::move(other.value);
            return *this;
        }

        operator int() const
        {
            return value;
        }

        static void resetCounters()
        {
            constructedObjects = 0;
            destroyedObjects = 0;
            copiedObjects = 0;
            movedObjects = 0;
            assignedObjects = 0;
        }

        static std::size_t constructedObjectsCount()
        {
            return constructedObjects;
        }

        static std::size_t destroyedObjectsCount()
        {
            return destroyedObjects;
        }

        static std::size_t copiedObjectsCount()
        {
            return copiedObjects;
        }

        static std::size_t movedObjectsCount()
        {
            return movedObjects;
        }

        static std::size_t assignedObjectsCount()
        {
            return assignedObjects;
        }

    private:
        int value;

        static std::size_t constructedObjects;
        static std::size_t destroyedObjects;
        static std::size_t copiedObjects;
        static std::size_t movedObjects;
        static std::size_t assignedObjects;
    };

    std::size_t OperationCountingObject::constructedObjects = 0;
    std::size_t OperationCountingObject::destroyedObjects = 0;
    std::size_t OperationCountingObject::copiedObjects = 0;
    std::size_t OperationCountingObject::movedObjects = 0;
    std::size_t OperationCountingObject::assignedObjects = 0 ;

    std::ostream& operator<<(std::ostream& out, const OperationCountingObject& obj)
    {
        return out << '<' << static_cast<int>(obj) << '>';
    }

    struct Fixture
    {
        Fixture()
        {
            OperationCountingObject::resetCounters();
        }
    };
} // namespace

namespace std{
    template <>
    struct _LIBCPP_TEMPLATE_VIS hash<OperationCountingObject>
            : public unary_function<OperationCountingObject, size_t>
    {
        _LIBCPP_INLINE_VISIBILITY
        size_t operator()(OperationCountingObject __v) const _NOEXCEPT {return static_cast<size_t>(__v);}
    };
}


#endif //AISDI_MAPS_HASHSPECIALISATION_H
