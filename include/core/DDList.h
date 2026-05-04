#pragma once

template <typename T>
class DDList
{
    private:
    int _maxSize;
    int _size;
    T** _items;

    public:
    DDList() : _maxSize{10}, _size{0}, _items{new T*[_maxSize]{}} {}
    DDList(const DDList& other) : _maxSize{other._maxSize}, _size{other._size}, _items{new T*[_maxSize]{}}
    {
        for (int i = 0; i < other._size; i++)
        {
            _items[i] = other._items[i];
        }
    }
    DDList(DDList&& other) noexcept : _maxSize{other._maxSize}, _size{other._size}, _items{other._items}
    {
        other._maxSize = 0;
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

        T** newItems = new T*[other._maxSize]{};
        for (int i = 0; i < other._size; i++)
        {
            newItems[i] = other._items[i];
        }

        delete[] _items;

        _maxSize = other._maxSize;
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

        _maxSize = other._maxSize;
        _size = other._size;
        _items = other._items;

        other._maxSize = 0;
        other._size = 0;
        other._items = nullptr;

        return *this;
    }


    void IncreaseMaxSize(int sizeIncrease)
    {
        int newMaxSize = _maxSize + sizeIncrease;
        T** newItemList = new T*[newMaxSize]{};
        for (int i = 0; i < _size; i++)
        {
            newItemList[i] = _items[i];
        }

        delete[] _items;
        _items = newItemList;
        _maxSize = newMaxSize;
    }

    void Add(T* item)
    {
        if (_size + 1 > _maxSize)
        {
            IncreaseMaxSize(_maxSize);
        }

        _items[_size++] = item;
    }
};
