/*
 * CS106L Assignment 1: SimpleEnroll
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 *
 * Welcome to Assignment 1 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 * Students must implement: parse_csv, write_courses_offered,
 * write_courses_not_offered
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::string COURSES_OFFERED_PATH = "student_output/courses_offered.csv";
const std::string COURSES_NOT_OFFERED_PATH = "student_output/courses_not_offered.csv";

/**
 * Represents a course a student can take in ExploreCourses.
 * You must fill in the types of the fields in this struct.
 * Hint: Remember what types C++ streams work with?!
 */
struct Course {
  std::string title;
  std::string number_of_units;
  std::string quarter;
  //全都用string，后面用streams处理
};

/**
 * (STUDENT TODO) Look at how the main function (at the bottom of this file)
 * calls `parse_csv`, `write_courses_offered`, and `write_courses_not_offered`.
 * Modify the signatures of these functions so that they work as intended, and then delete this
 * comment!
 */

/**
 * Note:
 * We need to #include utils.cpp _after_ we declare the Course struct above
 * so that the code inside utils.cpp knows what a Course is.
 * Recall that #include literally copies and pastes file contents.
 */
#include "utils.cpp"

/**
 * This function should populate the `courses` vector with structs of type
 * `Course`. We want to create these structs with the records in the courses.csv
 * file, where each line is a record!
 *
 * Hints:
 * 1) Take a look at the split function we provide in utils.cpp
 * 2) Each LINE is a record! *this is important, so we're saying it again :>)*
 * 3) The first line in the CSV defines the column names, so you can ignore it!(第一行不要
 *
 * @param filename The name of the file to parse.
 * @param courses  A vector of courses to populate.
 */
void parse_csv(std::string filename, std::vector<Course>& courses) {//courses要改成引用类型，否则无法修改实际值
  /* (STUDENT TODO) Your code goes here... */
  std::ifstream ifs(filename);
  if(ifs.is_open()){
    std::string line;
    std::getline(ifs,line);
    //第一行丢弃
    while(std::getline(ifs,line)){
      std::vector vec=split(line,',');
      courses.push_back({vec[0],vec[1],vec[2]});
    }
  }
  ifs.close();
}

/**
 * This function has TWO requirements.
 *
 * 1) Write the courses that are offered to the file
 * "student_output/courses_offered.csv"
 *
 * 2) Delete the courses that are offered from the `all_courses` vector.
 * IMPORTANT: do this after you write out to the file!
 *
 * HINTS:
 * 1) Keep track of the classes that you need to delete!
 * 2) Use the delete_elem_from_vector function we give you!
 * 3) Remember to write the CSV column headers at the beginning of the output!
 *    See courses.csv for reference.
 *
 * @param all_courses A vector of all courses gotten by calling `parse_csv`.
 *                    This vector will be modified by removing all offered courses.
 */
void write_courses_offered(std::vector<Course> all_courses) {
  /* (STUDENT TODO) Your code goes here... */
  std::ofstream ofs(COURSES_OFFERED_PATH);
  if(ofs.is_open()){
    ofs<<"Title,Number of Units,Quarter"<<std::endl;//写标题
    std::vector<Course> courses_null_queater;//存储quarter为null的course
    for(const auto& course:all_courses){
      //cpp17:结构化绑定.自动推断类型，并将向量course里的相应成员元素赋值给中括号里的变量
      auto [title,units,quarter]=course;
      if(quarter!="null")
        ofs<<title<<","<<units<<","<<quarter<<std::endl;
      else{
        //使用列表初始化，同时送入临时向量
        courses_null_queater.push_back({title,units,quarter});
      }
    }
    all_courses=courses_null_queater;
  }
  ofs.close();
}

/**
 * This function writes the courses NOT offered to the file
 * "student_output/courses_not_offered.csv".
 *
 * This function is ALWAYS called after the `write_courses_offered` function.
 * `unlisted_courses` will trivially contain classes that are not offered
 * since you delete offered classes from `all_courses` in the
 * `write_courses_offered` function.
 *
 * HINT: This should be VERY similar to `write_courses_offered`
 *
 * @param unlisted_courses A vector of courses that are not offered.
 */
void write_courses_not_offered(std::vector<Course> unlisted_courses) {
  /* (STUDENT TODO) Your code goes here... */
  std::ofstream ofs(COURSES_NOT_OFFERED_PATH);
  if(ofs.is_open()){
    ofs<<"Title,Number of Units,Quarter"<<std::endl;//写标题
    for(const auto& course:unlisted_courses){
      auto [title,units,quarter]=course;
      if(quarter=="null")
        ofs<<title<<","<<units<<","<<quarter<<std::endl;
      
    }
  }
  ofs.close();
}

int main() {
  /* Makes sure you defined your Course struct correctly! */
  static_assert(is_valid_course<Course>, "Course struct is not correctly defined!");

  std::vector<Course> courses;
  parse_csv("courses.csv", courses);

  /* Uncomment for debugging... */
  // print_courses(courses);

  write_courses_offered(courses);
  write_courses_not_offered(courses);

  return run_autograder();
}