#pragma once

#include <iostream>
#include <vector>

namespace ariel
{
    class MagicalContainer
    {
        std::vector<int> container;
        std::vector<int *> primeContainer;

        bool isPrime(int num);

    public:
        void addElement(int elem);
        void removeElement(int elem);
        size_t size() const;

        class Iterator
        {
            protected:
            const MagicalContainer *_mcontainer;
            size_t index;

            public:
            Iterator(const MagicalContainer &mcontainer, size_t indx = 0);
            Iterator();
            Iterator(const Iterator &other);
            ~Iterator();
            Iterator &operator=(const Iterator &other);
            bool operator==(const Iterator &other) const;
            bool operator!=(const Iterator &other) const;
            bool operator>(const Iterator &other) const;
            bool operator<(const Iterator &other) const;
        };

        class AscendingIterator : public Iterator
        {

        public:
            AscendingIterator(const MagicalContainer &mcontainer, size_t indx = 0);
            AscendingIterator();
            AscendingIterator(const AscendingIterator &other);
            ~AscendingIterator();
            int operator*() const;
            AscendingIterator &operator++();
            AscendingIterator begin();
            AscendingIterator end();
        };

        class SideCrossIterator
        {
            const MagicalContainer *_mcontainer;
            size_t _start;
            size_t _end;
            bool _reverse;
            SideCrossIterator(const MagicalContainer &mcontainer, size_t end, size_t start);

        public:
            SideCrossIterator(const MagicalContainer &mcontainer);
            SideCrossIterator();
            SideCrossIterator(const SideCrossIterator &other);
            ~SideCrossIterator();
            SideCrossIterator &operator=(const SideCrossIterator &other);
            bool operator==(const SideCrossIterator &other) const;
            bool operator!=(const SideCrossIterator &other) const;
            bool operator>(const SideCrossIterator &other) const;
            bool operator<(const SideCrossIterator &other) const;
            int operator*() const;
            SideCrossIterator &operator++();
            SideCrossIterator begin();
            SideCrossIterator end();
        };

        class PrimeIterator : public Iterator
        {
        public:
            PrimeIterator(const MagicalContainer &mcontainer, size_t indx=0);
            PrimeIterator();
            PrimeIterator(const PrimeIterator &other);
            ~PrimeIterator();
            int operator*() const;
            PrimeIterator &operator++();
            PrimeIterator begin();
            PrimeIterator end();
        };
    };
}
