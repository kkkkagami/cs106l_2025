/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

#include<random>
#include<chrono>

std::string kYourName = "Hiiragi Kagami"; // Don't forget to change this!
const std::string PATH="students.txt";//学生姓名文件

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  std::set<std::string> stu_name{};
  std::ifstream ifs(filename);
  if(ifs.is_open()){
    std::string line;//按行读取
  while(std::getline(ifs,line)){
      stu_name.insert(line);
  }

  ifs.close();
  }
  return stu_name;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */

//用于获取姓名两个首字母的函数，返回这两个字母（大写）组成的字符串
std::string get_initials(std::string name){
  std::stringstream name_ss(name);//转化为stringstream便于分开名和姓

  std::string family_name{};
  std::string given_name{};

  name_ss>>given_name>>family_name;

  const auto& it_given_name=given_name.begin();
  const auto& it_family_name=family_name.begin();

  return std::string()+*it_given_name+*it_family_name;
}

std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  const std::string my_initials=get_initials(name);//本人姓名的首字母

  std::queue<const std::string*> stu_name_queue{};
  for(auto it=students.begin();it!=students.end();++it){
    if(get_initials(*it)==my_initials){
      stu_name_queue.push(&(*it));//迭代器it不等于指针，需要解引用再取地址才能得到指针
    }
  }

  return stu_name_queue;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  if(matches.empty())
    return "NO MATCHES FOUND.";

  std::vector<const std::string*> vec{};
  while(!matches.empty()){
    vec.push_back(matches.front());
    matches.pop();
  }

  //生成随机数
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> distrubution(0,vec.size()-1);

  int rand_index=distrubution(generator);
  const std::string* rand_elem_ptr=vec[rand_index];

  return *rand_elem_ptr;
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
