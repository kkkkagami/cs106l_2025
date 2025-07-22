#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

//将输入字符串分割成一组Token(标记) //Corpus是set<Token>的别名
Corpus tokenize(std::string& source) {
  
  //step1.选出指向空格的迭代器，存入向量it_space
  /*
  结合utils.cpp的find_all函数来看，find_all最后一个参数应该是一个一元谓词pred，它可以判断pred(*it)的bool值
  可以直接传入std::isspace，或者将它封装成一个可以调用的函数对象(或者lambda)
  */
  auto is_space=[] (char ch){
    return std::isspace(int(ch));
  };//写成lambda
  std::vector<std::string::iterator> it_space=find_all(source.begin(),source.end(),isspace);//is_space也可以

  //step2
  Corpus tokens;//创建tokens存储空字符迭代器之间的内容Token
  std::transform(it_space.begin(),it_space.end()-1,it_space.begin()+1,
                  std::inserter(tokens,tokens.begin()),
                  [&source](auto it1,auto it2){return Token{source,it1,it2};});
  /*
  e.g.  std::transform(first1, last1, first2, result, op);
  [first1,last1)范围内的元素作为第一个参数，first2开头的元素作为第二个参数调用op，结果保存到以result开头的范围内
  result也应该是一个迭代器类型
  std::inserter的返回值是一个插入迭代器，记录插入位置

  lambda函数需要引用捕获source，并且每个单词的首位迭代器都会被送给it1,it2，lambda函数内部调用Token的构造函数生成对象并返回

  在step2中transform的作用：用每一对前后相邻的两个元素构造一个Token并放到tokens里面存储，即将每个单词都单独提取出来
  */

  //step3.
  std::erase_if(tokens,[](const auto& token){return token.content.empty();});
  
  return tokens;
}

//根据已标记的字符串和字典来识别拼写错误的单词
std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  /* TODO: Implement this method */
  return std::set<Misspelling>();
};

/* Helper methods */

#include "utils.cpp"