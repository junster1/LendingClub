/*
Created on July 28, 2014

@author:     Gregory Czajkowski

@copyright:  2013 Freedom. All rights reserved.

@license:    Licensed under the Apache License 2.0 http://www.apache.org/licenses/LICENSE-2.0

@contact:    gregczajkowski at yahoo.com
*/

#ifndef __LC_WORDS_IN_DESCRIPTION_HPP__
#define __LC_WORDS_IN_DESCRIPTION_HPP__

#include <algorithm>
#include "Filter.hpp"
#include "Loan.hpp"
#include "Utilities.hpp"

namespace lc
{
template<char Remove> bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == Remove); }

class WordsInDescription : public Filter<WordsInDescription>
{
public:
    static const std::string sqlite_type;
    static const std::string csv_name;
    static const std::string name;

    WordsInDescription(const Arguments& args, unsigned* current = nullptr) : Filter<WordsInDescription>(name, args)
    {
        static const std::vector<FilterValue>* options = create_range(25, 250, 50);
        Filter::initialize(options, current);
    }

    inline FilterValue convert(const std::string& raw_data)
    {
        std::string data = raw_data;
        std::unique(data.begin(), data.end(), BothAreSpaces<' '>);
        std::unique(data.begin(), data.end(), BothAreSpaces<'\t'>);
        return std::count(data.begin(), data.end(), ' ');
    }

    const std::string get_string_value() const
    {
        return boost::lexical_cast<std::string>(get_value());
    }

    static bool static_apply(const Filter& self, const LCLoan& loan)
    {
        return (loan.desc_word_count >= self.get_value());
    }

    inline bool apply(const LCLoan& loan) const
    {
        return (loan.desc_word_count >= get_value());
    }
};

};

#endif // __LC_WORDS_IN_DESCRIPTION_HPP__