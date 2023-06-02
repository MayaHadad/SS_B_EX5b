#include "MagicalContainer.hpp"
#include <algorithm>

using namespace std;

namespace ariel
{
    bool MagicalContainer::isPrime(int num)
    {
        if (num == 2)
            return true;
        if (num < 2 || num % 2 == 0)
            return false;
        for (int i = 3; i <= num / 2; i += 2)
        {
            if (num % i == 0)
                return false;
        }
        return true;
    }

    void MagicalContainer::addElement(int elem)
    {
        container.push_back(elem);
        sort(container.begin(), container.end());
        primeContainer.clear();
        for (size_t i = 0; i < container.size(); ++i)
        {
            if (isPrime(container.at(i)))
                primeContainer.push_back(&container.at(i));
        }
    }

    void MagicalContainer::removeElement(int elem)
    {
        if (!count(container.begin(), container.end(), elem))
            throw runtime_error("error ");
        container.erase(remove(container.begin(), container.end(), elem), container.end());
        if (isPrime(elem))
        {
            for (size_t i = 0; i < primeContainer.size(); ++i)
            {
                if (elem == *primeContainer.at(i))
                    remove(primeContainer.begin(), primeContainer.end(), primeContainer.at(i));
            }
        }
    }

    size_t MagicalContainer::size() const
    {
        return container.size();
    }

    // Iterator
    MagicalContainer::Iterator::Iterator(const MagicalContainer &mcontainer, size_t indx)
        : _mcontainer(&mcontainer), index(indx)
    {
    }

    MagicalContainer::Iterator::Iterator()
        : _mcontainer(nullptr), index(0)
    {
    }

    MagicalContainer::Iterator::Iterator(const Iterator &other)
        : _mcontainer(other._mcontainer), index(other.index)
    {
    }

    MagicalContainer::Iterator::~Iterator()
    {
    }

    MagicalContainer::Iterator &MagicalContainer::Iterator::operator=(const Iterator &other)
    {
        if (this->_mcontainer != other._mcontainer)
            throw runtime_error("error");
        if (this != &other)
        {
            _mcontainer = other._mcontainer;
            index = other.index;
        }
        return *this;
    }

    bool MagicalContainer::Iterator::operator==(const Iterator &other) const
    {
        return index == other.index;
    }

    bool MagicalContainer::Iterator::operator!=(const Iterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::Iterator::operator>(const Iterator &other) const
    {
        return index > other.index;
    }

    bool MagicalContainer::Iterator::operator<(const Iterator &other) const
    {
        return index < other.index;
    }

    // AscendingIterator
    MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer &mcontainer, size_t indx)
        : Iterator(mcontainer, indx)
    {
    }

    MagicalContainer::AscendingIterator::AscendingIterator()
        : Iterator()
    {
    }

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other)
        : Iterator(other)
    {
    }

    MagicalContainer::AscendingIterator::~AscendingIterator()
    {
    }

    int MagicalContainer::AscendingIterator::operator*() const
    {
        return _mcontainer->container.at(index);
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() //++i
    {
        if (index == this->end().index)
            throw runtime_error("error");
        ++index;
        return *this;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
    {
        return AscendingIterator(*_mcontainer);
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
    {
        return AscendingIterator(*_mcontainer, _mcontainer->size());
    }

    // SideCrossIterator
    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &mcontainer, size_t end, size_t start)
        : _mcontainer(&mcontainer), _start(start), _end(end), _reverse(false)
    {
    }
    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &mcontainer)
        : _mcontainer(&mcontainer), _start(0), _end(mcontainer.size() - 1), _reverse(false)
    {
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator()
        : _mcontainer(), _start(0), _end(0), _reverse(false)
    {
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other)
        : _mcontainer(other._mcontainer), _start(other._start), _end(other._end), _reverse(other._reverse)
    {
    }

    MagicalContainer::SideCrossIterator::~SideCrossIterator()
    {
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
    {
        if (this->_mcontainer != other._mcontainer)
            throw runtime_error("error");
        if (this != &other)
        {
            _mcontainer = other._mcontainer;
            _start = other._start;
            _end = other._end;
            _reverse = other._reverse;
        }
        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
    {
        return (_start == other._start && _end == other._end);
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
    {
        return _start > other._start;
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
    {
        return _start < other._start;
    }

    int MagicalContainer::SideCrossIterator::operator*() const
    {
        if (_reverse)
            return _mcontainer->container.at(_end);
        return _mcontainer->container.at(_start);
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() //++i
    {
        if (_reverse)
        {
            if (_start <= _end)
                --_end;
            else
                throw runtime_error("error");
        }
        else
        {
            if (_start <= _end)
                ++_start;
            else
                throw runtime_error("error");
        }
        _reverse = !_reverse;
        return *this;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
    {
        return SideCrossIterator(*_mcontainer);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
    {
        size_t mid = _mcontainer->size() / 2;
        if (_mcontainer->size() % 2 == 1)
            return SideCrossIterator(*_mcontainer, mid, mid + 1);
        return SideCrossIterator(*_mcontainer, mid - 1, mid);
    }

    // PrimeIterator
    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &mcontainer, size_t indx)
        : Iterator(mcontainer, indx)
    {
    }

    MagicalContainer::PrimeIterator::PrimeIterator()
        : Iterator()
    {
    }

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
        : Iterator(other)
    {
    }

    MagicalContainer::PrimeIterator::~PrimeIterator()
    {
    }

    int MagicalContainer::PrimeIterator::operator*() const
    {
        return *_mcontainer->primeContainer.at(index);
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
    {
        if (index == this->end().index)
            throw runtime_error("error");
        ++index;
        return *this;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
    {
        return PrimeIterator(*_mcontainer);
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
    {
        return PrimeIterator(*_mcontainer, _mcontainer->primeContainer.size());
    }
}