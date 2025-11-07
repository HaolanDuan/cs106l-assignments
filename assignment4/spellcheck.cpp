#include "spellcheck.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <set>
#include <utility>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  auto space_its = find_all(source.begin(), source.end(), [](unsigned char ch) {
    return std::isspace(ch);
  });

  Corpus tokens;
  std::transform(space_its.begin(), space_its.end() - 1, space_its.begin() + 1, 
                 std::inserter(tokens, tokens.end()), [&source](auto first, auto second)
                {return Token{source, first, second};});
  std::erase_if(tokens, [](const Token& token) {return token.content.empty();});
  return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  namespace rv = std::ranges::views;

  auto misspellings_view = source | rv::filter([&dictionary](const Token& token) {
                           return !token.content.empty() && !dictionary.contains(token.content);
                         })
                           | rv::transform([&dictionary](const Token& token) {
                               auto suggestions_view = dictionary | rv::filter([&token](const auto& word) {
                                                         return levenshtein(token.content, word) == 1;
                                                       });
                               std::set<std::string> suggestions(suggestions_view.begin(),
                                                                  suggestions_view.end());
                               return Misspelling{token, std::move(suggestions)};
                             })
                           | rv::filter([](const Misspelling& misspelling) {
                               return !misspelling.suggestions.empty();
                             });

  return std::set<Misspelling>(misspellings_view.begin(), misspellings_view.end());
};

/* Helper methods */

#include "utils.cpp"