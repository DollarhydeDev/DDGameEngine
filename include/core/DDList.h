#pragma once

template <typename T>
class DDList
{
    private:
    int _capacity;
    int _size;
    T** _items;

    public:
    DDList() : _capacity{10}, _size{0}, _items{new T*[_capacity]{}} {}
    DDList(const DDList& other) : _capacity{other._capacity}, _size{other._size}, _items{new T*[_capacity]{}}
    {
        for (int i = 0; i < other._size; i++)
        {
            _items[i] = other._items[i];
        }
    }
    DDList(DDList&& other) noexcept : _capacity{other._capacity}, _size{other._size}, _items{other._items}
    {
        other._capacity = 0;
        other._size = 0;
        other._items = nullptr;
    }
    ~DDList()
    {
        delete[] _items;
    }

    DDList& operator=(const DDList& other)
    {
        if (this == &other) return *this;

        T** newItems = new T*[other._capacity]{};
        for (int i = 0; i < other._size; i++)
        {
            newItems[i] = other._items[i];
        }

        delete[] _items;

        _capacity = other._capacity;
        _size = other._size;
        _items = newItems;

        return *this;
    }
    DDList& operator=(DDList&& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] _items;

        _capacity = other._capacity;
        _size = other._size;
        _items = other._items;

        other._capacity = 0;
        other._size = 0;
        other._items = nullptr;

        return *this;
    }

    private:
    void IncreaseMaxSize(int sizeIncrease)
    {
        if (sizeIncrease <= 0) sizeIncrease = 10;
        int newMaxSize = _capacity + sizeIncrease;
        T** newItemList = new T*[newMaxSize]{};
        for (int i = 0; i < _size; i++)
        {
            newItemList[i] = _items[i];
        }

        delete[] _items;
        _items = newItemList;
        _capacity = newMaxSize;
    }

    public:
    int Size() const
    {
        return _size;
    }

    T* GetAt(int index) const
    {
        if (index < 0 || index >= _size) return nullptr;
        return _items[index];
    }

    void Add(T* item)
    {
        if (_size + 1 > _capacity)
        {
            IncreaseMaxSize(_capacity);
        }

        _items[_size++] = item;
    }

    void Clear()
    {
        _size = 0;
    }
};
