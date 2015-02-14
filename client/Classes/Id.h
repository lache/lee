#ifndef __Id_H__
#define __Id_H__

enum class IdType
{
    Lane, Vehicle, Fighter, Stage
};

template <IdType IdTypeValue, typename ValueType>
class Id
{
public:
    typedef Id<IdTypeValue, ValueType> ConcreteType;

    Id() {}
    explicit Id(ValueType&& value) : _value(value) {}
    explicit Id(const ValueType& value) : _value(value) {}
    ValueType GetValue() const { return _value; }

    bool operator == (const ConcreteType& other) const
    {
        return GetValue() == other.GetValue();
    }

    bool operator < (const ConcreteType& other) const
    {
        return GetValue() < other.GetValue();
    }

    ValueType _value;
};

#endif
