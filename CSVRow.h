#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class CSVRow
{
private:
    std::vector<std::string> m_data;
public:
    std::string const& operator[](std::size_t index) const;
    std::size_t size() const;
    void readNextRow(std::istream& str);
    friend std::istream& operator>>(std::istream& str, CSVRow& data);
};

class CSVIterator
{
public:
    typedef std::input_iterator_tag     iterator_category;
    typedef CSVRow                      value_type;
    typedef std::size_t                 difference_type;
    typedef CSVRow*                     pointer;
    typedef CSVRow&                     reference;

    CSVIterator(std::istream& str) :m_str(str.good() ? &str : NULL) { ++(*this); }
    CSVIterator() :m_str(NULL) {}

    // Pre Increment
    CSVIterator& operator++() { if (m_str) { if (!((*m_str) >> m_row)) { m_str = NULL; } }return *this; }
    // Post increment
    CSVIterator operator++(int) { CSVIterator    tmp(*this); ++(*this); return tmp; }
    CSVRow const& operator*()   const { return m_row; }
    CSVRow const* operator->()  const { return &m_row; }

    bool operator==(CSVIterator const& rhs) { return ((this == &rhs) || ((this->m_str == NULL) && (rhs.m_str == NULL))); }
    bool operator!=(CSVIterator const& rhs) { return !((*this) == rhs); }
private:
    std::istream* m_str;
    CSVRow m_row;
};