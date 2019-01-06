//
// Created by wojtek on 22.05.18.
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <sstream>

#include "StudentBase.h"
#include "School.h"
#include "InputException.hpp"


BOOST_AUTO_TEST_SUITE(School_test)

    BOOST_AUTO_TEST_SUITE(addStudents_test)


        //addStudent(int id, T name, int age, int gr, std::string language)
        BOOST_AUTO_TEST_CASE(test1){
            School school;
        }
        BOOST_AUTO_TEST_CASE(add_student1){
            School school;
            BOOST_CHECK_NO_THROW(school.addStudent(1,"Wojciech", 12, 1, "Polish"));
        }
        BOOST_AUTO_TEST_CASE(add_student_name_throw){
            School school;
            //even if it's incorrect, it shouldn't give error, because name is checked earlier
            BOOST_CHECK_NO_THROW(school.addStudent(1,"1234567890123456789012345678901", 12, 1, "Polish"));
        }
        BOOST_AUTO_TEST_CASE(add_student_id_throw){
            School school;
            BOOST_CHECK_THROW(school.addStudent(-1,"Wojciech", 12, 1, "Polish"), InputException);
        }
        BOOST_AUTO_TEST_CASE(add_student_age_throw){
            School school;
            BOOST_CHECK_THROW(school.addStudent(1,"Wojciech", 1000, 1, "Polish"), InputException);
        }
        BOOST_AUTO_TEST_CASE(add_student_group_throw){
            School school;
            BOOST_CHECK_THROW(school.addStudent(1,"Wojciech", 12, 100, "Polish"), InputException);
        }
        BOOST_AUTO_TEST_CASE(add_student_lang_throw){
            School school;
            BOOST_CHECK_THROW(school.addStudent(1,"Wojciech", 12, 1, "Language of Republic of South Africa"), InputException);
        }
        BOOST_AUTO_TEST_CASE(add_student2){
            School school;
            BOOST_CHECK_NO_THROW(school.addStudent(2,"Przemyslaw Smith", 35, 5, "English"));
        }
        BOOST_AUTO_TEST_CASE(add_student3){
            School school;
            BOOST_CHECK_NO_THROW(school.addStudent(3,"Andrzej Nowak", 20, 5, "English"));
        }
        BOOST_AUTO_TEST_CASE(add_student4){
            School school;
            BOOST_CHECK_NO_THROW(school.addStudent(4,23000, 19, 5, "English"));
        }
        BOOST_AUTO_TEST_CASE(add_student5){
            School school;
            BOOST_CHECK_NO_THROW(school.addStudent(2,"Mieczyslaw Hadziuk", 30, 18, "English"));
        }
        BOOST_AUTO_TEST_CASE(add_student_small_id_throw){
            School school;
            BOOST_CHECK_NO_THROW(school.addStudent(1,"Wojciech", 12, 1, "Polish"));
            BOOST_CHECK_NO_THROW(school.addStudent(2,"Przemyslaw Smith", 35, 5, "English"));
            BOOST_CHECK_NO_THROW(school.addStudent(3,"Andrzej Nowak", 20, 5, "English"));
            BOOST_CHECK_NO_THROW(school.addStudent(4,23000, 19, 5, "English"));

            BOOST_CHECK_THROW(school.addStudent(2,"Mieczyslaw Hadziuk", 30, 18, "English"), InputException);
        }
        BOOST_AUTO_TEST_CASE(add_9students){
            School school;
            BOOST_CHECK_NO_THROW(school.addStudent(1, "Wojciech", 12, 1, "Polish"));
            BOOST_CHECK_NO_THROW(school.addStudent(2, "Przemyslaw Smith", 35, 5, "English"));
            BOOST_CHECK_NO_THROW(school.addStudent(3, "Andrzej Nowak", 20, 5, "English"));
            BOOST_CHECK_NO_THROW(school.addStudent(4, 23000, 19, 5, "English"));
            BOOST_CHECK_NO_THROW(school.addStudent(5, "Mieczyslaw Hadziuk", 30, 18, "English"));
            BOOST_CHECK_NO_THROW(school.addStudent(6, "Wojciech", 12, 1, "Polish"));
            BOOST_CHECK_NO_THROW(school.addStudent(7, "Przemyslaw Smith", 35, 5, "English"));
            BOOST_CHECK_NO_THROW(school.addStudent(8, "Andrzej Nowak", 20, 5, "English"));
            BOOST_CHECK_NO_THROW(school.addStudent(9, 23000, 19, 5, "English"));
        }
        BOOST_AUTO_TEST_CASE(add_99students) {
            School school;
            for (int i = 0; i < 11; i++) {
                BOOST_CHECK_NO_THROW(school.addStudent(11 * i + 1, "Wojciech", 12, 1, "Polish"));
                BOOST_CHECK_NO_THROW(school.addStudent(11 * i + 2, "Przemyslaw Smith", 35, 5, "English"));
                BOOST_CHECK_NO_THROW(school.addStudent(11 * i + 3, "Andrzej Nowak", 20, 5, "English"));
                BOOST_CHECK_NO_THROW(school.addStudent(11 * i + 4, 23000, 19, 5, "English"));
                BOOST_CHECK_NO_THROW(school.addStudent(11 * i + 5, "Mieczyslaw Hadziuk", 30, 18, "English"));
                BOOST_CHECK_NO_THROW(school.addStudent(11 * i + 6, "Wojciech", 12, 1, "Polish"));
                BOOST_CHECK_NO_THROW(school.addStudent(11 * i + 7, "Przemyslaw Smith", 35, 5, "English"));
                BOOST_CHECK_NO_THROW(school.addStudent(11 * i + 8, "Andrzej Nowak", 20, 5, "English"));
                BOOST_CHECK_NO_THROW(school.addStudent(11 * i + 9, 23000, 19, 5, "English"));
            }
        }
        BOOST_AUTO_TEST_CASE(add_toomuch_students){
            School school;
            for(int i=0;i<11;i++) {
                BOOST_CHECK_NO_THROW(school.addStudent(11*i+1, "Wojciech", 12, 1, "Polish"));
                BOOST_CHECK_NO_THROW(school.addStudent(11*i+2, "Przemyslaw Smith", 35, 5, "English"));
                BOOST_CHECK_NO_THROW(school.addStudent(11*i+3, "Andrzej Nowak", 20, 5, "English"));
                BOOST_CHECK_NO_THROW(school.addStudent(11*i+4, 23000, 19, 5, "English"));
                BOOST_CHECK_NO_THROW(school.addStudent(11*i+5, "Mieczyslaw Hadziuk", 30, 18, "English"));
                BOOST_CHECK_NO_THROW(school.addStudent(11*i+6, "Wojciech", 12, 1, "Polish"));
                BOOST_CHECK_NO_THROW(school.addStudent(11*i+7, "Przemyslaw Smith", 35, 5, "English"));
                BOOST_CHECK_NO_THROW(school.addStudent(11*i+8, "Andrzej Nowak", 20, 5, "English"));
                BOOST_CHECK_NO_THROW(school.addStudent(11*i+9, 23000, 19, 5, "English"));
            }
            BOOST_CHECK_THROW(school.addStudent(100, 23000, 19, 5, "English"), InputException);
        }
    BOOST_AUTO_TEST_SUITE_END();




    BOOST_AUTO_TEST_SUITE(printStudents_test)
        BOOST_AUTO_TEST_CASE(print_empty) {
            School school;
            std::stringstream str;
            BOOST_CHECK_THROW(school.printStudents(str), InputException);
        }
        BOOST_AUTO_TEST_CASE(print1){
            School school;
            BOOST_CHECK_NO_THROW(school.addStudent(1, "Wojciech", 12, 1, "Polish"));
            std::stringstream str;
            BOOST_CHECK_NO_THROW(school.printStudents(str));
            std::string output;
            str >> output;
            BOOST_CHECK_EQUAL(output, "ID|| Name or index number           || Age || Language        || Group\n1|| Wojciech                       || 12  || Polish          || 1");
        }



    BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()