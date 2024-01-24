#include "generics.h"
program_exception::program_exception(type_exception t){
    switch(t){
    case type_exception::faild_open_file:
        err = "failed to open the file";
        break;
    case type_exception::fill_out_blanks:
        err = "please fill out the blanks";
        break;
    case type_exception::user_exist:
        err = "the user exists";
        break;
    case type_exception::user_not_exist:
        err = "the user not exists";
        break;
    }
}
QString program_exception::what(){ return err; }
