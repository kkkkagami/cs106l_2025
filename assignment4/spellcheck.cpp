#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  
  //step1.
  
  auto is_space=[] (char ch){
    return std::isspace(int(ch));
  };
  std::vector<std::string::iterator> it_space=find_all(source.begin(),source.end(),isspace);

  //step2
  Corpus tokens;
  std::transform(it_space.begin(),it_space.end()-1,it_space.begin()+1,
                  std::inserter(tokens,tokens.begin()),
                  [&source](auto it1,auto it2){return Token{source,it1,it2};});
  
  //step3.
  std::erase_if(tokens,[](const auto& token){return token.content.empty();});
  
  return tokens;
}


std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  namespace rv=std::ranges::views;
  
  auto view = source
    |rv::filter([&dictionary](Token token){
      return !dictionary.contains(token.content);
    })
    |rv::transform([&dictionary](Token token){
      auto similar_words=dictionary|rv::filter([&token](std::string str){
        return 1==levenshtein(token.content,str);
      });
      std::set<std::string> suggestions(similar_words.begin(),similar_words.end());
      return Misspelling{token,suggestions};
    })
    |rv::filter([](Misspelling wrong){
      return !wrong.suggestions.empty();
    })
    ;

  return std::set<Misspelling>(view.begin(),view.end());
};

/* Helper methods */

#include "utils.cpp"